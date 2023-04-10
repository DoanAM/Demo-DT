import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import { GradientTexture } from "@react-three/drei";

function Line2({ points }) {
  const lineRef = useRef();
  const axisOffsets = [-516, 530, 681];

  useEffect(() => {
    if (lineRef.current) {
      const line = lineRef.current;
      line.geometry.setFromPoints(
        points.map(
          (p) =>
            new THREE.Vector3(
              p.XCurrPos + axisOffsets[0],
              p.ZCurrPos + axisOffsets[1],
              -p.YCurrPos + axisOffsets[2]
            )
        )
      );
      line.geometry.needsUpdate = true;
    }
  }, [points]);

  return (
    <line ref={lineRef}>
      <bufferGeometry />
      <lineBasicMaterial color={0xff0000} linewidth={2} />
    </line>
  );
}
export default Line2;
