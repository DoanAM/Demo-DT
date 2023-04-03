import { Box, Button, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect, useContext } from "react";
import { useLoader } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";
import Axios from "axios";
import { SimulationDataContext } from "./Context.jsx";
import Workpiece from "../../components/Workpiece.jsx";

const SimulationLoadHandler = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const sim_id = props.sim_ID;
  const { simulationData, setSimulationData } = useContext(
    SimulationDataContext
  );

  const getSimulationData = async (id) => {
    const response = await Axios.get(
      `/simulation-API/get-simulationData/?simulation=${id}`
    );
    console.log(response.data);
    const updatedData = response.data.map((item) => {
      return {
        ...item,
        workpiece: <Workpiece key={item.stlPath} path={item.stlPath} />,
      };
    });

    const simData = { ID: id, data: updatedData };
    if (simulationData.some((item) => item.ID === simData.ID)) {
      return null;
    } else {
      setSimulationData((e) => [...e, simData]);
      return response;
    }
  };

  const { isFetching, refetch } = useQuery({
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
      disabled={!props.finished}
      onClick={handleClick}
      width="30px"
      sx={{ color: colors.orangeAccent[300] }}
    >
      {props.finished ? "Load" : "Not Finished"}
    </Button>
  );
};

export default SimulationLoadHandler;
