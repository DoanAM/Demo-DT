import { Box, Button, useTheme, Typography, Slider } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";

const FileUploadBox = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [selectedFile, setSelectedFile] = useState();

  return (
    <Box>
      <Box display="flex" justifyContent={"flex-start"}>
        <Button variant="contained" component="label">
          Upload
        </Button>
      </Box>
      <Slider
        aria-label="Precision"
        valueLabelDisplay="auto"
        step={0.1}
        marks
        min={0.1}
        max={5}
        color="secondary"
      />
    </Box>
  );
};
export default FileUploadBox;

//style={{ display: "None" }}
