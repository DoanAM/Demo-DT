import { tokens } from "../../theme";

import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, Typography, useTheme } from "@mui/material";
import Card from "./Card.jsx";
import Axios from "axios";
import { useQuery } from "@tanstack/react-query";
import LiveDataContext from "./LiveDataContext.jsx";
import LiveJson from "../../data/Live.json";

const CardHandler = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [boardContent, setBoardContent] = useState([]);
  const stateRef = useRef();
  stateRef.boardContentLength = boardContent.length;
  const { liveData, setLiveData } = useContext(LiveDataContext);
  //const [counter, setCounter] = useState(null);
  const [currData, setCurrData] = useState();

  // useEffect((props) => {
  //   const startTime = new Date();
  //   startTime.setHours(8, 0, 0, 0); // set the starting time to 08:00:00.000

  //   const intervalId = setInterval(() => {
  //     const timeElapsed = Math.floor((new Date() - startTime) / 1000) + 1;
  //     setCounter(timeElapsed % (LiveJson.length - 1));
  //   }, 1000);

  //   return () => clearInterval(intervalId);
  // }, []);

  useEffect(() => {
    setCurrData(LiveJson[props.counter]);
  }, [props.counter, LiveJson]);

  return (
    <Box
      width="100%"
      height="100%"
      display="grid"
      gridTemplateColumns="repeat(12, 1fr)"
      gap="20px"
      borderRadius={"20px"}
    >
      <Card readings={currData} />
      <Card readings={currData} />
      <Card readings={currData} />
      <Card readings={currData} />
    </Box>
  );
};

export default CardHandler;
