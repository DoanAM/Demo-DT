import React, { Fragment, useState, useRef } from "react";
import { useDrag, useDrop } from "react-dnd";
import { Box, Typography, Button } from "@mui/material";

const DragAndDrop = ({ id, name }) => {
  const [{ isDragging }, drag] = useDrag(() => ({
    type: "drag",
    item: { id: id, name: name },
    collect: (monitor) => ({
      isDragging: !!monitor.isDragging(),
    }),
  }));
  return <Button ref={drag}>{name}</Button>;
};

export default DragAndDrop;
