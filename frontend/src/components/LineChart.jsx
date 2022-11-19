import { ResponsiveLine } from "@nivo/line";
import { useTheme } from "@mui/material";
import { tokens } from "../theme";

const data = [
  {
    id: "japan",
    color: "hsl(238, 70%, 50%)",
    data: [
      {
        x: "plane",
        y: 203,
      },
      {
        x: "helicopter",
        y: 248,
      },
      {
        x: "boat",
        y: 91,
      },
      {
        x: "train",
        y: 107,
      },
      {
        x: "subway",
        y: 122,
      },
      {
        x: "bus",
        y: 151,
      },
      {
        x: "car",
        y: 144,
      },
      {
        x: "moto",
        y: 196,
      },
      {
        x: "bicycle",
        y: 17,
      },
      {
        x: "horse",
        y: 31,
      },
      {
        x: "skateboard",
        y: 87,
      },
      {
        x: "others",
        y: 27,
      },
    ],
  },
  {
    id: "france",
    color: "hsl(347, 70%, 50%)",
    data: [
      {
        x: "plane",
        y: 177,
      },
      {
        x: "helicopter",
        y: 263,
      },
      {
        x: "boat",
        y: 168,
      },
      {
        x: "train",
        y: 223,
      },
      {
        x: "subway",
        y: 58,
      },
      {
        x: "bus",
        y: 221,
      },
      {
        x: "car",
        y: 217,
      },
      {
        x: "moto",
        y: 179,
      },
      {
        x: "bicycle",
        y: 236,
      },
      {
        x: "horse",
        y: 138,
      },
      {
        x: "skateboard",
        y: 200,
      },
      {
        x: "others",
        y: 198,
      },
    ],
  },
  {
    id: "us",
    color: "hsl(339, 70%, 50%)",
    data: [
      {
        x: "plane",
        y: 27,
      },
      {
        x: "helicopter",
        y: 162,
      },
      {
        x: "boat",
        y: 178,
      },
      {
        x: "train",
        y: 209,
      },
      {
        x: "subway",
        y: 60,
      },
      {
        x: "bus",
        y: 115,
      },
      {
        x: "car",
        y: 22,
      },
      {
        x: "moto",
        y: 164,
      },
      {
        x: "bicycle",
        y: 24,
      },
      {
        x: "horse",
        y: 132,
      },
      {
        x: "skateboard",
        y: 239,
      },
      {
        x: "others",
        y: 97,
      },
    ],
  },
  {
    id: "germany",
    color: "hsl(329, 70%, 50%)",
    data: [
      {
        x: "plane",
        y: 120,
      },
      {
        x: "helicopter",
        y: 113,
      },
      {
        x: "boat",
        y: 263,
      },
      {
        x: "train",
        y: 62,
      },
      {
        x: "subway",
        y: 288,
      },
      {
        x: "bus",
        y: 294,
      },
      {
        x: "car",
        y: 86,
      },
      {
        x: "moto",
        y: 283,
      },
      {
        x: "bicycle",
        y: 79,
      },
      {
        x: "horse",
        y: 277,
      },
      {
        x: "skateboard",
        y: 258,
      },
      {
        x: "others",
        y: 236,
      },
    ],
  },
  {
    id: "norway",
    color: "hsl(69, 70%, 50%)",
    data: [
      {
        x: "plane",
        y: 293,
      },
      {
        x: "helicopter",
        y: 5,
      },
      {
        x: "boat",
        y: 273,
      },
      {
        x: "train",
        y: 173,
      },
      {
        x: "subway",
        y: 29,
      },
      {
        x: "bus",
        y: 214,
      },
      {
        x: "car",
        y: 229,
      },
      {
        x: "moto",
        y: 167,
      },
      {
        x: "bicycle",
        y: 293,
      },
      {
        x: "horse",
        y: 152,
      },
      {
        x: "skateboard",
        y: 182,
      },
      {
        x: "others",
        y: 238,
      },
    ],
  },
];

const LineChart = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  return (
    <ResponsiveLine
      data={data}
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
  );
};

export default LineChart;
