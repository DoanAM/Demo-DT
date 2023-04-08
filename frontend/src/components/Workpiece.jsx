import React from "react";
import { useLoader } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";

const Workpiece = (props) => {
  const geom = useLoader(STLLoader, `/static/frontend/MRS/${props.path}.stl`);
  //const geom = props.geom;
  return (
    <mesh position={[0, 230, 260]} rotation-x={-Math.PI / 2}>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial
        attach={"material"}
        color="rgb(100, 100, 100)"
        opacity={"0.8"}
        transparent={true}
      />
    </mesh>
  );
};

export default Workpiece;
