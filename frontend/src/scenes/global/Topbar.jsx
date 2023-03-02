import { Box, Button, IconButton, Typography, useTheme } from "@mui/material";
import { useContext } from "react";
import { ColorModeContext, tokens } from "../../theme";
import { Link } from "react-router-dom";
import InputBase from "@mui/material/InputBase";
import LightModeOutlinedIcon from "@mui/icons-material/LightModeOutlined";
import DarkModeOutlinedIcon from "@mui/icons-material/DarkModeOutlined";
import AICom_Logo_2021 from "../../data/AICom_Logo_2021.png";

const Topbar = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const colorMode = useContext(ColorModeContext);
  return (
    <Box
      width={"100vw"}
      display="flex"
      justifyContent="flex-end"
      p={2}
      gap="152px"
      alignItems={"center"}
    >
      <Box>
        <IconButton onClick={colorMode.toggleColorMode}>
          {theme.palette.mode === "dark" ? (
            <DarkModeOutlinedIcon />
          ) : (
            <LightModeOutlinedIcon />
          )}
        </IconButton>
      </Box>
      {/* <Typography variant="h4">Save View</Typography> */}
      <Button
        variant="text"
        to="/home"
        component={Link}
        sx={{
          fontSize: "20px",
          color: colors.black[100],
          textTransform: "none",
        }}
      >
        Live Data
      </Button>
      <Button
        variant="text"
        to="/simulation"
        component={Link}
        sx={{
          fontSize: "20px",
          color: colors.black[100],
          textTransform: "none",
        }}
      >
        Simulation
      </Button>
      <Box height={"50px"} component="img" alt="Logo" src={AICom_Logo_2021} />
      {/* <Button
        variant="text"
        sx={{
          fontSize: "20px",
          color: colors.black[100],
          textTransform: "none",
        }}
      >
        My Account
      </Button> */}
    </Box>
  );
};

export default Topbar;
