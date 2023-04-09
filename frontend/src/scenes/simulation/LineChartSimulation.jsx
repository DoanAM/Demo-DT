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
import { tokens } from "../../theme";
import CloseOutlinedIcon from "@mui/icons-material/CloseOutlined";
import { CurrentSimulationContext, PlaybackIdxContext } from "./Context.jsx";
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
import SimulationJSON from "../../data/Simulation.json";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);
const types = [
  { key: "XCurrPos", name: "X Position", unit: "mm" },
  { key: "YCurrPos", name: "Y Position", unit: "mm" },
  { key: "ZCurrPos", name: "Z Position", unit: "mm" },
  { key: "Removal_Volume", name: "Removal Volume", unit: "mm³" },
];

const LineChartsimulation = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );
  const [value, setValue] = useState("XCurrPos");
  const selectedType = types.find((type) => type.key === value);
  //const keys = Object.keys(currentSimulationData[0]);
  const chartRef = useRef();
  const { playbackIdx, setPlaybackIdx } = useContext(PlaybackIdxContext);

  const handleChange = (event) => {
    setValue(event.target.value);
    console.log(event.target.unit);
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
    scales: {
      x: {
        display: true,
        title: {
          display: true,
          text: "Time",
        },
      },

      y: {
        display: true,
        title: {
          display: true,
          text: `${selectedType.name} in ${selectedType.unit}`,
        },
      },
    },
  };
  const data = {
    labels: Object.keys(SimulationJSON).map(
      (key) => SimulationJSON[key].Timestamp
    ),
    datasets: [
      {
        data: Object.values(SimulationJSON).map((obj) => obj[value]),
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.5)",
      },
    ],
  };

  const triggerTooltip = (chart, idx) => {
    const tooltip = chart.tooltip;

    const chartArea = chart.chartArea;
    tooltip.setActiveElements(
      [
        {
          datasetIndex: 0,
          index: idx,
        },
      ],
      {
        x: (chartArea.left + chartArea.right) / 2,
        y: (chartArea.top + chartArea.bottom) / 2,
      }
    );

    chart.update();
  };

  useEffect(() => {
    if (chartRef.current != null) {
      triggerTooltip(chartRef.current, playbackIdx);
    }
  }, [playbackIdx]);

  return (
    <Box
      sx={{
        height: "50%",
        border: "2px solid #5921d0",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(89, 33, 208, 0.29)",
        display: "flex",
        flexDirection: "column",
        backgroundColor: colors.indigoAccent[900],
      }}
    >
      <FormControl size="small">
        <InputLabel id="demo-simple-select-label">Category</InputLabel>
        <Select
          labelId="demo-simple-select-label"
          id="demo-simple-select"
          value={value}
          label="Value"
          onChange={handleChange}
        >
          {types.map((e) => {
            return (
              <MenuItem value={e.key} unit={e.unit} key={e.key}>
                {" "}
                {e.name}{" "}
              </MenuItem>
            );
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
