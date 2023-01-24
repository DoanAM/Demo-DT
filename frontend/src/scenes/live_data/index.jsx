import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, useTheme, Typography } from "@mui/material";
import { tokens, RoutingContext } from "../../theme";
import DropBoxStats from "./DropBoxStats.jsx";
import LiveView3d from "./LiveView3d.jsx";
import DropBoxGraphs from "./DropBoxGraphs.jsx";
import LiveDataContext from "./LiveDataContext.jsx";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [liveData, setLiveData] = useState([]);
  const { currentSite, setCurrentSite } = useContext(RoutingContext);

  useEffect(() => {
    setCurrentSite("live_data");
    console.log("Live_data is set");
  }, []);

  return (
    <LiveDataContext.Provider value={{ liveData, setLiveData }}>
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
        <Box
          component="img"
          width="1000px"
          height="562px"
          src="http://10.42.3.15:44347/mjpg/video.mjpg?camera=1"
        ></Box>
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
