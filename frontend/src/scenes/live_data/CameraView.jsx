import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, useTheme, Typography } from "@mui/material";
import { tokens, RoutingContext } from "../../theme";
import DropBoxStats from "./DropBoxStats.jsx";
import LiveView3d from "./LiveView3d.jsx";
import DropBoxGraphs from "./DropBoxGraphs.jsx";
import LiveDataContext from "./LiveDataContext.jsx";

const CameraView = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [showFallback, setShowFallback] = useState(false);

  return (
    <Box
      mt="50px"
      component="img"
      width="1000px"
      height="562px"
      src="http://10.42.3.15:44347/mjpg/video.mjpg?camera=1"
      onError={() => setShowFallback(true)}
    ></Box>
  );
};

export default CameraView;
/* 
display="grid"
gridTemplateColumns="repeat(12, 1fr)"
gap="20px"
backgroundColor={colors.black[400]} */
