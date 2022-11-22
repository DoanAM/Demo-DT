import { Box, Typography, useTheme, Button } from "@mui/material";
import { useState, useEffect } from "react";
import { tokens } from "../theme";
import CloseOutlinedIcon from "@mui/icons-material/CloseOutlined";

const StatBox = (props) => {
  /* const requestString = props.name.toLowerCase(); */
  const title = props.name.toLowerCase();
  const type = props.category;
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  //console.log(title);
  const [value, setValue] = useState("loading");
  const close = () => {
    props.onClose(props.id);
  };

  return (
    <Box
      gridColumn="span 3"
      //m="0 30px"
      backgroundColor={colors.black[400]}
      borderRadius={"15px"}
      padding="20px"
    >
      <Box display="flex" justifyContent="space-between">
        <Box>
          <Typography variant="h5" sx={{ color: colors.black[100] }}>
            {props.name}
          </Typography>
        </Box>
        <Box mr="5px">
          <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
        </Box>
      </Box>
      <Box display="flex">
        <Typography variant="h1" sx={{ color: colors.primary[500] }}>
          {String(props.readings[type][title])}
        </Typography>
      </Box>
    </Box>
  );
};

export default StatBox;
