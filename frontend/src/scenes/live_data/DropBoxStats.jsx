import { useDrop } from "react-dnd";
import { tokens } from "../../theme";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import { useState, useEffect } from "react";
import { Box, Button, useTheme } from "@mui/material";
import StatBox from "../../components/StatBox.jsx";
import Axios from "axios";
import { useQuery } from "@tanstack/react-query";

const DropBoxStats = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [boardContent, setBoardContent] = useState([]);

  const addCardToBoard = (item) => {
    item = [...item, generateRandomKey()];
    setBoardContent((boardContent) => [...boardContent, item]);
    console.log(boardContent.length);
  };

  const closeStatBox = (e) => {
    setBoardContent(boardContent.filter((content) => content[1] !== e));
    //setShowStatBox(false);
  };

  const generateRandomKey = () => Math.random().toString(16).slice(2);

  const [, drop] = useDrop(() => ({
    accept: "drag",
    drop: (item) => addCardToBoard(item),
    collect: (monitor) => ({
      isOver: !!monitor.isOver(),
    }),
  }));

  const fetchData = async () => {
    const response = await Axios.get("/debug/get-all");
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
    return <div>Error</div>;
  }

  return (
    <Box
      width="100%"
      height="100%"
      ref={drop}
      //backgroundColor={colors.indigoAccent[800]}
      display="grid"
      gridTemplateColumns="repeat(12, 1fr)"
      gap="20px"
      //boxShadow="inset 20px 20px 23px #1f2433, inset -20px -20px 23px #2b3045"
      borderRadius={"20px"}
    >
      {boardContent.map((e) => {
        return (
          <StatBox
            name={e[0].name}
            onClose={closeStatBox}
            category={e[0].category}
            readings={data.data}
            id={e[1]}
          />
        );
      })}
    </Box>
  );
};

export default DropBoxStats;

/* {showStatBox && (
  <StatBox
    name={measurementType}
    onClose={closeStatBox}
    category={category}
    readings={data.data}
  />
)}
{showStatBox && (
  <StatBox
    name={measurementType}
    onClose={closeStatBox}
    category={category}
    readings={data.data}
  />
)}
{showStatBox && (
  <StatBox
    name={measurementType}
    onClose={closeStatBox}
    category={category}
    readings={data.data}
  />
)}
{showStatBox && (
  <StatBox
    name={measurementType}
    onClose={closeStatBox}
    category={category}
    readings={data.data}
  />
)} */
