import { Box, Button, useTheme, Typography } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import StatBox from "../../components/StatBox.jsx";
import { useDrop } from "react-dnd";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import SimulationView3d from "./SimulationView3d.jsx";
import FileUploadBox from "./FileUploadBox.jsx";
import SimulationTable from "./SimulationTable.jsx";
import SimulationDataContext from "./SimulationDataContext.jsx";
//import DropBoxGraphs from "./DropBoxGraphs.jsx";

const Simulation = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [simulationData, setSimulationData] = useState([]);

  const handleUpload = (e) => {
    //console.log(e.target.value);
    console.log(e.target.files);
  };

  return (
    <SimulationDataContext.Provider
      value={{ simulationData, setSimulationData }}
    >
      <Box>
        <Box m="20px" display="flex" alignItems={"flex-start"} gap="20px">
          <Box width={"50%"} height="120px">
            <Typography variant="h3">Simulation Management</Typography>
            <FileUploadBox />
          </Box>
          <Box width="50%">
            <SimulationTable />
          </Box>
        </Box>
        <SimulationView3d />
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
