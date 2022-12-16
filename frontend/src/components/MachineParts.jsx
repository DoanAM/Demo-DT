import pathMachineBedStl from "../data/MachineBed.stl";
import pathBridgeStl from "../data/Bridge.stl";
import pathXAxisStl from "../data/X-Axis.stl";
import pathSpindleStl from "../data/Spindle.stl";
import { useLoader } from "@react-three/fiber";
import { STLLoader } from "three/examples/jsm/loaders/STLLoader";

export const MachineBed = () => {
  const geom = useLoader(STLLoader, pathMachineBedStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach="material" color="rgb(77,78,102)" />
    </mesh>
  );
};

export const Bridge = () => {
  const geom = useLoader(STLLoader, pathBridgeStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(26, 71, 50)" />
    </mesh>
  );
};

export const XAxis = () => {
  const geom = useLoader(STLLoader, pathXAxisStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(47, 103, 193)" />
    </mesh>
  );
};

export const Spindle = () => {
  const geom = useLoader(STLLoader, pathSpindleStl);
  return (
    <mesh>
      <primitive object={geom} attach="geometry" />
      <meshPhongMaterial attach={"material"} color="rgb(228, 123, 37)" />
    </mesh>
  );
};
