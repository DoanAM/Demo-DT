import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import { Canvas } from "@react-three/fiber";
import { OrbitControls, Html, useProgress } from "@react-three/drei";
import { useLoader, useThree } from "@react-three/fiber";
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

const Line = (props) => {
  //points.push(new THREE.Vector3(-10000, 0, 0));
  //points.push(new THREE.Vector3(0, 10000, 0));
  //points.push(new THREE.Vector3(10000, 0, 0));
  const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.data);
  return (
    <line geometry={lineGeometry}>
      <lineBasicMaterial
        attach="material"
        color={"#eb3434"}
        linewidth={1}
        linecap={"round"}
        linejoin={"round"}
      />
    </line>
  );
};

const LiveView3d = () => {
  const { liveData, setLiveData } = useContext(LiveDataContext);
  const { points, setPoints } = useState([]);

  useEffect(() => {
    vec = new THREE.Vector3(
      liveData.xcurrpos,
      liveData.zcurrpos,
      liveData.ycurrpos
    );
    setPoints((e) => [...e, vec]);
  }, [LiveDataContext]);

  /* const points = [
    new THREE.Vector3(-10000, 0, 0),
    new THREE.Vector3(10000, 0, 0),
  ]; */
  //new THREE.Vector3(10000, 0, 0),

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
          {points && <Line data={points} />}
          <MachineBed />
          <group position={[0, 0, 0]}>
            <Bridge />
            <group position={[0, 0, 0]}>
              <XAxis />
              <group position={[0, 0, 0]}>
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

{
  /* <group position={[0, 0, liveData.ycurrpos / 50000]}>
            <Bridge />
            <group position={[liveData.xcurrpos / 50000, 0, 0]}>
              <XAxis />
              <group position={[0, liveData.zcurrpos / 100000, 0]}>
                <Spindle />
              </group>
            </group>
          </group> */
}
