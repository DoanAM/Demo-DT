import { Box, Button, useTheme, Typography } from "@mui/material";

import { tokens } from "../../theme";

import DropBoxStats from "./DropBoxStats.jsx";
import LiveView3d from "./LiveView3d.jsx";

import DropBoxGraphs from "./DropBoxGraphs.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  return (
    <Box m="20px">
      <Box height="120px">
        <DropBoxStats />
      </Box>
      <Box
        width="100%"
        backgroundColor={colors.indigoAccent[900]}
        mt={"20px"}
        display="flex"
        height={"70vh"}
      >
        <DropBoxGraphs height={"60vh"}></DropBoxGraphs>
        <LiveView3d />
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
