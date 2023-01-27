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
import LiveDataContext from "./LiveDataContext.jsx";

import {
  MachineBed,
  Bridge,
  XAxis,
  Spindle,
} from "../../components/MachineParts.jsx";

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

const LiveView3d = () => {
  const { liveData, setLiveData } = useContext(LiveDataContext);

  return (
    <Box
      sx={{
        width: "50%",
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        marginLeft: "5px",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <Canvas
        camera={{
          position: [0, 1300, 1500],
          far: 10000,
        }}
      >
        <React.Suspense fallback={<Loader />}>
          <axesHelper args={[1000]} />
          <OrbitControls />
          <ambientLight intensitiy={2.2} />
          <pointLight position={[-780, 430, 0]} />
          <MachineBed />
          <group position={[0, 0, -liveData.ycurrpos / 10000]}>
            <Bridge />
            <group position={[liveData.xcurrpos / 10000, 0, 0]}>
              <XAxis />
              <group position={[0, -liveData.zcurrpos / 10000, 0]}>
                <Spindle />
              </group>
            </group>
          </group>
        </React.Suspense>
      </Canvas>
    </Box>
  );
};

export default LiveView3d;

//liveData.ycurrpos / 10000, liveData.xcurrpos / 10000, liveData.zcurrpos / 10000
