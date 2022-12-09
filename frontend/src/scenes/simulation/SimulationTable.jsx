import { Box, Button, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect } from "react";
import Axios from "axios";
import LoadSimulationButton from "./LoadSimulationButton.jsx";

const SimulationTable = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [tableContent, setTableContent] = useState();

  const fetchData = async () => {
    const response = await Axios.get("/simulationAPI/get-simulation");
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
    refetchInterval: 60000,
  });

  const columns = [
    { field: "sim_ID", headerName: "sim_ID" },
    {
      field: "timestamp",
      headerName: "timestamp",
      type: "dateTime",
      flex: 1,
      minWidth: 120,
    },
    { field: "nc_file", headerName: "nc_file" },
    {
      field: "finished",
      headerName: "finished",
      flex: 1,
      renderCell: ({ row: { sim_ID } }) => {
        return <LoadSimulationButton sim_ID={sim_ID} />;
      },
    },
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
        initialState={{
          sorting: {
            sortModel: [{ field: "sim_ID", sort: "desc" }],
          },
          pagination: {
            pageSize: 5,
          },
        }}
      />
    </Box>
  );
};

export default SimulationTable;
