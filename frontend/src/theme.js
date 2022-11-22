import { createContext, useState, useMemo } from "react";
import { createTheme } from "@mui/material/styles";

//color design tokens
export const tokens = (mode) => ({
  ...(mode === "dark"
    ? {
        black: {
          100: "#cececf",
          200: "#9d9d9f",
          300: "#6c6c6f",
          400: "#3b3b3f",
          500: "#0a0a0f",
          600: "#08080c",
          700: "#060609",
          800: "#040406",
          900: "#020203",
        },
        primary: {
          100: "#d3eff6",
          200: "#a6deec",
          300: "#7acee3",
          400: "#4dbdd9",
          500: "#21add0",
          600: "#1a8aa6",
          700: "#14687d",
          800: "#0d4553",
          900: "#07232a",
        },
        yellowAccent: {
          100: "#f7f7f7",
          200: "#f0f0f0",
          300: "#e8e8e8",
          400: "#e1e1e1",
          500: "#d9d9d9",
          600: "#aeaeae",
          700: "#828282",
          800: "#575757",
          900: "#2b2b2b",
        },
        purpleAccent: {
          100: "#ded3f6",
          200: "#bda6ec",
          300: "#9b7ae3",
          400: "#7a4dd9",
          500: "#5921d0",
          600: "#471aa6",
          700: "#35147d",
          800: "#240d53",
          900: "#12072a",
        },
        orangeAccent: {
          100: "#e4d9cf",
          200: "#cab39e",
          300: "#af8d6e",
          400: "#95673d",
          500: "#7a410d",
          600: "#62340a",
          700: "#492708",
          800: "#311a05",
          900: "#180d03",
        },
        indigoAccent: {
          100: "#dfe1e9",
          200: "#bfc3d2",
          300: "#a0a4bc",
          400: "#8086a5",
          500: "#60688f",
          600: "#4d5372",
          700: "#3a3e56",
          800: "#262a39",
          900: "#13151d",
        },
      }
    : {
        black: {
          100: "#020203",
          200: "#040406",
          300: "#060609",
          400: "#08080c",
          500: "#0a0a0f",
          600: "#3b3b3f",
          700: "#6c6c6f",
          800: "#9d9d9f",
          900: "#cececf",
        },
        primary: {
          100: "#07232a",
          200: "#0d4553",
          300: "#14687d",
          400: "#1a8aa6",
          500: "#21add0",
          600: "#4dbdd9",
          700: "#7acee3",
          800: "#a6deec",
          900: "#d3eff6",
        },
        yellowAccent: {
          100: "#2b2b2b",
          200: "#575757",
          300: "#828282",
          400: "#aeaeae",
          500: "#d9d9d9",
          600: "#e1e1e1",
          700: "#e8e8e8",
          800: "#f0f0f0",
          900: "#f7f7f7",
        },
        purpleAccent: {
          100: "#12072a",
          200: "#240d53",
          300: "#35147d",
          400: "#471aa6",
          500: "#5921d0",
          600: "#7a4dd9",
          700: "#9b7ae3",
          800: "#bda6ec",
          900: "#ded3f6",
        },
        orangeAccent: {
          100: "#180d03",
          200: "#311a05",
          300: "#492708",
          400: "#62340a",
          500: "#7a410d",
          600: "#95673d",
          700: "#af8d6e",
          800: "#cab39e",
          900: "#e4d9cf",
        },
        indigoAccent: {
          100: "#13151d",
          200: "#262a39",
          300: "#3a3e56",
          400: "#4d5372",
          500: "#60688f",
          600: "#8086a5",
          700: "#a0a4bc",
          800: "#bfc3d2",
          900: "#dfe1e9",
        },
      }),
});
// mui theme settings
export const themeSettings = (mode) => {
  const colors = tokens(mode);

  return {
    palette: {
      mode: mode,
      ...(mode === "dark"
        ? {
            primary: {
              main: colors.primary[500],
            },
            secondary: {
              main: colors.purpleAccent[500],
            },
            neutral: {
              dark: colors.black[700],
              main: colors.black[500],
              light: colors.black[100],
            },
            background: {
              default: colors.black[500],
            },
          }
        : {
            primary: {
              main: colors.primary[500],
            },
            secondary: {
              main: colors.purpleAccent[500],
            },
            neutral: {
              dark: colors.black[700],
              main: colors.black[500],
              light: colors.black[100],
            },
            background: {
              default: "#d1d7e0",
            },
          }),
    },
    typography: {
      fontFamily: ["Poppins", "sans-serif"].join(","),
      fontSize: 12,
      color: colors.black[700],
      h1: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 40,
      },
      h2: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 32,
      },
      h3: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 24,
      },
      h4: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 20,
      },
      h5: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 16,
      },
      h6: {
        fontFamily: ["Poppins", "sans-serif"].join(","),
        fontSize: 14,
      },
    },
  };
};

//context for color Mode
export const ColorModeContext = createContext({
  toggleColorMode: () => {},
});

export const useMode = () => {
  const [mode, setMode] = useState("dark");

  const colorMode = useMemo(
    () => ({
      toggleColorMode: () =>
        setMode((prev) => (prev === "light" ? "dark" : "light")),
    }),
    []
  );

  const theme = useMemo(() => createTheme(themeSettings(mode)), [mode]);
  return [theme, colorMode];
};
