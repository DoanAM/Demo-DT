import os

from ..config import data_rootpath, mwcamlib_path, ToolDict, toolpath_filename, simtoolpath_filename, result_real_filename,\
    result_sim_filename, mesh_sim_filename, mesh_real_filename
from .. import mwwrapper
import platform
from datetime import datetime
from matplotlib import pyplot as plt
import matplotlib.dates as mdates

import pandas as pd

class EvalSim:
    """
    This class contains the method to visualize the simulation animation and live plot of machine parameter

    This class is similar to mwCamSim class. They share the same working principle.
    """

    def __init__(self, simType: str):
        """
        MW CAM function wrapper to conduct the CAM simulation and cutting analysis
        :param simType: string, simulation type, it should be either 'cnc' or 'real'
        """
        if platform.architecture()[0] == '32bit':
            print("Error: MW Cam does not has the dll with 32 version yet")
            exit()
        if platform.architecture()[0] == '64bit':
            self.mw_dll = mwwrapper.load(mwcamlib_path)

        # file storage path of simulated tool path
        self.toolpathfile = None
        # file storage path of engagement result
        self.simfile = None
        # file storage path of generated CAD model
        self.stlfile = None
        # tool number in mw cam simulation ToDo: for future work, here should be determined whether use tool id or tool number
        self.tool_id = 0
        # simulation step index
        self.cut_id = 1
        # diagnose position of workpiece
        self.workpiece_pos = {}
        # used tolls
        self.toolset = {}
        # visualization padding
        self.viewrange = 50

        mwwrapper.init(self.mw_dll)
        self.simType = simType

    def __del__(self):
        """
        object deconstruction
        :return: None
        """
        del (self.mw_dll)
        print("[\033[1;32mOK\033[0m]  Shut down ModuleWork CAM Sim")

    def load_file(self, partname):
        """
        import tool path file either from real cnc dat or vnck simulated cnc data
        :param partname: string, folder name of workpiece
        :return: None
        """

        if self.simType == 'real':
            self.toolpathfile = os.path.join(data_rootpath, partname, toolpath_filename)

        elif self.simType == 'vnck':
            self.toolpathfile = os.path.join(data_rootpath, partname, simtoolpath_filename)

        else:
            raise ValueError(f"wrong simType is given, value: {self.simType}")

        # need to encode in byte string
        # mwwrapper.load_file(self.mw_dll, self.simfile.encode())

    def load_toolset(self):
        """
        configurate pre-defined tool set
        :return:
        """
        for key, value in ToolDict.items():
            # if current item only has two parameters, it is an end milling tool
            if len(value) == 2:
                fDiameter = value[0]
                fHeight = value[1]
                fid = int(key)
                self._set_tool(fDiameter, fHeight, fid)
            # if current item has four parameters, it is a chamfer tool
            elif len(value) == 4:
                cDiameter = value[0]
                cHeight = value[1]
                fid = int(key)
                cDiameterOut = value[2]
                taperangle = value[3]
                self._set_tool(cDiameter, cHeight, fid, cDiameterOut=cDiameterOut, taperangle=taperangle)

    def set_stock(self, bounds):
        """
        create workpiece in simulation environment
        :param bounds: dict, stock diagnose point position
        :return: None
        """

        mwwrapper.set_precision(self.mw_dll, 1)

        self.workpiece_pos = bounds

        mwwrapper.set_stock(self.mw_dll,
                            self.workpiece_pos["x_init"],
                            self.workpiece_pos["y_init"],
                            self.workpiece_pos["z_init"],
                            self.workpiece_pos["x_end"],
                            self.workpiece_pos["y_end"],
                            self.workpiece_pos["z_end"])

        # visualization range should larger than maximum workpiece dimension
        self.viewrange += max(self.workpiece_pos["x_end"] - self.workpiece_pos["x_init"],
                              self.workpiece_pos["y_end"] - self.workpiece_pos["y_init"],
                              self.workpiece_pos["z_end"] - self.workpiece_pos["z_init"])


    def sim(self, *args):
        """

        :param args: list[pd.DataFrame], dataframe for machine parameter, the dataframe should contain two columns: Timestamp and corresponding status value
        :return: None
        """

        mwwrapper.set_visualization(self.mw_dll, True)
        mwwrapper.config(self.mw_dll)
        f_toolpath = open(self.toolpathfile, 'r')
        f_toolpath.readline()  # skip name row

        # init graph figure
        visual_x = []
        visual_ys = []
        plt.rcParams["figure.figsize"] = (10, 6)
        for i in range(len(args)):
            visual_ys.append([])
            plt.plot(visual_x, visual_ys[i], label=args[i].columns[-1])
        # specific for spindle speed. please uncomment following lines, if you want to see the spindle motor velocity :
        # visual_rev = []
        #plt.plot(visual_x, visual_rev, label='S1ActRev')
        plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%d-%m %H:%M'))
        plt.grid(True)
        #figure(figsize=(8, 6))
        plt.xlabel('Datetime')
        # ToDo: solve this hard coded
        plt.ylabel('spindle current (A)')
        plt.title('Live graph')
        plt.legend()


        x_start = None
        y_start = None
        z_start = None

        # ToDo: check the tool information before sim start
        # use first tool by default
        mwwrapper.set_current_tool(self.mw_dll, 0)

        num_lines = sum(1 for _ in open(self.toolpathfile))
        current_line_idx = 1
        print(f"[]  CAM Simulation running {0}/{num_lines}", end="\r")

        isstart = False
        curr_tool_id_twincat = 0
        prev_tool_id_twincat = 0
        curr_tool_id = 0
        block_nr = 0

        # move tool out of visualization:
        for tool_id_mw, tool_id_vnck in self.toolset.items():
            mwwrapper.set_current_tool(self.mw_dll, int(tool_id_mw))
            mwwrapper.DoCut(self.mw_dll,
                            0,
                            0,
                            1,
                            400,
                            400,
                            100,
                            0,
                            0,
                            int(0),
                            int(tool_id_vnck[2]),
                            -1,
                            False,
                            False)


        while True:
            if self.cut_id == 1 and not isstart:
                line_start = f_toolpath.readline()
                pos_list = list(map(float, line_start.strip().split(' ')))
                x_start = pos_list[1]
                y_start = pos_list[2]
                z_start = pos_list[3]
                prev_tool_id_twincat = pos_list[6]
                new_tool_id_mw = self._find_tool_id(prev_tool_id_twincat)
                mwwrapper.set_current_tool(self.mw_dll, new_tool_id_mw)
                isstart = True

            line = f_toolpath.readline()
            current_line_idx += 1
            if not line:
                break
            if current_line_idx % 10 == 0 or current_line_idx == num_lines-1:
                pos_list = list(map(float, line.strip().split(' ')))
                timestamp = pos_list[0]
                x_end = pos_list[1]
                y_end = pos_list[2]
                z_end = pos_list[3]
                S1Actrev = pos_list[4]
                Actfeed = pos_list[5]
                curr_tool_id_twincat = pos_list[6]

                if curr_tool_id_twincat != prev_tool_id_twincat:
                        if self.simType == 'vnck':
                            # move out current tool
                            mwwrapper.DoCut(self.mw_dll,
                                            x_start,
                                            y_start,
                                            z_start,
                                            400,
                                            400,
                                            100,
                                            0,
                                            0,
                                            int(0),
                                            int(prev_tool_id_twincat),
                                            -1,
                                            False,
                                            False)

                        new_tool_id_mw = self._find_tool_id(curr_tool_id_twincat)
                        mwwrapper.set_current_tool(self.mw_dll, new_tool_id_mw)
                        curr_tool_id = str(new_tool_id_mw)

                mwwrapper.DoCut(self.mw_dll,
                                x_start,
                                y_start,
                                z_start,
                                x_end,
                                y_end,
                                z_end,
                                S1Actrev,
                                Actfeed,
                                int(timestamp),
                                int(curr_tool_id_twincat),
                                self.cut_id,
                                True, # do real cut
                                False) # not record any result

                if self.cut_id % 10 == 0:
                    # show the animation
                    mwwrapper.visualization(self.mw_dll, True, self.viewrange)

                    # show the live updated graph
                    if len(plt.gca().lines):
                        visual_x.append(datetime.fromtimestamp(timestamp / 1000.))
                        # specific for spindle speed. please uncomment following lines, if you want to see the spindle motor velocity :
                        # visual_rev.append(S1Actrev)
                        for i in range(len(args)):
                            current_output = args[i][args[i]['Timestamp'] == timestamp].iloc[0, 1]
                            visual_ys[i].append(current_output)
                            plt.gca().lines[i].set_xdata(visual_x[-100:])
                            plt.gca().lines[i].set_ydata(visual_ys[i][-100:])

                        plt.gca().relim()
                        plt.gca().autoscale_view()
                    plt.pause(0.05)

                print(f"[]  CAM Simulation running {current_line_idx}/{num_lines}, current position: {x_end}, {y_end}, "
                      f"{z_end}, current tool: (diameter, length, id): {self.toolset.get(str(curr_tool_id))} "
                      f"nc block: {block_nr}", end="\r")
                x_start = x_end
                y_start = y_end
                z_start = z_end
                prev_tool_id_twincat = curr_tool_id_twincat

                self.cut_id += 1

        f_toolpath.close()
        mwwrapper.window_close(self.mw_dll)
        plt.show()
        print(f"[\033[1;32mOK\033[0m]  CAM Simulation running {num_lines}/{num_lines}", end="\n")


    def _set_tool(self, fDiameter, fHeight, machine_tool_id, **kwargs):
        """
        set each tool in simulation environment with give dimension
        :param fDiameter: float, cutter diameter
        :param fHeight: float, cutter shaft length
        :param machine_tool_id: string, tool number defined by NC program
        :param kwargs: additional parameter of chamfer tool
        :return: None
        """
        fDiameterTop = fDiameter
        fShoulderHeight = int(1.5 * fHeight)

        if 'cDiameterOut' in kwargs and 'taperangle' in kwargs:
            cDiameterOut = kwargs['cDiameterOut']
            taperangle = kwargs['taperangle']
            mwwrapper.set_tool_chamfer(self.mw_dll, fDiameter, cDiameterOut, fDiameterTop, fShoulderHeight, fHeight, taperangle, self.tool_id)
            self.toolset[str(self.tool_id)] = (fDiameter, fHeight, machine_tool_id, cDiameterOut, taperangle)
        else:
            mwwrapper.set_tool(self.mw_dll, fDiameter, fDiameterTop, fShoulderHeight, fHeight, self.tool_id)
            self.toolset[str(self.tool_id)] = (fDiameter, fHeight, machine_tool_id)

        self.tool_id += 1

    def _find_tool_id(self, machine_tool_id) -> int:
        for key, value in self.toolset.items():
            if value[2] == machine_tool_id:
                return int(key)

        raise ValueError("Don't find a tool that fixed the dimension, please check if all the tools are imported in mwcam")


if __name__ == "__main__":
    print(f"Current working directory: {os.getcwd()}")
    os.chdir("../")
    print(f"Change the working directory: {os.getcwd()}")

    partname = "Versuchsteil_Quadrant_test"
    selected_col_drive = ['S1ActTrq']
    bounds = {'x_init': 0, 'y_init': 0, 'z_init': -30,
              'x_end': 90, 'y_end': 95, 'z_end': 0}


    df_drive = pd.read_csv(os.path.join(data_rootpath, partname, 'DriveData.csv'), sep=",", index_col='Timestamp')
    df_drive = df_drive[selected_col_drive]
    df_drive = df_drive.reset_index()

    myES = EvalSim('real')
    myES.load_file(partname)
    myES.set_stock(bounds)
    myES.load_toolset()
    myES.sim(df_drive)

    del myES