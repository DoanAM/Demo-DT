import React from "react";
import { useState, useEffect, useContext, useRef, useMemo } from "react";
import { Canvas } from "@react-three/fiber";
import * as THREE from "three";
import { OrbitControls, Html, useProgress } from "@react-three/drei";
import { useLoader } from "@react-three/fiber";
import { tokens } from "../../theme";
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
import {
  SimulationDataContext,
  CurrentSimulationContext,
  PlaybackIdxContext,
} from "./Context.jsx";
import {
  MachineBed,
  Bridge,
  XAxis,
  Spindle,
} from "../../components/MachineParts.jsx";
import Line from "../../components/Line.jsx";
import Workpiece from "../../components/Workpiece.jsx";
import Tool from "../../components/Tool.jsx";
import { red } from "@mui/material/colors";
import { LineColorVariables_Simulation } from "../../data/LineColorVariables.js";
import { colorMapper } from "../../components/Utilities.jsx";
import MxCube from "../../components/MxCube.jsx";
import SimulationJSON from "../../data/Simulation.json";

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

const SimulationView3d = () => {
  const fileNames = Array.from({ length: 286 }, (_, i) => (i + 1) * 100);

  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const { simulationData, setSimulationData } = useContext(
    SimulationDataContext
  );
  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );

  const [simulation, setSimulation] = useState();
  const [xCoordinate, setXCoordinate] = useState(0);
  const [yCoordinate, setYCoordinate] = useState(0);
  const [zCoordinate, setZCoordinate] = useState(0);
  const [vectorArray, setVectorArray] = useState();
  //const [color, setColor] = useState();
  const [stlPath, setStlPath] = useState(null);
  const { playbackIdx, setPlaybackIdx } = useContext(PlaybackIdxContext);
  const playbackInterval = useRef();
  const [lineVariable, setLineVariable] = useState("xcurrpos");
  const toolLength = 20;
  const toolDiameter = 5;

  const handleSelectChange = (e) => {
    const id = e.target.value;
    const obj = simulationData.find((o) => o.ID === id);
    setSimulation(obj.data);
    setCurrentSimulationData(obj.data);
  };

  const handleSliderChange = (e, nV) => {
    setPlaybackIdx(nV);
  };

  const handlePlayback = () => {
    playbackInterval.current = setInterval(() => {
      setPlaybackIdx((value) => value + 1);
    }, 150);
  };

  useEffect(() => {
    if (playbackIdx != 0) {
      setXCoordinate(SimulationJSON[playbackIdx].XCurrPos);
      setYCoordinate(SimulationJSON[playbackIdx].YCurrPos);
      setZCoordinate(SimulationJSON[playbackIdx].ZCurrPos);
    }
  }, [playbackIdx]);

  useEffect(() => {
    if (playbackIdx >= 285) {
      clearInterval(playbackInterval.current);
      playbackInterval.current = null;
      setPlaybackIdx(0);
    }
  }, [playbackIdx]);

  // useEffect(() => {
  //   if (simulation == null || playbackIdx == simulation.length) {
  //     clearInterval(playbackInterval.current);
  //     playbackInterval.current = null;
  //     setPlaybackIdx(0);
  //     return;
  //   } else {
  //     setXCoordinate(simulation[playbackIdx].XCurrPos);
  //     setYCoordinate(simulation[playbackIdx].YCurrPos);
  //     setZCoordinate(simulation[playbackIdx].ZCurrPos);
  //     if (simulation[playbackIdx].stlPath != null) {
  //       setStlPath(simulation[playbackIdx].stlPath);
  //     }
  //   }
  // }, [playbackIdx]);

  // useEffect(() => {
  //   if (simulation != null) {
  //     setVectorArray(
  //       simulation.map(function (item) {
  //         return new THREE.Vector3(
  //           item.xcurrpos,
  //           item.zcurrpos + 230, //+ 230
  //           -item.ycurrpos + 260 //+ 260
  //         );
  //       })
  //     );
  //   }
  // }, [simulation]);

  useEffect(() => {
    let pointPairs = [];
    for (let i = 1; i < 286; i++) {
      const startPoint = new THREE.Vector3(
        SimulationJSON[i].XCurrPos,
        SimulationJSON[i].ZCurrPos + 230,
        -SimulationJSON[i].YCurrPos + 260
      );
      const endPoint = new THREE.Vector3(
        SimulationJSON[i + 1].XCurrPos,
        SimulationJSON[i + 1].ZCurrPos + 230,
        -SimulationJSON[i + 1].YCurrPos + 260
      );
      ///calculate Color
      const colorArray = () => {
        let result = {};
        result = colorMapper(SimulationJSON[i]["Removal_Volume"], -1, 4);
        return result;
      };
      pointPairs.push({
        points: [startPoint, endPoint],
        color: colorArray(),
      });
    }
    setVectorArray(pointPairs);
  }, []);

  const handlePause = () => {
    clearInterval(playbackInterval.current);
    playbackInterval.current = null;
  };

  const handleLineColorChange = (e) => {
    setLineVariable(e.target.value);
  };

  return (
    <Box
      sx={{
        paddingTop: "15px",
        width: "50%",
        height: "55vh",
        display: "flex",
        flexDirection: "column",
        justifyContent: "center",
        alignItems: "center",
        marginLeft: "5px",
        border: "2px solid #5921d0",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(89, 33, 208, 0.29)",
        backgroundColor: colors.indigoAccent[900],
      }}
    >
      <Canvas
        camera={{
          position: [0, 1300, 1500],
          far: 10000,
        }}
      >
        <React.Suspense fallback={<Loader />}>
          {/* <axesHelper args={[1000]} /> */}
          <OrbitControls />
          <hemisphereLight
            color="rgb(242,247,253)"
            groundColor={"rgb(191,191,191)"}
            intensity={1.1}
          />
          <directionalLight position={[5, 575, 2265]} />
          <pointLight position={[0, 756, -2243]} />
          {vectorArray != undefined &&
            vectorArray.map((item, index) => {
              return (
                <Line points={item.points} color={item.color} key={index} />
              );
            })}
          <MachineBed visible={true} />
          <MxCube
            bridgePosition={-yCoordinate - 419}
            xAxisPosition={xCoordinate + 518}
            spindlePosition={zCoordinate - 300}
            toolDiameter={toolDiameter}
            toolLength={toolLength}
          />
          {fileNames.map((filename) => (
            <Workpiece
              key={filename}
              path={filename}
              visible={filename === playbackIdx * 100}
            />
          ))}
          {/* {filePaths.map((filePath) => (
            <Workpiece path={filePath} key={filePath} visible={true} />
          ))} */}
        </React.Suspense>
      </Canvas>
      <Box display="flex">
        <Slider
          onChange={handleSliderChange}
          valueLabelDisplay="auto"
          min={1}
          max={285}
          sx={{ width: "30vw" }}
          value={playbackIdx}
        />
        <IconButton onClick={handlePlayback}>
          <PlayArrowOutlinedIcon />
        </IconButton>
        <IconButton onClick={handlePause}>
          <PauseCircleOutlineOutlinedIcon />
        </IconButton>
      </Box>
    </Box>
  );
};

export default SimulationView3d;
