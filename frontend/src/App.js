import { ColorModeContext, useMode, RoutingContext } from "./theme";
import { CssBaseline, ThemeProvider } from "@mui/material";
import React, { Component, useState } from "react";
import { render } from "react-dom";
import Topbar from "./scenes/global/Topbar.jsx";
import Navbar from "./scenes/global/Sidebar.jsx";
import Live_Data from "./scenes/live_data/index.jsx";
import Simulation from "./scenes/simulation/index.jsx";
import { DndProvider } from "react-dnd";
import { HTML5Backend } from "react-dnd-html5-backend";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link,
  Redirect,
  Routes,
} from "react-router-dom";

const queryClient = new QueryClient();
function App() {
  const [theme, colorMode] = useMode();
  const [currentSite, setCurrentSite] = useState("");

  return (
    <ColorModeContext.Provider value={colorMode}>
      <ThemeProvider theme={theme}>
        <RoutingContext.Provider value={{ currentSite, setCurrentSite }}>
          <QueryClientProvider client={queryClient}>
            <DndProvider backend={HTML5Backend}>
              <CssBaseline />

              <div className="app">
                <Navbar />
                <main className="content">
                  <Topbar />
                  <Routes>
                    <Route path="/home" element={<Live_Data />} />
                    <Route path="/simulation" element={<Simulation />} />
                  </Routes>
                </main>
              </div>
            </DndProvider>
          </QueryClientProvider>
        </RoutingContext.Provider>
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
