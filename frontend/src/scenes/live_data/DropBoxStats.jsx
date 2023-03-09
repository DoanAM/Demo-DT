import { tokens } from "../../theme";

import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import { useState, useEffect, useRef, useContext } from "react";
import { Box, Button, useTheme } from "@mui/material";
import StatBox from "./StatBox.jsx";
import Axios from "axios";
import { useQuery } from "@tanstack/react-query";
import LiveDataContext from "./LiveDataContext.jsx";

const DropBoxStats = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [boardContent, setBoardContent] = useState([]);
  const stateRef = useRef();
  stateRef.boardContentLength = boardContent.length;
  const { liveData, setLiveData } = useContext(LiveDataContext);

  const generateRandomKey = () => Math.random().toString(16).slice(2);

  const fetchData = async () => {
    const response = await Axios.get("/debug/get-all");
    //console.log(response);
    // setLiveData({
    //   xcurrpos: response.data.cnc.xcurrpos,
    //   ycurrpos: response.data.cnc.ycurrpos,
    //   zcurrpos: response.data.cnc.zcurrpos,
    // });
    return response;
  };

  const { status, data } = useQuery({
    queryKey: ["currentData"],
    queryFn: fetchData,
    refetchInterval: 1000,
  });

  if (status === "loading") {
    return <div>Loading...</div>;
  }

  if (status === "error") {
    return <div>Error cannot connect to database</div>;
  }

  return (
    <Box
      width="100%"
      height="100%"
      display="grid"
      gridTemplateColumns="repeat(12, 1fr)"
      gap="20px"
      borderRadius={"20px"}
    >
      <StatBox readings={data.data} />
      <StatBox readings={data.data} />
      <StatBox readings={data.data} />
      <StatBox readings={data.data} />
    </Box>
  );
};

export default DropBoxStats;
