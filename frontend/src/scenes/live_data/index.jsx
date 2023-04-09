import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, useTheme, Typography } from "@mui/material";
import { tokens, RoutingContext } from "../../theme";
import CardHandler from "./CardHandler.jsx";
import LiveView3d from "./LiveView3d.jsx";
import Graphs from "./Graphs.jsx";
import LiveDataContext from "./LiveDataContext.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [liveData, setLiveData] = useState([]);

  const { currentSite, setCurrentSite } = useContext(RoutingContext);
  const startTime = new Date();
  startTime.setHours(8, 0, 0, 0); // set the starting time to 08:00:00.000

  return (
    <LiveDataContext.Provider value={{ liveData, setLiveData }}>
      <Box m="20px">
        <Box height="13vh">
          <CardHandler />
        </Box>
        <Box
          width="100%"
          // backgroundColor={colors.indigoAccent[900]}
          mt={"20px"}
          display="flex"
          height={"70vh"}
        >
          <Graphs />
          <LiveView3d />
        </Box>
      </Box>
    </LiveDataContext.Provider>
  );
};

export default Live_Data;
/* 
display="grid"
gridTemplateColumns="repeat(12, 1fr)"
gap="20px"
backgroundColor={colors.black[400]} */
