import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import { Canvas } from "@react-three/fiber";
import { OrbitControls, Html, useProgress } from "@react-three/drei";
import { useLoader } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";
import {
  Box,
  IconButton,
  useTheme,
  Typography,
  Slider,
  FormControl,
  InputLabel,
  Select,
  MenuItem,
} from "@mui/material";
import PlayArrowOutlinedIcon from "@mui/icons-material/PlayArrowOutlined";
import PauseCircleOutlineOutlinedIcon from "@mui/icons-material/PauseCircleOutlineOutlined";
import pathMachineBedStl from "../../data/MachineBed.stl";
import pathBridgeStl from "../../data/Bridge.stl";
import pathXAxisStl from "../../data/X-Axis.stl";
import pathSpindleStl from "../../data/Spindle.stl";
import SimulationDataContext from "./SimulationDataContext.jsx";

const MachineBed = () => {
  const geom = useLoader(STLLoader, pathMachineBedStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach="material" color="rgb(77,78,102)" />
    </mesh>
  );
};

const Bridge = () => {
  const geom = useLoader(STLLoader, pathBridgeStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(26, 71, 50)" />
    </mesh>
  );
};

const XAxis = () => {
  const geom = useLoader(STLLoader, pathXAxisStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(47, 103, 193)" />
    </mesh>
  );
};

const Spindle = () => {
  const geom = useLoader(STLLoader, pathSpindleStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(228, 123, 37)" />
    </mesh>
  );
};

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

const View3d = () => {
  const { simulationData, setSimulationData } = useContext(
    SimulationDataContext
  );
  const [simulation, setSimulation] = useState();
  const [xCoordinate, setXCoordinate] = useState(0);
  const [yCoordinate, setYCoordinate] = useState(0);
  const [zCoordinate, setZCoordinate] = useState(0);
  const [playbackIdx, setPlaybackIdx] = useState(0);
  const playbackInterval = useRef();

  const handleSelectChange = (e) => {
    const id = e.target.value;
    const obj = simulationData.find((o) => o.ID === id);
    setSimulation(obj.data);
  };

  const handleSliderChange = (e, nV) => {
    setPlaybackIdx(nV);
  };

  const handlePlayback = () => {
    playbackInterval.current = setInterval(() => {
      setPlaybackIdx((value) => value + 1);
    }, 500);
  };

  useEffect(() => {
    if (simulation == null || playbackIdx == simulation.length) {
      clearInterval(playbackInterval.current);
      playbackInterval.current = null;
      console.log("no simulation");
      return;
    } else {
      setXCoordinate(simulation[playbackIdx].xcurrpos);
      setYCoordinate(simulation[playbackIdx].ycurrpos);
      setZCoordinate(simulation[playbackIdx].zcurrpos);
    }
  }, [playbackIdx]);

  const handlePause = () => {
    clearInterval(playbackInterval.current);
    playbackInterval.current = null;
  };

  return (
    <Box
      sx={{
        width: "50%",
        height: "50vh",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <FormControl fullWidth>
        <InputLabel id="test-select-label">Simulation</InputLabel>
        <Select
          labelId="test-select-label"
          label="Time"
          defaultValue={""}
          sx={{
            width: 200,
            height: 30,
          }}
          onChange={handleSelectChange}
        >
          {simulationData.map((item) => {
            return (
              <MenuItem value={item.ID} key={item.ID}>
                {item.ID}
              </MenuItem>
            );
          })}
        </Select>
      </FormControl>
      <Canvas
        camera={{
          position: [0, 1200, 1500],
          far: 10000,
        }}
      >
        <React.Suspense fallback={<Loader />}>
          <axesHelper args={[1000]} />
          <OrbitControls />
          <ambientLight intensitiy={2.2} />
          <pointLight position={[-780, 430, 0]} />
          <MachineBed />
          <group position={[0, 0, yCoordinate]}>
            <Bridge />
            <group position={[xCoordinate, 0, 0]}>
              <XAxis />
              <group position={[0, zCoordinate, 0]}>
                <Spindle />
              </group>
            </group>
          </group>
        </React.Suspense>
      </Canvas>
      {simulation != undefined && (
        <Box display="flex">
          <Slider
            onChange={handleSliderChange}
            valueLabelDisplay="auto"
            max={simulation.length - 1}
            width="50%"
            value={playbackIdx}
          />
          <IconButton onClick={handlePlayback}>
            <PlayArrowOutlinedIcon />
          </IconButton>
          <IconButton onClick={handlePause}>
            <PauseCircleOutlineOutlinedIcon />
          </IconButton>
        </Box>
      )}
    </Box>
  );
};

export default View3d;
