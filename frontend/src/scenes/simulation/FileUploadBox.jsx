import { Box, Button, useTheme, Typography, Slider } from "@mui/material";
import { useState } from "react";
import { tokens } from "../../theme";
import StatBox from "../../components/StatBox.jsx";
import { useDrop } from "react-dnd";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import DropBox from "../../components/DropBox.jsx";
//import DropBoxStats from "./DropBoxStats.jsx";
import LineChart from "../../components/LineChart.jsx";
//import DropBoxGraphs from "./DropBoxGraphs.jsx";
import axios from "axios";
import Cookies from "js-cookie";

const FileUploadBox = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [selectedFile, setSelectedFile] = useState();
  const [quality, setQuality] = useState(50);

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
      url: "/simulationAPI/upload-simulation",
      data: fd,
      xsrfHeaderName: "X-CSRFToken",
      xsrfCookieName: "csrftoken",
    }).then((res) => {
      console.log(res);
    });
    setSelectedFile(null);
  };

  /*   const handleQualityUpdate = (e, val) => {
    setQuality(val);
  }; */

  return (
    <Box>
      <Box display="flex" justifyContent={"flex-start"}>
        <Button variant="contained" component="label">
          Select File
          <input type="file" onChange={setFile} />
        </Button>
        <Button variant="contained" component="label" onClick={handleUpload}>
          Upload
        </Button>
      </Box>
      <Slider
        aria-label="Temperature"
        defaultValue={quality}
        valueLabelDisplay="auto"
        step={10}
        marks
        min={10}
        max={110}
        color="secondary"
        //onChange={handleQualityUpdate}
      />
    </Box>
  );
};
export default FileUploadBox;

//style={{ display: "None" }}
