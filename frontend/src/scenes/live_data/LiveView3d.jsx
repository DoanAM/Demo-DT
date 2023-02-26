import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import Axios from "axios";
import { Canvas } from "@react-three/fiber";
import { useQuery } from "@tanstack/react-query";
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
import Line from "../../components/Line.jsx";

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

// const Line = (props) => {
//   //points.push(new THREE.Vector3(-10000, 0, 0));
//   //points.push(new THREE.Vector3(0, 10000, 0));
//   //points.push(new THREE.Vector3(10000, 0, 0));
//   const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
//   return (
//     <line geometry={lineGeometry}>
//       <lineBasicMaterial
//         attach="material"
//         color={"#FFFFFF"}
//         linewidth={1}
//         linecap={"round"}
//         linejoin={"round"}
//       />
//     </line>
//   );
// };

const LiveView3d = () => {
  const { liveData, setLiveData } = useContext(LiveDataContext);
  const { points, setPoints } = useState([]);
  const PositionMachine = useRef({ xcurrpos: 0, ycurrpos: 0, zcurrpos: 0 }); //useState instead
  const lastPoint = useRef();
  const [lineArray, setLineArray] = useState([]);
  let startVector = null;
  let endVector = null;
  const axisOffsets = [-516, 530, 681];

  const fetchData = async () => {
    const response = await Axios.get("debug/live3dPoints");
    console.log(response);
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
      async function setMachineCoordinates() {
        // let arr = data.data.posVectorList;
        // //console.log(arr[index]);
        // PositionMachine.current = arr[index];
        // index++;
        // if (index < arr.length) {
        //   setTimeout(setMachineCoordinates, 16);
        //   console.log(
        //     "Effect",
        //     Date.now(),
        //     arr[index].xcurrpos,
        //     arr[index].xcurrpos / 10000
        //   );
        // }
        let arr = data.data.posVectorList;
        for (let index = 0; index < arr.length; index++) {
          PositionMachine.current = arr[index];
          console.log(
            "Effect",
            Date.now(),
            arr[index].xcurrpos,
            arr[index].xcurrpos / 10000
          );
          await sleep(16);
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
              .xcurrpos /
              10000 +
              axisOffsets[0],
            data.data.posVectorList[data.data.posVectorList.length - 1]
              .zcurrpos /
              10000 +
              axisOffsets[1],
            data.data.posVectorList[data.data.posVectorList.length - 1]
              .ycurrpos /
              10000 +
              axisOffsets[2]
          );
        } else {
          startVector = lastPoint.current;
        }
        endVector = new THREE.Vector3(
          data.data.posVectorList[0].xcurrpos / 10000 + axisOffsets[0],
          data.data.posVectorList[0].zcurrpos / 10000 + axisOffsets[1],
          data.data.posVectorList[0].ycurrpos / 10000 + axisOffsets[2]
        );
        const newLine = [startVector, endVector];
        setLineArray((e) => [...e, newLine]);
        lastPoint.current = endVector;
      }
    }
  }, [data]);

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
          <hemisphereLight
            color="rgb(242,247,253)"
            groundColor={"rgb(191,191,191)"}
            intensity={1.1}
          />
          <directionalLight position={[5, 575, 2265]} />
          <pointLight position={[0, 756, -2243]} />
          {lineArray.map((e) => {
            return <Line points={e} />;
          })}
          <MachineBed visible={true} />
          <group position={[0, 0, PositionMachine.current.ycurrpos / 10000]}>
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
