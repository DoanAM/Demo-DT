import {Box, Button, Typography, useTheme} from "@mui/material";
import { useContext } from "react"
import {ColorModeContest, ColorModeContext, tokens} from "../../theme";
import InputBase from "@mui/material";

const Topbar = () => {
    const theme = useTheme();
    const colors = tokens(theme.palette.mode);
    const colorMode = useContext(ColorModeContext);
    return (
        <Box display="flex" justifyContent ="space-between" p={2} gap="152px">
            <Button variant="text" size="large">SaveView</Button>
            <Button variant="text" size="large">LiveData</Button>
            <Button variant="text" size="large">Simulation</Button>
            <Button variant="text" size="large">My Account</Button>
        </Box>
    )
}

export default Topbar;