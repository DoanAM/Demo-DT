import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";

const Line = (props) => {
  //points.push(new THREE.Vector3(-10000, 0, 0));
  //points.push(new THREE.Vector3(0, 10000, 0));
  //points.push(new THREE.Vector3(10000, 0, 0));
  const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
  return (
    <line geometry={lineGeometry}>
      <lineBasicMaterial
        attach="material"
        color={0xffffff}
        linewidth={1}
        linecap={"round"}
        linejoin={"round"}
      />
    </line>
  );
};

export default Line;
