import { IconButton, Typography, useTheme } from "@mui/material";
import { tokens } from "../../theme";
import Axios from "axios";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect } from "react";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import Select from "@mui/material/Select";
import Box from "@mui/material/Box";
import InputLabel from "@mui/material/InputLabel";
import { padding } from "@mui/system";
import datalist from "../../data/datalist.json";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  TimeScale,
} from "chart.js";
import LiveJson from "../../data/Live.json";
import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  TimeScale,
  Title,
  Tooltip,
  Legend
);
const types = [
  { key: "XCurrPos", name: "X Position", unit: "mm" },
  { key: "YCurrPos", name: "Y Position", unit: "mm" },
  { key: "ZCurrPos", name: "Z Position", unit: "mm" },
  { key: "XFollDist", name: "X Error", unit: "mm" },
  { key: "YFollDist", name: "Y Error", unit: "mm" },
  { key: "ZFollDist", name: "Z Error", unit: "mm" },
];

const LineChartHandler = (props) => {
  const theme = useTheme();
  //const [counter, setCounter] = useState(null);
  const colors = tokens(theme.palette.mode);
  const [graphPoints, setGraphPoints] = useState([]);
  const [type, setType] = useState("XCurrPos");
  const selectedType = types.find((item) => item.key === type);
  // useEffect(() => {
  //   const startTime = new Date();
  //   startTime.setHours(8, 0, 0, 0); // set the starting time to 08:00:00.000

  //   const intervalId = setInterval(() => {
  //     const timeElapsed = Math.floor((new Date() - startTime) / 1000) + 1;
  //     setCounter(timeElapsed % (LiveJson.length - 1));
  //   }, 1000);

  //   return () => clearInterval(intervalId);
  // }, []);

  useEffect(() => {
    if (props.counter !== null) {
      if (props.counter === 1) {
        setGraphPoints([]);
      }

      const slicedData = LiveJson.slice(0, props.counter);

      setGraphPoints(slicedData);
    }
  }, [props.counter, LiveJson, type]);

  const data = {
    labels: graphPoints.map((item) => item.Timestamp),
    datasets: [
      {
        data: graphPoints.map((d) => d[type]),
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.5)",
      },
    ],
  };

  const handleTypeChange = (e) => {
    setType(e.target.value);
  };

  const options = {
    animation: false,
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
    sampling: {
      enabled: true,
      threshold: 5, // Maximum number of points to display on the chart
    },
    scales: {
      x: {
        display: true,
        title: {
          display: true,
          text: "Time in min:sec",
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

  return (
    <Box
      name={props.name}
      sx={{
        gridRow: "span 4",
        paddingBottom: "0px",
        paddingTop: "15px",
        paddingLeft: "20px",
        paddingRight: "20px",
        backgroundColor: colors.indigoAccent[900],
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <Box width={"100%"} display="flex" justifyContent={"space-between"}>
        <FormControl size="small">
          <InputLabel id="test-select-label">Value</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            value={type}
            sx={{
              width: 200,
              height: 30,
            }}
            onChange={handleTypeChange}
          >
            {types.map((item, index) => {
              return (
                <MenuItem value={item.key} key={item.index}>
                  {item.name}
                </MenuItem>
              );
            })}
          </Select>
        </FormControl>
      </Box>
      <Box display={"flex"}>
        <Line data={data} options={options} />
      </Box>
    </Box>
  );
};

export default LineChartHandler;

/*   useEffect(() => {
    const fetchOldData = async () => {
      const response = await Axios.get(
        "/debug/get-timedData/" +
          "?model=drive" +
          "&field=xenc1vel" +
          "&timespan=" +
          timeFrame
      );
      setOldData(response);
    };
    fetchOldData();
    //setOldData(res);
    //console.log(oldData);
  }, [timeFrame]); */
