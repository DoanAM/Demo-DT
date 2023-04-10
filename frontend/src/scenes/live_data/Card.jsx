import {
  Box,
  Typography,
  useTheme,
  FormControl,
  Select,
  InputLabel,
  MenuItem,
} from "@mui/material";
import { useState, useEffect, useRef } from "react";
import { tokens } from "../../theme";
import datalist from "../../data/datalist.json";

const types = [
  { key: "XCurrPos", name: "X Position", unit: "mm" },
  { key: "YCurrPos", name: "Y Position", unit: "mm" },
  { key: "ZCurrPos", name: "Z Position", unit: "mm" },
  { key: "XFollDist", name: "X Error", unit: "mm" },
  { key: "YFollDist", name: "Y Error", unit: "mm" },
  { key: "ZFollDist", name: "Z Error", unit: "mm" },
  { key: "Programname", name: "Programname", unit: "" },
];

const Card = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [title, setTitle] = useState("cnc");
  const [type, setType] = useState(props.defaultValue);
  const selectedType = types.find((item) => item.key === type);
  const typographyRef = useRef(null);

  const handleTypeChange = (e) => {
    setType(e.target.value);
  };

  return (
    <Box
      width={"100%"}
      //gridColumn="span 3"
      backgroundColor={colors.indigoAccent[900]}
      borderRadius={"15px"}
      padding="20px"
      boxShadow="4px 2px 15px rgba(122, 65, 13, 0.29)"
      border="2px solid #7A410D"
    >
      <FormControl size="small">
        <InputLabel id="test-select-label">Value</InputLabel>
        <Select
          labelId="test-select-label"
          label="Time"
          value={type}
          sx={{
            // width: 200,
            height: 30,
          }}
          onChange={handleTypeChange}
        >
          {types.map((item, index) => {
            return (
              <MenuItem value={item.key} key={item.index}>
                {item.name}
              </MenuItem>
            );
          })}
        </Select>
      </FormControl>

      <Box display="flex">
        <Typography
          variant="h2"
          sx={{ color: colors.primary[500] }}
          typography={{ fontSize: "clamp(16px, 3vw, 25px)" }}
        >
          {props.readings && props.readings[type]}{" "}
          {props.readings && selectedType.unit}
        </Typography>
      </Box>
    </Box>
  );
};

export default Card;
