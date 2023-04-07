import { Button, useTheme } from "@mui/material";
import { tokens } from "../../theme";
import { SimulationDataContext } from "./Context.jsx";

const SimulationLoadHandler = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  return (
    <Button
      disabled={!props.finished}
      width="30px"
      sx={{ color: colors.orangeAccent[300] }}
    >
      {props.finished ? "Load" : "Not Finished"}
    </Button>
  );
};

export default SimulationLoadHandler;
