import { Box, Button, useTheme } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import StatBox from "../../components/StatBox.jsx";
import { useDrop } from "react-dnd";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import DropBox from "../../components/DropBox.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  return (
    <Box m="20px">
      <Box
        display="grid"
        gridTemplateColumns="repeat(12, 1fr)"
        gridAutoRows="140px"
        gap="20px"
      >
        {/* ROW 1 */}
        <Box
          gridColumn="span 3"
          backgroundColor={colors.black[400]}
          display="flex"
          alignItems="center"
          justifyContent="center"
        >
          <DropBox />
        </Box>
        <Box
          gridColumn="span 3"
          backgroundColor={colors.black[400]}
          display="flex"
          alignItems="center"
          justifyContent="center"
        >
          <DropBox />
          {/* <StatBox /> */}
        </Box>
        <Box
          gridColumn="span 3"
          backgroundColor={colors.black[400]}
          display="flex"
          alignItems="center"
          justifyContent="center"
        >
          <DropBox />
          {/* <StatBox /> */}
        </Box>
        <Box
          gridColumn="span 3"
          backgroundColor={colors.black[400]}
          display="flex"
          alignItems="center"
          justifyContent="center"
        >
          <DropBox />
          {/* <StatBox /> */}
        </Box>
      </Box>
    </Box>
  );
};

export default Live_Data;
