import { Box, Button, useTheme, Typography, Slider } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import axios from "axios";

const FileUploadBox = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [selectedFile, setSelectedFile] = useState();
  const [quality, setQuality] = useState(0.5);

  const setFile = (e) => {
    setSelectedFile(e.target.files[0]);
    console.log(selectedFile);
  };

  const handleUpload = (e) => {
    //console.log(e.target.value);
    const fd = new FormData();
    fd.append("nc_file", selectedFile);
    console.log("fd is", fd);

    axios({
      method: "POST",
      url: `/simulation-API/upload-simulation/?precision=${quality}`,
      data: fd,
      xsrfHeaderName: "X-CSRFToken",
      xsrfCookieName: "csrftoken",
    }).then((res) => {
      console.log(res);
    });
  };

  const handleQualityUpdate = (e, val) => {
    setQuality(val);
  };

  return (
    <Box>
      <Box display="flex" justifyContent={"flex-start"}>
        <Button variant="contained" component="label">
          <input type="file" accept=".nc" onChange={setFile} />
        </Button>
        <Button variant="contained" component="label" onClick={handleUpload}>
          Upload
        </Button>
      </Box>
      <Slider
        //key={`slider-${quality}`}
        aria-label="Precision"
        value={quality}
        valueLabelDisplay="auto"
        step={0.1}
        marks
        min={0.1}
        max={5}
        color="secondary"
        onChange={handleQualityUpdate}
      />
    </Box>
  );
};
export default FileUploadBox;

//style={{ display: "None" }}
