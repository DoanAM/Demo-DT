import { Box, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect } from "react";
import Axios from "axios";

const SimulationTable = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [tableContent, setTableContent] = useState();

  const fetchData = async () => {
    const response = await Axios.get("/simulationAPI/get-simulation");
    console.log(response);
    setTableContent((e) => response.data);
    return response;
  };

  const {
    isLoading,
    isError,
    data: AllSimulations,
  } = useQuery({
    queryKey: ["currentSimulations"],
    queryFn: fetchData,
    refetchInterval: 3000,
  });

  const columns = [
    { field: "sim_ID", headerName: "sim_ID" },
    { field: "timestamp", headerName: "timestamp" },
    { field: "nc_file", headerName: "nc_file" },
    { field: "csv_file", headerName: "csv_file" },
    { field: "finished", headerName: "finished" },
    /*  {
      field: "date",
      headerName: "DATE",
      flex: 1,
      cellClassName: "name-column--cell",
    },
    {
      field: "download",
      headerName: "DOWNLOAD",
      flex: 1,
      renderCell: ({}) => {
        return <Box></Box>;
      },
    }, */
  ];

  if (isLoading) {
    return <span>Loading...</span>;
  }

  if (isError) {
    return <span>Error: {error.message}</span>;
  }

  return (
    <Box height="30vh">
      <DataGrid
        rows={tableContent}
        columns={columns}
        getRowId={(row) => row.sim_ID}
      />
    </Box>
  );
};

export default SimulationTable;
