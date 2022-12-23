import { Box, Button, useTheme, Typography, IconButton } from "@mui/material";
import { useState, useContext, useEffect } from "react";
import AddIcon from "@mui/icons-material/Add";
import LineChartsimulation from "./LineChartSimulation.jsx";
import CurrentSimulationContext from "./CurrentSimulationContext.jsx";

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
        //border: "2px solid #7A410D",
        borderRadius: "14px",
        //boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <IconButton
        style={{ borderRadius: 0 }}
        onClick={addCardToBox}
        disabled={currentSimulationData == undefined}
      >
        <AddIcon />
      </IconButton>
      <Box gap="5px" display="flex" flexDirection={"column"} height="100%">
        {boxContent.map((e) => {
          return (
            <LineChartsimulation onClose={closeStatBox} id={e[1]} key={e[1]} />
          );
        })}
      </Box>
    </Box>
  );
};

export default BoxGraphs;
