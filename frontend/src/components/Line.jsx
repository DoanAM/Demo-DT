import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import { GradientTexture } from "@react-three/drei";

const Line = (props) => {
  const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
  return (
    <line geometry={lineGeometry}>
      <lineBasicMaterial
        attach="material"
        color={props.color}
        linewidth={1}
        linecap={"round"}
        linejoin={"round"}
      />
    </line>
  );
};

export default Line;
