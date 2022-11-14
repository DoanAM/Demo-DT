import { ColorModeContext, useMode } from "./theme";
import { CssBaseline, ThemeProvider } from "@mui/material";
import React, { Component } from "react";
import { render } from "react-dom";
import Topbar from "./scenes/global/Topbar.jsx";
import Navbar from "./scenes/global/Sidebar.jsx";
import Live_Data from "./scenes/live_data/index.jsx";

function App() {
  const [theme, colorMode] = useMode();

  return (
    <ColorModeContext.Provider value={colorMode}>
      <ThemeProvider theme={theme}>
        <CssBaseline />
        <div className="app">
          <Navbar />
          <main className="content">
            <Topbar />
            <Live_Data />
          </main>
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
