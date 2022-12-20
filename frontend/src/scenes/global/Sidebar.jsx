import { useState, useContext } from "react";
import { ProSidebar, Menu, MenuItem, SubMenu } from "react-pro-sidebar";
import { Box, IconButton, Typography, useTheme } from "@mui/material";
import "react-pro-sidebar/dist/css/styles.css";
import { tokens, RoutingContext } from "../../theme";
import MenuOutlinedIcon from "@mui/icons-material/MenuOutlined";
import GamepadOutlinedIcon from "@mui/icons-material/GamepadOutlined";
import MiscellaneousServicesOutlinedIcon from "@mui/icons-material/MiscellaneousServicesOutlined";
import CarpenterOutlinedIcon from "@mui/icons-material/CarpenterOutlined";
import TerminalOutlinedIcon from "@mui/icons-material/TerminalOutlined";
import ControlCameraOutlinedIcon from "@mui/icons-material/ControlCameraOutlined";
import HubOutlinedIcon from "@mui/icons-material/HubOutlined";
import DragAndDrop from "../../components/DragAndDrop.jsx";
import { AuxiliaryList } from "../../data/AuxiliaryList.js";
import { CncList } from "../../data/CncList.js";
import { WcsList } from "../../data/WcsList.js";
import { ProgList } from "../../data/ProgList.js";
import { DriveList } from "../../data/DriveList.js";
import { ToolList } from "../../data/ToolList.js";
import { SimulationList } from "../../data/SimulationList";

const Navbar = () => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);
  const [isCollapsed, setIsCollapsed] = useState(true);
  const [selected, setSelected] = useState("Dashboard");
  const { currentSite, setCurrentSite } = useContext(RoutingContext);

  if (currentSite == "live_data") {
    return (
      <Box
        sx={{
          "& .pro-sidebar-inner": {
            background: `${colors.black[600]} !important`,
          },
          "& .pro-icon-wrapper": {
            backgroundColor: "transparent !important",
          },
          "& .pro-inner-item": {
            padding: "5px 35px 5px 20px !important",
          },
          "& .pro-inner-item:hover": {
            color: "#868dfb !important",
          },
          "& .pro-menu-item.active": {
            color: "#6870fa !important",
          },
        }}
        height="100vh"
      >
        <ProSidebar collapsed={isCollapsed}>
          <Menu iconShape="square" innerSubMenuArrows={true}>
            {/* LOGO AND MENU ICON */}
            <MenuItem
              onClick={() => setIsCollapsed(!isCollapsed)}
              icon={isCollapsed ? <MenuOutlinedIcon /> : undefined}
              style={{
                margin: "10px 0 20px 0",
                color: colors.black[100],
              }}
            >
              {!isCollapsed && (
                <Box
                  display="flex"
                  justifyContent="space-between"
                  alignItems="center"
                  ml="15px"
                >
                  <IconButton onClick={() => setIsCollapsed(!isCollapsed)}>
                    <MenuOutlinedIcon />
                  </IconButton>
                </Box>
              )}
            </MenuItem>

            {/*           <Box paddingLeft={isCollapsed ? undefined : "10%"}> */}
            <Box paddingLeft={isCollapsed ? undefined : "10%"}>
              <SubMenu
                title="CNC"
                icon={<GamepadOutlinedIcon />}
                defaultOpen={false}

                /*  selected={selected}
          setSelected={setSelected} */
              >
                {CncList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"cnc"}
                    />
                  );
                })}
              </SubMenu>
              <SubMenu
                title="Auxiliary"
                icon={<MiscellaneousServicesOutlinedIcon />}
                /*             selected={selected}
            setSelected={setSelected} */
              >
                {AuxiliaryList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"auxiliary"}
                    />
                  );
                })}
              </SubMenu>
              <SubMenu
                title="Drive"
                icon={<HubOutlinedIcon />}
                /*             selected={selected}
            setSelected={setSelected} */
              >
                {DriveList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"drive"}
                    />
                  );
                })}
              </SubMenu>
              <SubMenu
                title="WCS"
                icon={<ControlCameraOutlinedIcon />}
                /*             selected={selected}
            setSelected={setSelected} */
              >
                {WcsList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"wcs"}
                    />
                  );
                })}
              </SubMenu>
              <SubMenu
                title="Prog"
                icon={<TerminalOutlinedIcon />}
                /*             selected={selected}
            setSelected={setSelected} */
              >
                {ProgList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"prog"}
                    />
                  );
                })}
              </SubMenu>
              <SubMenu
                title="Tool"
                icon={<CarpenterOutlinedIcon />}
                /*             selected={selected}
            setSelected={setSelected} */
              >
                {ToolList.map((item) => {
                  return (
                    <DragAndDrop
                      name={item.name}
                      id={item.id}
                      category={"tool"}
                    />
                  );
                })}
              </SubMenu>
            </Box>
          </Menu>
        </ProSidebar>
      </Box>
    );
  }
  if (currentSite == "simulation") {
    return;
    return (
      <Box
        sx={{
          "& .pro-sidebar-inner": {
            background: `${colors.black[600]} !important`,
          },
          "& .pro-icon-wrapper": {
            backgroundColor: "transparent !important",
          },
          "& .pro-inner-item": {
            padding: "5px 35px 5px 20px !important",
          },
          "& .pro-inner-item:hover": {
            color: "#868dfb !important",
          },
          "& .pro-menu-item.active": {
            color: "#6870fa !important",
          },
        }}
        height="100vh"
      >
        <ProSidebar collapsed={isCollapsed}>
          <Menu iconShape="square" innerSubMenuArrows={true}>
            {/* LOGO AND MENU ICON */}
            <MenuItem
              onClick={() => setIsCollapsed(!isCollapsed)}
              icon={isCollapsed ? <MenuOutlinedIcon /> : undefined}
              style={{
                margin: "10px 0 20px 0",
                color: colors.black[100],
              }}
            >
              {!isCollapsed && (
                <Box
                  display="flex"
                  justifyContent="space-between"
                  alignItems="center"
                  ml="15px"
                >
                  <IconButton onClick={() => setIsCollapsed(!isCollapsed)}>
                    <MenuOutlinedIcon />
                  </IconButton>
                </Box>
              )}
            </MenuItem>

            <Box paddingLeft={isCollapsed ? undefined : "10%"}>
              {SimulationList.map((item) => {
                return <DragAndDrop name={item} />;
              })}
            </Box>
          </Menu>
        </ProSidebar>
      </Box>
    );
  }
};
export default Navbar;
