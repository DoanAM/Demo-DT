import { tokens } from "../../theme";
import { useState, useEffect, useRef } from "react";
import { Box, Button, useTheme } from "@mui/material";
import LineChartHandler from "./LineChartHandler.jsx";

const Graphs = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [boardContent, setBoardContent] = useState([]);
  const stateRef = useRef();
  stateRef.boardContentLength = boardContent.length;

  return (
    <Box
      width="50%"
      height="100%"
      marginRight="5px"
      // backgroundColor={colors.indigoAccent[900]}
      gap="5px"
      display="flex"
      flexDirection={"column"}
      justifyContent={"space-between"}
    >
      {/* {boardContent.map((e) => {
        return (
          <LineChart
            onClose={closeStatBox}
            id={e[1]}
            category={e[0].category}
            name={e[0].name}
          />
        );
      })} */}
      <LineChartHandler name="1" />
      <LineChartHandler />
      <LineChartHandler />
    </Box>
  );
};

export default Graphs;
