import { ResponsiveLine } from "@nivo/line";
import { useTheme } from "@mui/material";
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
  const [graphPoints, setGraphPoints] = useState([]);
  const [timeFrame, setTimeFrame] = useState("1day");
  //const [oldData, setOldData] = useState([]);

  const fetchOldData = async (t) => {
    const response = await Axios.get(
      "/debug/get-timedData/" +
        "?model=drive" +
        "&field=xenc1vel" +
        "&timespan=" +
        t
    );
    setGraphPoints((e) => response.data);
    //console.log(response);
    return response;
  };

  const { status, data: oldData } = useQuery({
    queryKey: ["OtherData", timeFrame],
    queryFn: ({ queryKey }) => fetchOldData(queryKey[1]),
  });

  const fetchData = async () => {
    const response = await Axios.get("/debug/get-enc");
    setGraphPoints((e) => [...e, response.data]);
    //console.log("GraphPoints Are:", graphPoints);
    return response;
  };

  const checkData = oldData?.data;

  const { data: newData } = useQuery({
    queryKey: ["graphData", checkData],
    queryFn: fetchData,
    enabled: !!checkData,
    refetchInterval: 3000,
  });

  const close = () => {
    console.log("Clicked");
    console.log("Id is: ", props.id);
    props.onClose(props.id);
  };

  const handleChange = (e) => {
    //console.log(e.target.value);
    setTimeFrame(e.target.value);
  };

  return (
    <Box width={"100%"} height="50vh">
      <FormControl fullWidth>
        <InputLabel id="demo-simple-select-label">Time</InputLabel>
        <Select
          defaultValue={timeFrame}
          //defaultValue={"1day"}
          //placeholder=""
          sx={{
            width: 200,
            height: 50,
          }}
          onChange={handleChange}
        >
          <MenuItem value="30min">30min</MenuItem>
          <MenuItem value="1hr">1hr</MenuItem>
          <MenuItem value="1day">1day</MenuItem>
          <MenuItem value="1month">1month</MenuItem>
        </Select>
      </FormControl>
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
        margin={{ top: 50, right: 110, bottom: 50, left: 60 }}
        xScale={{ type: "point" }}
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
          orient: "bottom",
          tickSize: 5,
          tickPadding: 5,
          tickRotation: 0,
          legend: "transportation",
          legendOffset: 36,
          legendPosition: "middle",
        }}
        axisLeft={{
          orient: "left",
          tickSize: 5,
          tickPadding: 5,
          tickRotation: 0,
          legend: "count",
          legendOffset: -40,
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
        legends={[
          {
            anchor: "bottom-right",
            direction: "column",
            justify: false,
            translateX: 100,
            translateY: 0,
            itemsSpacing: 0,
            itemDirection: "left-to-right",
            itemWidth: 80,
            itemHeight: 20,
            itemOpacity: 0.75,
            symbolSize: 12,
            symbolShape: "circle",
            symbolBorderColor: "rgba(0, 0, 0, .5)",
            effects: [
              {
                on: "hover",
                style: {
                  itemBackground: "rgba(0, 0, 0, .03)",
                  itemOpacity: 1,
                },
              },
            ],
          },
        ]}
      />
      <Box mr="5px">
        <CloseOutlinedIcon onClick={close}>X</CloseOutlinedIcon>
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
