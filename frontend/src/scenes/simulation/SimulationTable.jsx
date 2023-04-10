import { Box, Button, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect } from "react";
import Axios from "axios";
import SimulationLoadHandler from "./SimulationLoadHandler.jsx";

const rows = [
  {
    sim_ID: 1,
    timestamp: "2023-04-08 20:25:13",
    nc_file: "Teil 3",
    precision: 0.3,
    finished: true,
  },
  {
    sim_ID: 2,
    timestamp: "2023-04-08 20:25:13",
    nc_file: "Teil 2",
    precision: 0.1,
    finished: false,
  },
  {
    sim_ID: 3,
    timestamp: "2023-04-08 20:25:13",
    nc_file: "Teil 1",
    precision: 0.4,
    finished: false,
  },
];

const SimulationTable = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [tableContent, setTableContent] = useState();

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
    { field: "precision", headerName: "Precision" },
    {
      field: "finished",
      headerName: "finished",
      flex: 1,
      renderCell: ({ row: { sim_ID, finished } }) => {
        return <SimulationLoadHandler sim_ID={sim_ID} finished={finished} />;
      },
    },
  ];

  return (
    <Box height="30vh">
      <DataGrid
        sx={{
          "& .MuiDataGrid-cell": {
            borderBottomColor: colors.black[400],
          },
          "	.MuiDataGrid-overlay": {
            borderLeftColor: colors.black[400],
          },
          "& .MuiDataGrid-root": {
            borderBottomColor: colors.black[400],
          },
          "& .MuiDataGrid-footerContainer": {
            borderTopColor: colors.black[400],
            minHeight: "5vh",
          },
          "& .MuiDataGrid-columnHeaders": {
            borderBottomColor: colors.black[400],
          },
          border: "2px solid #5921d0",
          boxShadow: "4px 2px 15px rgba(89, 33, 208, 0.29)",
          backgroundColor: colors.indigoAccent[900],
        }}
        rows={rows}
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
        density="standard"
      />
    </Box>
  );
};

export default SimulationTable;
