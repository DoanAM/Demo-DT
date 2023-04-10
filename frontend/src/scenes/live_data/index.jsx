import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, useTheme, Typography } from "@mui/material";
import { tokens, RoutingContext } from "../../theme";
import CardHandler from "./CardHandler.jsx";
import LiveView3d from "./LiveView3d.jsx";
import Graphs from "./Graphs.jsx";
import LiveDataContext from "./LiveDataContext.jsx";
import { useScroll } from "@react-three/drei";
import LiveJson from "../../data/Live3D.json";
import MediaQuery from "react-responsive";

const Live_Data = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [liveData, setLiveData] = useState([]);
  const [counter, setCounter] = useState();
  const [counter2, setCounter2] = useState();
  const { currentSite, setCurrentSite } = useContext(RoutingContext);

  useEffect(() => {
    const startTime = new Date();
    startTime.setHours(10, 5, 0, 0); // set the starting time to 10:00:00.000

    const intervalId = setInterval(() => {
      const timeElapsed = Math.floor((new Date() - startTime) / 100) + 1;
      let miliseconds = timeElapsed % (LiveJson.length - 1);
      let seconds = Math.round((timeElapsed % (LiveJson.length - 1)) / 10);
      setCounter(miliseconds);
      setCounter2(seconds);
    }, 100);

    return () => clearInterval(intervalId);
  }, []);

  return (
    <LiveDataContext.Provider value={{ liveData, setLiveData }}>
      <Box m="20px">
        <Box height="13vh">
          {counter2 && <CardHandler counter={counter2} />}
        </Box>
        <Box
          width="100%"
          // backgroundColor={colors.indigoAccent[900]}
          mt={"20px"}
          display="flex"
          height={"70vh"}
        >
          <MediaQuery minWidth={1200}>
            {counter2 && <Graphs counter={counter2} />}
          </MediaQuery>
          {counter && <LiveView3d counter={counter} />}
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
