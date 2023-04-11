import React from "react";
import { useState, useEffect, useContext, useRef } from "react";
import * as THREE from "three";
import Axios from "axios";
import { Canvas } from "@react-three/fiber";
import { useQuery } from "@tanstack/react-query";
import { OrbitControls, Html, useProgress } from "@react-three/drei";
import {
  Box,
  FormControl,
  Select,
  MenuItem,
  InputLabel,
  Typography,
  useTheme,
  LinearProgress,
} from "@mui/material";
import MxCube from "../../components/MxCube.jsx";
import Path from "../../components/Line.jsx";
import { useMediaQuery } from "react-responsive";
import { colorMapper, sleep, Loader } from "../../components/Utilities.jsx";
import { LineColorVariables_LiveData } from "../../data/LineColorVariables.js";
import { tokens, RoutingContext } from "../../theme";
import LiveJson from "../../data/MachineCoordinates.json";

import LineCoordinates from "../../data/LineCoordinates.json";
import RGB_XFollDist from "../../data/RGB_XFollDist.json";
import RGB_YFollDist from "../../data/RGB_YFollDist.json";
import RGB_ZFollDist from "../../data/RGB_ZFollDist.json";

const types = [
  { key: "XFollDist", name: "X Error", min: "-2.16", max: "2.05" },
  { key: "YFollDist", name: "Y Error", min: "3.46", max: "3.90" },
  { key: "ZFollDist", name: "Z Error", min: "-4.42", max: "4.25" },
];

const LiveView3d = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [positionMachine, setPositionMachine] = useState({
    xcurrpos: 0,
    ycurrpos: 0,
    zcurrpos: 0,
  });
  const [lineArray, setLineArray] = useState();
  const [lineVariable, setLineVariable] = useState("XFollDist");
  const [lineColors, setLineColors] = useState();
  const selectedType = types.find((item) => item.key === lineVariable);

  useEffect(() => {
    if (props.counter !== null) {
      const slicedData = LiveJson[props.counter];
      setPositionMachine({
        xcurrpos: slicedData.XCurrPos,
        ycurrpos: slicedData.YCurrPos,
        zcurrpos: slicedData.ZCurrPos,
      });
      setLineArray(LineCoordinates.slice(0, props.counter));
      setLineColors(RGB_XFollDist.slice(0, props.counter));
    }
  }, [props.counter]);

  useEffect(() => {
    if (props.counter !== null) {
      if (lineVariable == "XFollDist") {
        setLineColors(RGB_XFollDist.slice(0, props.counter));
      }
      if (lineVariable == "YFollDist") {
        setLineColors(RGB_YFollDist.slice(0, props.counter));
      }
      if (lineVariable == "ZFollDist") {
        setLineColors(RGB_ZFollDist.slice(0, props.counter));
      }
    }
  }, [props.counter, lineVariable]);

  const handleSelectChange = (e) => {
    setLineVariable(e.target.value);
  };

  const barStyle = {
    borderRadius: 10,
    background: "linear-gradient(to right, #00FF00, #0000FF)",
    height: 20,
    width: 100,
  };
  const isDesktopOrLaptop = useMediaQuery({
    query: "(min-width: 1224px)",
  });
  const isTabletOrMobile = useMediaQuery({ query: "(max-width: 1224px)" });
  return (
    <Box
      sx={{
        backgroundColor: colors.indigoAccent[900],
        width: isDesktopOrLaptop ? "50%" : "95%",
        display: "flex",
        flexDirection: "column",
        justifyContent: "center",
        alignItems: "center",
        paddingTop: "15px",
        paddingRight: "5px",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <FormControl>
        <InputLabel id="test-select-label">Highlight Value</InputLabel>
        <Select
          labelId="test-select-label"
          label="Time"
          value={lineVariable}
          sx={{
            width: 200,
            height: 30,
          }}
          onChange={handleSelectChange}
        >
          {types.map((item, index) => {
            return (
              <MenuItem value={item.key} key={index}>
                {item.name}
              </MenuItem>
            );
          })}
        </Select>
      </FormControl>
      <Box display={"flex"} paddingTop={"2px"} paddingBottom={"2px"}>
        <Typography style={{ left: 0 }}>{selectedType.min}mm</Typography>
        <Box style={barStyle} marginLeft={"3px"} marginRight={"3px"} />
        <Typography style={{ right: 0 }}>{selectedType.max}mm</Typography>
      </Box>
      <Canvas
        camera={{
          position: [0, 1300, 1500],
          far: 10000,
        }}
        gl={{ localClippingEnabled: true }}
      >
        <React.Suspense fallback={<Loader />}>
          {/* <axesHelper args={[1000]} /> */}
          <OrbitControls />
          <hemisphereLight
            color="rgb(242,247,253)"
            groundColor={"rgb(191,191,191)"}
            intensity={1.1}
          />
          <directionalLight position={[5, 575, 2265]} />
          <pointLight position={[0, 756, -2243]} />
          {/* {lineArray.map((e) => {
            return (
              <Line
                points={e.vectors}
                color={e.color}
                displayColor={lineVariable}
              />
            );
          })} */}
          {lineArray && lineColors && (
            <Path points={lineArray} rgb={lineColors} />
          )}

          <MxCube
            bridgePosition={-positionMachine.ycurrpos}
            xAxisPosition={positionMachine.xcurrpos}
            spindlePosition={positionMachine.zcurrpos}
            toolDiameter={10}
            toolLength={25}
          />
        </React.Suspense>
      </Canvas>
    </Box>
  );
};

export default LiveView3d;
