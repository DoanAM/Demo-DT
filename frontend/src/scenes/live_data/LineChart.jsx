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

const LineChart = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [graphPoints, setGraphPoints] = useState([]);
  const [timeFrame, setTimeFrame] = useState("1hr");
  const [title, setTitle] = useState("cnc");
  const [type, setType] = useState(["XCurrPos"]);
  const [text, setText] = useState("xcurrpos");

  const data = {
    datasets: [
      {
        data: graphPoints,
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.5)",
      },
    ],
  };

  const fetchOldData = async (m, f, t) => {
    const response = await Axios.get(
      "/debug/get-timedData/" + "?model=" + m + "&field=" + f + "&timespan=" + t
    );
    setGraphPoints((e) => response.data);
    //console.log(response);
    return response;
  };

  const { status, data: oldData } = useQuery({
    queryKey: ["OtherData", title, text, timeFrame],
    queryFn: ({ queryKey }) =>
      fetchOldData(queryKey[1], queryKey[2], queryKey[3]),
    refetchOnWindowFocus: false,
  });

  const fetchData = async (m, f) => {
    const response = await Axios.get(
      "/debug/get-cur/" + "?model=" + m + "&field=" + f
    );
    setGraphPoints((e) => [...e, response.data]);
    //console.log("GraphPoints Are:", graphPoints);
    return response;
  };

  const checkData = oldData?.data;

  const { data: newData } = useQuery({
    queryKey: ["graphData", title, text, checkData],
    queryFn: ({ queryKey }) => fetchData(queryKey[1], queryKey[2]),
    enabled: !!checkData,
    refetchInterval: 3000,
    refetchOnWindowFocus: false,
  });

  const handleTimeframeChange = (e) => {
    //console.log(e.target.value);
    setTimeFrame(e.target.value);
  };

  const handleGroupChange = (e) => {
    setTitle(e.target.value);
  };

  const handleTypeChange = (e) => {
    const lowerCaseText = e.target.value.toLowerCase();
    setText(lowerCaseText);
  };

  useEffect(() => {
    const table = datalist.find((obj) => obj.tablename === title);
    const tableKeys = Object.keys(table["columnnames"]);
    setType(tableKeys);
  }, [title]);

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

  return (
    <Box
      sx={{
        gridRow: "span 4",
        paddingBottom: "0px",
        paddingTop: "15px",
        paddingLeft: "20px",
        paddingRight: "20px",
        //margin: "5px 5px 5px 0px",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <Box width={"100%"} display="flex" justifyContent={"space-between"}>
        <FormControl size="small">
          <InputLabel id="test-select-label">Time</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            defaultValue={timeFrame}
            //defaultValue={"1day"}
            sx={{
              //width: 200,
              height: 30,
            }}
            onChange={handleTimeframeChange}
          >
            <MenuItem value="30min">
              <Typography variant="h6">30min</Typography>
            </MenuItem>
            <MenuItem value="1hr">1hr</MenuItem>
            <MenuItem value="1day">1day</MenuItem>
            <MenuItem value="1month">1month</MenuItem>
          </Select>
        </FormControl>
        <FormControl size="small">
          <InputLabel id="test-select-label">Group</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            defaultValue={title}
            sx={{
              //width: 200,
              height: 30,
            }}
            onChange={handleGroupChange}
          >
            {datalist.map((item, index) => {
              return (
                <MenuItem value={item.tablename} key={index}>
                  {item.tablename}
                </MenuItem>
              );
            })}
          </Select>
        </FormControl>

        <FormControl size="small">
          <InputLabel id="test-select-label">Type</InputLabel>
          <Select
            labelId="test-select-label"
            label="Time"
            defaultValue={type}
            sx={{
              //width: 200,
              height: 30,
            }}
            onChange={handleTypeChange}
          >
            {type.map((item, index) => {
              return (
                <MenuItem value={item} key={index}>
                  {item}
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

export default LineChart;

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
