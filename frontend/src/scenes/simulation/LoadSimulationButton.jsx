import { Box, Button, Typography, useTheme } from "@mui/material";
import { DataGrid } from "@mui/x-data-grid";
import { tokens } from "../../theme";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect, useContext } from "react";
import { useLoader } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";
import Axios from "axios";
import SimulationDataContext from "./SimulationDataContext.jsx";

const Workpiece = (props) => {
  const geom = useLoader(STLLoader, props);
  return (
    <mesh position={[0, 230, 260]} rotation-x={-Math.PI / 2}>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(50, 168, 82)" />
    </mesh>
  );
};

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

    /*     response.data.forEach((item, idx) => {
      console.log(Workpiece(item.stlPath));
      //item.stlPath = Workpiece(item.stlPath);
    }); */
    console.log(response.data);
    /*     for (const item of response.data) {
      const fileUrl = item.stlPath;
      console.log(fileUrl);
      console.log(Workpiece(fileUrl));
    } */
    //console.log(response.data);
    const simData = { ID: id, data: response.data };
    setSimulationData((e) => [...e, simData]);
    return response;
  };

  const { isFetching, data, refetch } = useQuery({
    queryKey: ["newSimulation", sim_id],
    queryFn: ({ queryKey }) => getSimulationData(queryKey[1]),
    refetchOnWindowFocus: false,
    enabled: false,
  });

  const handleClick = () => {
    refetch();
  };

  /*   useEffect(() => {
    if (data != undefined) {
      for (const item of data.data) {
        console.log(Workpiece());
      }
      const id = data.data[0].simulation;
      const simData = { ID: id, data: data.data };
      console.log(simData);
      setSimulationData((e) => [...e, simData]);
    }
  }, [data]); */

  return (
    <Button
      onClick={handleClick}
      width="30px"
      sx={{ color: colors.orangeAccent[300] }}
    >
      {isFetching ? "Fetching" : "Load"}
    </Button>
  );
};

export default LoadSimulationButton;
