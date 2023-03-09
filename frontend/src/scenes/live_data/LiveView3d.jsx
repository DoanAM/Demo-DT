import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import Axios from "axios";
import { Canvas } from "@react-three/fiber";
import { useQuery } from "@tanstack/react-query";
import { OrbitControls, Html, useProgress } from "@react-three/drei";
import { useLoader, useThree } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";
import { Box } from "@mui/material";
import MxCube from "../../components/MxCube.jsx";
import Line from "../../components/Line.jsx";
import cncfakedata from "../../data/cncfakedata.json";

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

const LiveView3d = () => {
  const [positionMachine, setPositionMachine] = useState({
    xcurrpos: 0,
    ycurrpos: 0,
    zcurrpos: 0,
  });
  const endPoint = useRef();
  const [lineArray, setLineArray] = useState([]);
  let startVector = null;
  let endVector = null;
  const axisOffsets = [-516, 530, 681];
  const lastData = useRef();
  //const data = cncfakedata;

  const fetchData = async () => {
    const response = await Axios.get("debug/live3dPoints");
    console.log("Data is: ", response);
    //setPoints(response.data);
    return response;
  };

  const { status, data } = useQuery({
    queryKey: ["live3dPoints"],
    queryFn: fetchData,
    refetchInterval: 1000,
  });

  async function setMachineCoordinates() {
    let arr = data.data.posVectorList;
    for (let index = 0; index < arr.length; index++) {
      setPositionMachine(arr[index]);
      //console.log("Effect", Date.now(), positionMachine.current);
      await sleep(20);
    }
  }

  useEffect(() => {
    if (data != undefined) {
      setMachineCoordinates();
    }
  }, [data]);

  //draw lines
  useEffect(() => {
    //check if data is available
    if (data != undefined) {
      //check if the new data === last data, then do nothing
      if (data.data == lastData.current) {
        console.log("data is old");
        return;
      }
      //check if line should be drawn
      else if (data.data.line == true) {
        console.log("data is not old");
        lastData.current = data.data;
        //check if line starting point is available
        if (endPoint.current == undefined) {
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
          startVector = endPoint.current;
        }
        endVector = new THREE.Vector3(
          data.data.posVectorList[0].xcurrpos / 10000 + axisOffsets[0],
          data.data.posVectorList[0].zcurrpos / 10000 + axisOffsets[1],
          data.data.posVectorList[0].ycurrpos / 10000 + axisOffsets[2]
        );
        const newLine = [startVector, endVector];
        setLineArray((e) => [...e, newLine]);
        endPoint.current = endVector;
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

          <MxCube
            bridgePosition={positionMachine.ycurrpos / 10000}
            xAxisPosition={positionMachine.xcurrpos / 10000}
            spindlePosition={positionMachine.zcurrpos / 10000}
          />
        </React.Suspense>
      </Canvas>
    </Box>
  );
};

export default LiveView3d;
