import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import { Line, Box } from "@react-three/drei";

const Path = (props) => {
  const plane = new THREE.Plane(new THREE.Vector3(0, -1, 0), 270);
  const colors = props.rgb.map(
    (rgb) => new THREE.Color(rgb[0] / 255, rgb[1] / 255, rgb[2] / 255)
  );
  return (
    <Line
      points={props.points}
      color="white"
      clippingPlanes={[plane]}
      clipIntersection={true}
      vertexColors={colors}
    ></Line>
  );

  // const lineGeometry = new THREE.BufferGeometry().setFromPoints(props.points);
  // return (
  //   <line geometry={lineGeometry}>
  //     <lineBasicMaterial
  //       attach="material"
  //       color={props.color}
  //       linewidth={1}
  //       linejoin={"round"}
  //     />
  //   </line>
  // );
};

export default Path;
