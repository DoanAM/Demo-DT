import { Box, Button, useTheme, Typography } from "@mui/material";
import { useState, useContext, useEffect } from "react";
import { tokens, RoutingContext } from "../../theme";
import SimulationView3d from "./SimulationView3d.jsx";
import SimulationLoadHandler from "./SimulationLoadHandler.jsx";
import SimulationTable from "./SimulationTable.jsx";
import {
  SimulationDataContext,
  CurrentSimulationContext,
  PlaybackIdxContext,
} from "./Context.jsx";
import BoxGraphs from "./BoxGraphs.jsx";
import FileUploadBox from "./FileUploadBox.jsx";

//import DropBoxGraphs from "./DropBoxGraphs.jsx";

const Simulation = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [simulationData, setSimulationData] = useState([]);
  const [currentSimulationData, setCurrentSimulationData] = useState();
  const { currentSite, setCurrentSite } = useContext(RoutingContext);
  const [playbackIdx, setPlaybackIdx] = useState(0);

  useEffect(() => {
    setCurrentSite("simulation");
  }, []);

  return (
    <SimulationDataContext.Provider
      value={{ simulationData, setSimulationData }}
    >
      <Box m="20px">
        <Box display="flex" alignItems={"flex-start"} gap="40px">
          <Box width={"50%"} height="120px">
            <Typography variant="h3">Simulation Management</Typography>
            <FileUploadBox />
          </Box>
          <Box width="50%">
            <SimulationTable />
          </Box>
        </Box>
        <Box display="flex" flexDirection={"row"} paddingTop={"1vh"}>
          <CurrentSimulationContext.Provider
            value={{ currentSimulationData, setCurrentSimulationData }}
          >
            <PlaybackIdxContext.Provider
              value={{ playbackIdx, setPlaybackIdx }}
            >
              <SimulationView3d />
              <BoxGraphs />
            </PlaybackIdxContext.Provider>
          </CurrentSimulationContext.Provider>
        </Box>
      </Box>
    </SimulationDataContext.Provider>
  );
};

export default Simulation;
/* 
display="grid"
gridTemplateColumns="repeat(12, 1fr)"
gap="20px"
backgroundColor={colors.black[400]} */
