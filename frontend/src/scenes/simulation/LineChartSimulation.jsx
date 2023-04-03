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
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const { currentSimulationData, setCurrentSimulationData } = useContext(
    CurrentSimulationContext
  );
  const [age, setAge] = useState("");
  const keys = Object.keys(currentSimulationData[0]);
  const chartRef = useRef();
  const { playbackIdx, setPlaybackIdx } = useContext(PlaybackIdxContext);

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
    const timestampArray = Object.values(data).map((obj) => obj.Timestamp);
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
      <Box mr="5px">
        <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
      </Box>
      <FormControl size="small">
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
