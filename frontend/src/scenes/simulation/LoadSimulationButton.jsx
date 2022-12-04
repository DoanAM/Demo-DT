import { Box, Button, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect, useContext } from "react";
import Axios from "axios";
import SimulationDataContext from "./SimulationDataContext.jsx";

const LoadSimulationButton = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const sim_id = props.sim_ID;
  const { simulationData, setSimulationData } = useContext(
    SimulationDataContext
  );

  const getSimulationData = async (id) => {
    const response = await Axios.get(
      "/simulationAPI/get-simulationData/?simulation=" + id
    );
    const simData = { [id]: response.data };
    setSimulationData((e) => [...e, simData]);
    console.log(simData);
    return response;
  };

  const { status, data, refetch } = useQuery({
    queryKey: ["newSimulation", sim_id],
    queryFn: ({ queryKey }) => getSimulationData(queryKey[1]),
    refetchOnWindowFocus: false,
    enabled: false,
  });

  const handleClick = () => {
    refetch();
  };

  return (
    <Button
      onClick={handleClick}
      width="30px"
      backgroundColor={colors.orangeAccent[300]}
    >
      {" "}
      Load
    </Button>
  );
};

export default LoadSimulationButton;
