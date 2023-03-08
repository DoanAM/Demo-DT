import { MachineBed, Bridge, XAxis, Spindle } from "./MachineParts.jsx";
import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import { useLoader, useFrame } from "@react-three/fiber";
import cncfakedata from "../data/cncfakedata.json";

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

const MxCube = (props) => {
  const bridgeRef = useRef();
  const xAxisRef = useRef();
  const spindleRef = useRef();
  const data = cncfakedata;

  useFrame(() => {
    bridgeRef.current.position.z = props.bridgePosition;
    xAxisRef.current.position.x = props.xAxisPosition;
    spindleRef.current.position.y = props.spindlePosition;
    py;
  });
  return (
    <group>
      <MachineBed visible={true} />
      <group ref={bridgeRef}>
        <Bridge />
        <group ref={xAxisRef}>
          <XAxis />
          <group ref={spindleRef}>
            <Spindle />
          </group>
        </group>
      </group>
    </group>
  );
};

export default MxCube;
