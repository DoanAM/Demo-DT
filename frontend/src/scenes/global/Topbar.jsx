import { Box, Button, Typography, useTheme } from "@mui/material";
import { useContext } from "react";
import { ColorModeContest, ColorModeContext, tokens } from "../../theme";
import InputBase from "@mui/material";

const Topbar = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const colorMode = useContext(ColorModeContext);
  return (
    <Box display="flex" justifyContent="space-between" p={2} gap="152px">
      <Typography variant="h4">Simulation</Typography>
      <Typography variant="h4">Live Data</Typography>
      <Typography variant="h4">Save View</Typography>
      <Typography variant="h4">My Account</Typography>
    </Box>
  );
};

export default Topbar;
