import { useDrop } from "react-dnd";
import DragAndDrop from "./DragAndDrop.jsx";
import { AuxiliaryList } from "../data/AuxiliaryList.js";
import { useState } from "react";
import { Box, Button, useTheme } from "@mui/material";
import StatBox from "./StatBox.jsx";

const DropBox = () => {
  const [showStatBox, setShowStatBox] = useState(false);
  const [measurementType, setMeasurementType] = useState(null);
  const [{ isOver }, drop] = useDrop(() => ({
    accept: "drag",
    drop: (item) => addCardToBoard(item.name),
    collect: (monitor) => ({
      isOver: !!monitor.isOver(),
    }),
  }));
  const addCardToBoard = (name) => {
    console.log(name);
    setMeasurementType(name);
    setShowStatBox(true);
  };
  const closeStatBox = () => {
    setShowStatBox(false);
  };
  return (
    <Box
      sx={{
        width: 300,
        height: 100,
        backgroundColor: "black",
      }}
      ref={drop}
    >
      {showStatBox && <StatBox name={measurementType} onClose={closeStatBox} />}
    </Box>
  );
};

export default DropBox;
