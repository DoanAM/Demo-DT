import { Box, Button, useTheme, Typography } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import StatBox from "../../components/StatBox.jsx";
import { useDrop } from "react-dnd";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import DropBox from "../../components/DropBox.jsx";
import DropBoxStats from "./DropBoxStats.jsx";
import LineChart from "../../components/LineChart.jsx";
import DropBoxGraphs from "./DropBoxGraphs.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  return (
    <Box m="20px">
      <Box height="120px" backgroundColor={colors.black[400]}>
        <DropBoxStats />
      </Box>
      <Box
        width="100%"
        backgroundColor={"#0F0F16"}
        mt={"20px"}
        display="flex"
        height={"60vh"}
      >
        <DropBoxGraphs height={"60vh"}></DropBoxGraphs>
        <Box
          sx={{
            width: "50%",
            display: "flex",
            justifyContent: "center",
            alignItems: "center",
            margin: "5px 5px 5px 0px",
            border: "2px solid #7A410D",
            borderRadius: "14px",
            boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
          }}
        >
          <Typography variant="h1">3D Model</Typography>
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
