import { Box, Button, useTheme, Typography } from "@mui/material";
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
  //const csrftoken = Cookies.get("csrftoken");
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [selectedFile, setSelectedFile] = useState();

  const handleUpload = (e) => {
    //console.log(e.target.value);
    setSelectedFile(e.target.files[0]);
    const fd = new FormData();
    fd.append("cover", selectedFile);
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
  };
  return (
    <Button variant="contained" component="label">
      Upload
      <input style={{ display: "None" }} type="file" onChange={handleUpload} />
    </Button>
  );
};
export default FileUploadBox;
