import {
  Box,
  Button,
  useTheme,
  Typography,
  IconButton,
  FormControl,
  InputLabel,
  Select,
  MenuItem,
} from "@mui/material";
import { useState, useContext, useEffect } from "react";
import CloseOutlinedIcon from "@mui/icons-material/CloseOutlined";
import CurrentSimulationContext from "./CurrentSimulationContext.jsx";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const LineChartsimulation = (props) => {
  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );
  const [age, setAge] = useState("");

  const keys = Object.keys(currentSimulationData[0]);

  const close = () => {
    props.onClose(props.id);
  };
  const handleChange = (event) => {
    setAge(event.target.value);
  };

  const options = {
    responsive: true,
    plugins: {
      legend: {
        position: "top",
      },
      title: {
        display: true,
        text: "Chart.js Line Chart",
      },
    },
  };

  const labels = Object.values(currentSimulationData).map(
    (obj) => obj.timestamp
  );

  const data = {
    labels,
    datasets: [
      {
        label: "Dataset 1",
        data: Object.values(currentSimulationData).map((obj) => obj[age]),
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.5)",
      },
    ],
  };

  return (
    <Box
      sx={{
        height: "33%",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <Box mr="5px">
        <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
      </Box>
      <FormControl fullWidth>
        <InputLabel id="demo-simple-select-label">Age</InputLabel>
        <Select
          labelId="demo-simple-select-label"
          id="demo-simple-select"
          value={age}
          label="Value"
          onChange={handleChange}
        >
          {keys.map((e) => {
            return <MenuItem value={e}> {e} </MenuItem>;
          })}
        </Select>
      </FormControl>
      <Line options={options} data={data} />
    </Box>
  );
};

export default LineChartsimulation;
