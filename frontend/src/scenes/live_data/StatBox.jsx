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
import DropDown from "../../components/DropDown.jsx";

const StatBox = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [title, setTitle] = useState("cnc");
  const [type, setType] = useState(["XCurrPos"]);
  const [text, setText] = useState("XCurrPos");
  const typographyRef = useRef(null);

  const handleGroupChange = (e) => {
    setTitle(e.target.value);
  };

  const handleTypeChange = (e) => {
    setText(e.target.value);
  };

  useEffect(() => {
    const table = datalist.find((obj) => obj.tablename === title);
    const tableKeys = Object.keys(table["columnnames"]);
    setType(tableKeys);
  }, [title]);

  return (
    <Box
      gridColumn="span 3"
      backgroundColor={colors.indigoAccent[900]}
      borderRadius={"15px"}
      padding="20px"
    >
      <Box display="flex" flexDirection={"row"} justifyContent="space-between">
        <FormControl size="small">
          <InputLabel id="test-select-label">Group</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            defaultValue={title}
            onChange={handleGroupChange}
            sx={{
              // width: 200,
              height: 30,
            }}
          >
            {datalist.map((item, index) => {
              return (
                <MenuItem value={item.tablename} key={index}>
                  {item.tablename}
                </MenuItem>
              );
            })}
          </Select>
        </FormControl>

        <FormControl size="small">
          <InputLabel id="test-select-label">Type</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            defaultValue={text}
            sx={{
              // width: 200,
              height: 30,
            }}
            onChange={handleTypeChange}
          >
            {type.map((item, index) => {
              return (
                <MenuItem value={item} key={index}>
                  {item}
                </MenuItem>
              );
            })}
          </Select>
        </FormControl>
      </Box>
      <Box display="flex">
        <Typography variant="h2" sx={{ color: colors.primary[500] }}>
          {String(props.readings[title][text.toLowerCase()])}
        </Typography>
      </Box>
    </Box>
  );
};

export default StatBox;
