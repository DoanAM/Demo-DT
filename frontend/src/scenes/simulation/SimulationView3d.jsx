import React from "react";
import { useState, useEffect, useContext, useRef, useMemo } from "react";
import { Canvas } from "@react-three/fiber";
import * as THREE from "three";
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

function normalize(value, min, max, newMin, newMax) {
  return Math.round(((value - min) / (max - min)) * (newMax - newMin) + newMin);
}

function rgbToHex(r, g, b) {
  const rHex = r.toString(16).padStart(2, "0");
  const gHex = g.toString(16).padStart(2, "0");
  const bHex = b.toString(16).padStart(2, "0");
  return "#" + rHex + gHex + bHex;
}

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

const SimulationView3d = () => {
  const { simulationData, setSimulationData } = useContext(
    SimulationDataContext
  );
  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );
  const axisOffsets = [-516, 530, 681];

  const [simulation, setSimulation] = useState();
  const [xCoordinate, setXCoordinate] = useState(0);
  const [yCoordinate, setYCoordinate] = useState(0);
  const [zCoordinate, setZCoordinate] = useState(0);
  const [vectorArray, setVectorArray] = useState();
  const [color, setColor] = useState();
  const [stlPath, setStlPath] = useState(null);
  const { playbackIdx, setPlaybackIdx } = useContext(PlaybackIdxContext);
  const playbackInterval = useRef();

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
    }, 40);
  };

  useEffect(() => {
    if (simulation == null || playbackIdx == simulation.length) {
      clearInterval(playbackInterval.current);
      playbackInterval.current = null;
      setPlaybackIdx(0);
      return;
    } else {
      setXCoordinate(simulation[playbackIdx].xcurrpos);
      setYCoordinate(simulation[playbackIdx].ycurrpos);
      setZCoordinate(simulation[playbackIdx].zcurrpos);
      if (simulation[playbackIdx].stlPath != null) {
        setStlPath(simulation[playbackIdx].stlPath);
      }
    }
  }, [playbackIdx]);

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
  //     console.log(vectorArray);
  //   }
  // }, [simulation]);

  useEffect(() => {
    if (simulation != null) {
      let pointPairs = [];
      for (let i = 0; i < simulation.length - 1; i++) {
        const startPoint = new THREE.Vector3(
          simulation[i].xcurrpos,
          simulation[i].zcurrpos + 230,
          -simulation[i].ycurrpos + 260
        );
        const endPoint = new THREE.Vector3(
          simulation[i + 1].xcurrpos,
          simulation[i + 1].zcurrpos + 230,
          -simulation[i + 1].ycurrpos + 260
        );
        const red = normalize(simulation[i].xcurrpos, 0, 100, 0, 255);
        const green = 255 - normalize(simulation[i].xcurrpos, 0, 100, 0, 255);
        let lineColor = rgbToHex(red, green, 0);
        pointPairs.push({
          points: [startPoint, endPoint],
          lineColor: lineColor,
        });
      }
      setVectorArray(pointPairs);
      console.log(vectorArray);
    }
  }, [simulation]);

  const handlePause = () => {
    clearInterval(playbackInterval.current);
    playbackInterval.current = null;
  };

  return (
    <Box
      sx={{
        width: "50%",
        height: "55vh",
        display: "flex",
        flexDirection: "column",
        justifyContent: "center",
        alignItems: "center",
        marginLeft: "5px",
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
          position: [0, 1300, 1500],
          far: 10000,
        }}
      >
        <React.Suspense fallback={<Loader />}>
          <axesHelper args={[1000]} />
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
                <Line points={item.points} color={item.lineColor} key={index} />
              );
            })}
          {/* {vectorArray != undefined && <Line points={vectorArray} />} */}
          <MachineBed visible={true} />
          <group position={[0, 0, -yCoordinate - 419]}>
            <Bridge />
            <group position={[xCoordinate + 518, 0, 0]}>
              <XAxis />
              <group position={[0, zCoordinate - 285, 0]}>
                <Spindle />
                <Tool position={[-518, 527, 680]} />
              </group>
            </group>
          </group>
          {simulation != undefined &&
            simulation.map((item, index) => {
              return (
                <Workpiece
                  path={item.stlPath}
                  key={index}
                  visible={index === playbackIdx}
                />
              );
            })}
        </React.Suspense>
      </Canvas>
      {simulation != undefined && (
        <Box display="flex">
          <Slider
            onChange={handleSliderChange}
            valueLabelDisplay="auto"
            max={simulation.length - 1}
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
      )}
    </Box>
  );
};

export default SimulationView3d;
