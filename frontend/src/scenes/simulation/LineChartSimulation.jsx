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
import { useState, useContext, useEffect, useRef } from "react";
import CloseOutlinedIcon from "@mui/icons-material/CloseOutlined";
import { CurrentSimulationContext } from "./Context.jsx";
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
  const chartRef = useRef();

  const close = () => {
    props.onClose(props.id);
  };
  const handleChange = (event) => {
    setAge(event.target.value);
  };

  const options = {
    responsive: true,
    maintainAspectRatio: false,
    plugins: {
      legend: {
        display: false,
      },
    },
    layout: {
      padding: 0,
    },
    elements: {
      point: {
        pointStyle: false,
      },
    },
    interaction: {
      mode: "index",
      intersect: false,
    },
    tooltips: {
      enabled: true,
      mode: "index",
      intersect: false,
    },
  };

  const normalizedTimestampArray = (data) => {
    const timestampArray = Object.values(data).map((obj) => obj.timestamp);
    const initVal = timestampArray[0];
    const normalizedArray = timestampArray.map((e) => e - initVal);
    return normalizedArray;
  };

  const labels = normalizedTimestampArray(currentSimulationData);

  const data = {
    labels,
    datasets: [
      {
        data: Object.values(currentSimulationData).map((obj) => obj[age]),
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.5)",
      },
    ],
  };

  const triggerTooltip = (chart) => {
    const tooltip = chart.tooltip;
    if (tooltip.getActiveElements().length > 0) {
      tooltip.setActiveElements([], { x: 0, y: 0 });
    } else {
      const chartArea = chart.chartArea;
      tooltip.setActiveElements(
        [
          {
            datasetIndex: 0,
            index: 2,
          },
          {
            datasetIndex: 1,
            index: 2,
          },
        ],
        {
          x: (chartArea.left + chartArea.right) / 2,
          y: (chartArea.top + chartArea.bottom) / 2,
        }
      );
    }

    chart.update();
  };

  return (
    <Box
      sx={{
        height: "50%",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
        display: "flex",
        flexDirection: "column",
      }}
    >
      <Box mr="5px">
        <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
      </Box>
      <FormControl fullWidth>
        <InputLabel id="demo-simple-select-label">Category</InputLabel>
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
      <Box display={"flex"} height={"100%"}>
        <Line ref={chartRef} options={options} data={data} />
      </Box>
    </Box>
  );
};

export default LineChartsimulation;
