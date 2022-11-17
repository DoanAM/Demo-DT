import { Box, Typography, useTheme, Button } from "@mui/material";
import { useState, useEffect } from "react";
import { tokens } from "../theme";
import Axios from "axios";

const StatBox = (props) => {
  const requestString = props.name.toLowerCase();
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [value, setValue] = useState(null);

  useEffect(() => {
    async function getData() {
      const request = await Axios.get("/debug/get-auxiliary");
      setValue(request.data[requestString]);
      console.log("Value is: ", value);
    }
    const refreshIntervalId = setInterval(() => {
      getData();
    }, 1000);
    return () => {
      clearInterval(refreshIntervalId);
      console.log("Component Unmounted");
    };
  });

  return (
    <Box width="100%">
      <Button onClick={props.onClose}>X</Button>
      <Box width="100%" flex-direction="column" justifyContent="flex-start">
        <Box>
          <Typography variant="h5" sx={{ color: colors.black[100] }}>
            {props.name}
          </Typography>
        </Box>
        <Box>
          <Typography
            variant="h4"
            fontWeight="bold"
            sx={{ color: colors.black[100] }}
          >
            {String(value)}
          </Typography>
        </Box>
      </Box>
    </Box>
  );
};

export default StatBox;
