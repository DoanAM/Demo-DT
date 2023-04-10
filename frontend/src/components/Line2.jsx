import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import { GradientTexture } from "@react-three/drei";

function Line2(props) {
  const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
  return (
    <line geometry={lineGeometry}>
      <lineBasicMaterial
        attach="material"
        color={props.color}
        linewidth={1}
        linejoin={"round"}
      />
    </line>
  );
}
export default Line2;
