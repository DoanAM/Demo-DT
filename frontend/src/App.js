import { ColorModeContext, useMode, RoutingContext } from "./theme";
import { CssBaseline, ThemeProvider } from "@mui/material";
import React, { Component, useState } from "react";
import { render } from "react-dom";
import Topbar from "./scenes/global/Topbar.jsx";

import Live_Data from "./scenes/live_data/index.jsx";
import Simulation from "./scenes/simulation/index.jsx";

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
            <CssBaseline />

            <div className="app">
              <main className="content">
                <Topbar />
                <Routes>
                  <Route path="/home" element={<Live_Data />} />
                  <Route path="/simulation" element={<Simulation />} />
                </Routes>
              </main>
            </div>
          </QueryClientProvider>
        </RoutingContext.Provider>
      </ThemeProvider>
    </ColorModeContext.Provider>
  );
}

export default App;
