import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import { Canvas } from "@react-three/fiber";
import { useQuery } from "@tanstack/react-query";
import Axios from "axios";
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
  const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
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
  const PositionMachine = useRef({ xcurrpos: 0, ycurrpos: 0, zcurrpos: 0 });
  const lastPoint = useRef();
  const [lineArray, setLineArray] = useState([]);
  let startVector = null;
  let endVector = null;

  const fetchData = async () => {
    const response = await Axios.get("debug/live3dPoints");
    //console.log(response);
    //setPoints(response.data);
    return response;
  };

  const { status, data } = useQuery({
    queryKey: ["live3dPoints"],
    queryFn: fetchData,
    refetchInterval: 1000,
  });

  useEffect(() => {
    if (data != undefined) {
      let index = 0;
      function setMachineCoordinates() {
        let arr = data.data.posVectorList;
        //console.log(arr[index]);
        PositionMachine.current = arr[index];
        index++;
        if (index < arr.length) {
          setTimeout(setMachineCoordinates, 80);
        }
      }
      setMachineCoordinates();
    }
  }, [data]);

  useEffect(() => {
    if (data != undefined) {
      if (data.data.line == true) {
        if (lastPoint.current == undefined) {
          startVector = new THREE.Vector3(
            data.data.posVectorList[data.data.posVectorList.length - 1]
              .xcurrpos / 10000,
            data.data.posVectorList[data.data.posVectorList.length - 1]
              .zcurrpos / 10000,
            data.data.posVectorList[data.data.posVectorList.length - 1]
              .ycurrpos / 10000
          );
        } else {
          startVector = lastPoint.current;
        }
        endVector = new THREE.Vector3(
          data.data.posVectorList[0].xcurrpos / 10000,
          data.data.posVectorList[0].zcurrpos / 10000,
          data.data.posVectorList[0].ycurrpos / 10000
        );
        const newLine = [startVector, endVector];
        setLineArray((e) => [...e, newLine]);
        lastPoint.current = endVector;
      }
    }
  }, [data]);

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
          <group position={[0, 0, -PositionMachine.current.ycurrpos / 10000]}>
            <Bridge />
            <group position={[PositionMachine.current.xcurrpos / 10000, 0, 0]}>
              <XAxis />
              <group
                position={[0, PositionMachine.current.zcurrpos / 10000, 0]}
              >
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
