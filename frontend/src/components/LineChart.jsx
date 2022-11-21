import { ResponsiveLine } from "@nivo/line";
import { Typography, useTheme } from "@mui/material";
import { tokens } from "../theme";
import Axios from "axios";
import { useQuery } from "@tanstack/react-query";
import { useState, useEffect } from "react";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import Select, { SelectChangeEvent } from "@mui/material/Select";
import Box from "@mui/material/Box";
import InputLabel from "@mui/material/InputLabel";
import CloseOutlinedIcon from "@mui/icons-material/CloseOutlined";
import { padding } from "@mui/system";

const graphData = [
  {
    id: "japan",
    color: "hsl(238, 70%, 50%)",
    data: [
      {
        x: "2022-11-19T17:32:33",
        y: 97,
      },
      {
        x: "2022-11-19T17:32:35",
        y: 62,
      },
      {
        x: "2022-11-19T17:32:37",
        y: 34,
      },
      {
        x: "2022-11-19T17:32:39",
        y: 3,
      },
      {
        x: "2022-11-19T17:32:41",
        y: 67,
      },
      {
        x: "2022-11-19T17:32:43",
        y: 29,
      },
      {
        x: "2022-11-19T17:32:45",
        y: 71,
      },
      {
        x: "2022-11-19T17:32:47",
        y: 92,
      },
      {
        x: "2022-11-19T17:32:49",
        y: 64,
      },
      {
        x: "2022-11-19T17:32:51",
        y: 53,
      },
      {
        x: "2022-11-19T17:32:53",
        y: 84,
      },
      {
        x: "2022-11-19T17:32:55",
        y: 93,
      },
      {
        x: "2022-11-19T17:32:57",
        y: 82,
      },
      {
        x: "2022-11-19T17:32:59",
        y: 69,
      },
      {
        x: "2022-11-19T17:33:01",
        y: 34,
      },
      {
        x: "2022-11-19T17:33:03",
        y: 7,
      },
      {
        x: "2022-11-19T17:33:05",
        y: 45,
      },
    ],
  },
];

const LineChart = (props) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const field = props.name.toLowerCase();
  const model = props.category.toLowerCase();
  const [graphPoints, setGraphPoints] = useState([]);
  const [timeFrame, setTimeFrame] = useState("1day");
  const valuesToShow = graphPoints.map((v, i) => (i % 3 === 0 ? "" : v));
  //const [oldData, setOldData] = useState([]);

  const fetchOldData = async (m, f, t) => {
    const response = await Axios.get(
      "/debug/get-timedData/" + "?model=" + m + "&field=" + f + "&timespan=" + t
    );
    setGraphPoints((e) => response.data);
    //console.log(response);
    return response;
  };

  const { status, data: oldData } = useQuery({
    queryKey: ["OtherData", model, field, timeFrame],
    queryFn: ({ queryKey }) =>
      fetchOldData(queryKey[1], queryKey[2], queryKey[3]),
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
    queryKey: ["graphData", model, field, checkData],
    queryFn: ({ queryKey }) => fetchData(queryKey[1], queryKey[2]),
    enabled: !!checkData,
    refetchInterval: 3000,
  });

  const close = () => {
    props.onClose(props.id);
  };

  const handleChange = (e) => {
    //console.log(e.target.value);
    setTimeFrame(e.target.value);
  };
  /* useEffect(() => {
    console.log("Field is: ", field);
    console.log("Model is: ", model);
  }); */

  return (
    <Box
      sx={{
        height: "33%",
        //backgroundColor: colors.black[700],
        paddingBottom: "0px",
        paddingTop: "15px",
        paddingLeft: "20px",
        paddingRight: "20px",
        margin: "5px 5px 5px 0px",
        border: "2px solid #7A410D",
        borderRadius: "14px",
        boxShadow: "4px 2px 15px rgba(122, 65, 13, 0.29)",
      }}
    >
      <Box width={"100%"} display="flex" justifyContent={"space-between"}>
        <Box>
          <FormControl fullWidth>
            <InputLabel id="demo-simple-select-label">Time</InputLabel>
            <Select
              defaultValue={timeFrame}
              //defaultValue={"1day"}
              //placeholder=""
              sx={{
                width: 200,
                height: 30,
              }}
              onChange={handleChange}
            >
              <MenuItem value="30min">
                <Typography variant="h6">30min</Typography>
              </MenuItem>
              <MenuItem value="1hr">1hr</MenuItem>
              <MenuItem value="1day">1day</MenuItem>
              <MenuItem value="1month">1month</MenuItem>
            </Select>
          </FormControl>
        </Box>
        <Box>
          <Typography variant="h4">{props.name}</Typography>
        </Box>
        <Box mr="5px">
          <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
        </Box>
      </Box>
      <ResponsiveLine
        //data={[{ id: "xenc1vel", data: oldData.data }]}
        data={[{ id: "xenc1vel", data: graphPoints }]}
        //data={graphData}
        theme={{
          axis: {
            domain: {
              line: {
                stroke: colors.black[100],
              },
            },
            legend: {
              text: {
                fill: colors.black[100],
              },
            },
            ticks: {
              line: {
                stroke: colors.black[100],
                strokeWidth: 1,
              },
              text: {
                fill: colors.black[100],
              },
            },
          },
          legends: {
            text: {
              fill: colors.black[100],
            },
          },
          tooltip: {
            container: {
              color: colors.primary[500],
            },
          },
        }}
        margin={{ top: 15, right: 5, bottom: 70, left: 35 }}
        /* xScale={{
          type: "point",
        }} */
        xScale={{
          type: "time",
          format: "%Y-%m-%d %H:%M:%S",
          //precision: "minute",
        }}
        //xFormat="time:%Y-%m-%d %H:%M:%S"
        yScale={{
          type: "linear",
          min: "auto",
          max: "auto",
          stacked: true,
          reverse: false,
        }}
        yFormat=" >-.2f"
        curve="linear"
        axisTop={null}
        axisRight={null}
        axisBottom={{
          format: "%H:%M:%S",
          orient: "bottom",
          tickSize: 5,
          tickPadding: 5,
          tickRotation: 0,
          legend: "time",
          legendOffset: 30,
          legendPosition: "middle",
        }}
        axisLeft={{
          orient: "left",
          tickSize: 5,
          tickPadding: 5,
          tickRotation: 0,
          legend: props.name,
          legendOffset: -30,
          legendPosition: "middle",
        }}
        enableGridX={false}
        enablePoints={false}
        colors={{ scheme: "category10" }}
        pointSize={10}
        pointColor={{ theme: "background" }}
        pointBorderWidth={2}
        pointBorderColor={{ from: "serieColor" }}
        pointLabelYOffset={-12}
        useMesh={true}
      />
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
