import * as THREE from "three";
import React from "react";
import { CylinderGeometry, Mesh, MeshBasicMaterial } from "three";

const Tool = (props) => {
  return (
    <mesh position={props.position}>
      <cylinderGeometry args={[2.5, 2.5, 20, 32]} />
      <meshPhongMaterial attach="material" color={"rgb(67,117,95)"} />
    </mesh>
  );
};

export default Tool;
