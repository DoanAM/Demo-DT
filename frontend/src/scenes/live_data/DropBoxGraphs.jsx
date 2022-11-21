import { useDrop } from "react-dnd";
import { tokens } from "../../theme";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import { useState, useEffect } from "react";
import { Box, Button, useTheme } from "@mui/material";
import StatBox from "../../components/StatBox.jsx";
import LineChart from "../../components/LineChart.jsx";

const DropBoxGraphs = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [boardContent, setBoardContent] = useState([]);

  const addCardToBoard = (item) => {
    item = [...item, generateRandomKey()];
    setBoardContent((boardContent) => [...boardContent, item]);
    //console.log(boardContent.length);
  };

  const closeStatBox = (e) => {
    setBoardContent(boardContent.filter((content) => content[1] !== e));
    //setShowStatBox(false);
  };

  const generateRandomKey = () => Math.random().toString(16).slice(2);

  const [, drop] = useDrop(() => ({
    accept: "drag",
    drop: (item) => addCardToBoard(item),
    collect: (monitor) => ({
      isOver: !!monitor.isOver(),
    }),
  }));

  return (
    <Box
      width="100%"
      height="50vh"
      ref={drop}
      backgroundColor={colors.black[300]}
      display="grid"
      gridTemplateColumns="repeat(12, 1fr)"
      gap="20px"
    >
      {boardContent.map((e) => {
        return <LineChart onClose={closeStatBox} id={e[1]} />;
      })}
    </Box>
  );
};

export default DropBoxGraphs;
