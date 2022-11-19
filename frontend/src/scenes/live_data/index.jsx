import { Box, Button, useTheme } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import StatBox from "../../components/StatBox.jsx";
import { useDrop } from "react-dnd";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import DropBox from "../../components/DropBox.jsx";
import DropBoxStats from "./DropBoxStats.jsx";
import LineChart from "../../components/LineChart.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  return (
    <Box m="20px">
      <Box height="120px" backgroundColor={colors.black[400]}>
        <DropBoxStats />
      </Box>
      <Box width="100%" backgroundColor={"#0E1317"} mt={"20px"}>
        <Box height="50vh">
          <LineChart />
        </Box>
      </Box>
    </Box>
  );
};

export default Live_Data;
/* 
display="grid"
gridTemplateColumns="repeat(12, 1fr)"
gap="20px"
backgroundColor={colors.black[400]} */
