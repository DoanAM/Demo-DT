import { Box, Button, useTheme, Typography, IconButton } from "@mui/material";
import { useState, useContext, useEffect } from "react";
import AddIcon from "@mui/icons-material/Add";
import LineChartsimulation from "./LineChartSimulation.jsx";
import { CurrentSimulationContext } from "./Context.jsx";

const BoxGraphs = () => {
  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );
  const [boxContent, setBoxContent] = useState([]);

  const addCardToBox = () => {
    const item = generateRandomKey();
    setBoxContent((boxContent) => [...boxContent, item]);
  };

  const closeStatBox = (e) => {
    setBoxContent(boxContent.filter((content) => content[1] !== e));
    //setShowStatBox(false);
  };

  const generateRandomKey = () => Math.random().toString(16).slice(2);

  return (
    <Box
      sx={{
        width: "50%",
        height: "55vh",
        paddingLeft: "15px",
        display: "flex",
        flexDirection: "column",
        justifyContent: "space-between",
        borderRadius: "14px",
      }}
    >
      <LineChartsimulation id={1} key={1} defaultValue={"XCurrPos"} />
      <LineChartsimulation id={2} key={2} defaultValue={"YCurrPos"} />
    </Box>
  );
};

export default BoxGraphs;
