import { ColorModeContext, useMode } from "./theme";
import { CssBaseline, ThemeProvider } from "@mui/material";
import React, { Component } from "react";
import { render } from "react-dom";

function App() {
  const [theme, colorMode] = useMode();

  return (
    <ColorModeContext.Provider value={colorMode}>
      <ThemeProvider theme={theme}>
        <CssBaseline />
        <div className="app">
          Function based view
          <main className="content"></main>
        </div>
      </ThemeProvider>
    </ColorModeContext.Provider>
  );
}

export default App;

/* export default class App extends Component {
  constructor(props) {
    super(props);
  }
  render() {
    return <h1>Testing React Code2</h1>;
  }
}

const appDiv = document.getElementById("app");
render(<App />, appDiv);
 */
