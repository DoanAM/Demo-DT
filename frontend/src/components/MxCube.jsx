import { MachineBed, Bridge, XAxis, Spindle } from "./MachineParts.jsx";
import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import { useLoader, useFrame } from "@react-three/fiber";
import cncfakedata from "../data/cncfakedata.json";
import Tool from "./Tool.jsx";

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

const MxCube = (props) => {
  const bridgeRef = useRef();
  const xAxisRef = useRef();
  const zAxisRef = useRef();
  const spindleRef = useRef();
  const data = cncfakedata;
  const toolLength = 100;
  const toolDiameter = 30;

  useFrame(() => {
    bridgeRef.current.position.z = props.bridgePosition;
    xAxisRef.current.position.x = props.xAxisPosition;
    zAxisRef.current.position.y = props.spindlePosition;
  });

  return (
    <group>
      <MachineBed visible={true} />
      <group ref={bridgeRef}>
        <Bridge />
        <group ref={xAxisRef}>
          <XAxis />
          <group ref={zAxisRef}>
            <Spindle toolOffset={props.toolLength / 2} />
            <Tool
              position={[-518, 540, 682]}
              diameter={props.toolDiameter}
              length={props.toolLength}
            />
          </group>
        </group>
      </group>
    </group>
  );
};

export default MxCube;
