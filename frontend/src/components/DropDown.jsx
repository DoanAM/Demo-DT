import { FormControl, Select, InputLabel, MenuItem } from "@mui/material";

const DropDown = (props) => {
  <FormControl size="small">
    <InputLabel id="test-select-label">Group</InputLabel>
    <Select
      labelId="test-select-label"
      label="Time"
      defaultValue={props.defaultValue}
      onChange={props.onChange}
      sx={{
        // width: 200,
        height: 30,
      }}
    >
      {props.arrayToMap.map((item, index) => {
        return (
          <MenuItem value={item[props.menuItem]} key={index}>
            {item[props.menuItem]}
          </MenuItem>
        );
      })}
    </Select>
  </FormControl>;
};

export default DropDown;
