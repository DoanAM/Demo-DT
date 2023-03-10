import { Html, useProgress } from "@react-three/drei";

export const Loader = () => {
  const { progress } = useProgress();
  return <Html center>{progress} % loaded</Html>;
};

export function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

/// Maps a value between min and max to a new range between newMin and newMax
function normalize(value, min, max, newMin, newMax) {
  return Math.round(((value - min) / (max - min)) * (newMax - newMin) + newMin);
}

function rgbToHex(r, g, b) {
  const rHex = r.toString(16).padStart(2, "0");
  const gHex = g.toString(16).padStart(2, "0");
  const bHex = b.toString(16).padStart(2, "0");
  return "#" + rHex + gHex + bHex;
}

export function colorMapper(value, min, max) {
  const red = normalize(value, min, max, 0, 255);
  const green = 255 - normalize(value, min, max, 0, 255);
  return rgbToHex(red, green, 0);
}
