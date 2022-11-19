import React, { Fragment, useState, useRef } from "react";
import { useDrag, useDrop } from "react-dnd";
import { Box, Typography, Button } from "@mui/material";
import { MenuItem } from "react-pro-sidebar";

const DragAndDrop = ({ id, name, category }) => {
  const [{ isDragging }, drag] = useDrag(() => ({
    type: "drag",
    item: [
      {
        name: name,
        category: category,
      },
    ],
    collect: (monitor) => ({
      isDragging: !!monitor.isDragging(),
    }),
  }));
  return <Button ref={drag}>{name}</Button>;
};

export default DragAndDrop;
