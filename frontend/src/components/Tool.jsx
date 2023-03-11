import * as THREE from "three";
import React from "react";
import { CylinderGeometry, Mesh, MeshBasicMaterial } from "three";

const Tool = (props) => {
  return (
    <mesh position={props.position}>
      <cylinderGeometry
        args={[props.diameter / 2, props.diameter / 2, props.length, 32]}
      />
      <meshPhongMaterial attach="material" color={"rgb(67,117,95)"} />
    </mesh>
  );
};

export default Tool;
