import os.path

from .config import mwcamlib_path, data_rootpath, toolpath_filename, simtoolpath_filename, result_real_filename, result_sim_filename, mesh_sim_filename, mesh_real_filename, ToolDict, cycleTime_mw
from . import mwwrapper
import platform


class mwCamSim:
    def __init__(self, mwdll, precision, simType: str):
        """
        MW CAM function wrapper to conduct the CAM simulation and cutting analysis
        :param simType: string, simulation type, it should be either 'cnc' or 'real'
        """
        if platform.architecture()[0] == '32bit':
            print("Error: MW Cam does not has the dll with 32 version yet")
            exit()
        if platform.architecture()[0] == '64bit':
            self.mw_dll = mwdll

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
        self.viewrange = 100

        self.precision = float(precision)

        mwwrapper.init(self.mw_dll)
        self.simType = simType

    def __del__(self):
        """
        object deconstruction
        :return: None
        """
        # mwwrapper.unloadMwDll(self.mw_dll)
        del (self.mw_dll)
        print("[\033[1;32mOK\033[0m]  Shut down ModuleWork CAM Sim")

    def load_file(self, partname):
        """
        import tool path file either from real cnc dat or vnck simulated cnc data
        :param partname: string, folder name of workpiece
        :return: None
        """

        if self.simType == 'real':
            self.toolpathfile = os.path.join(
                data_rootpath, partname, toolpath_filename)
            self.simfile = os.path.join(
                data_rootpath, partname, result_real_filename)
            self.stlfile = os.path.join(
                data_rootpath, partname, mesh_real_filename)
        elif self.simType == 'vnck':
            self.toolpathfile = os.path.join(
                data_rootpath, partname, simtoolpath_filename)
            self.simfile = os.path.join(
                data_rootpath, partname, result_sim_filename)
            self.stlfile = os.path.join(
                data_rootpath, partname, mesh_sim_filename)
            self.root = os.path.join(
                data_rootpath, partname, "MRS")
            os.makedirs(self.root, exist_ok=True)

        # need to encode in byte string
        mwwrapper.load_file(self.mw_dll, self.simfile.encode())

    def load_toolset(self):
        """
        configurate pre-defined tool set
        :return:
        """
        for key, value in ToolDict.items():
            # if current item only has two parameters, it is an end milling tool
            if value['type'] == 'end_mill':
                # required values for endmill
                tool_type = value['type']
                diameter = value['dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                fid = int(key)

                mwwrapper.set_tool_endmill(
                    self.mw_dll, self.tool_id, diameter, flute_length, shoulder_length)
                self.toolset[str(self.tool_id)] = (diameter, flute_length, fid)

            elif value['type'] == 'face_mill':
                # required values for camfer
                tool_type = value['type']
                diameter = value['dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                corner_radius = value['corner_rad']
                outside_diameter = value['outside_dia']
                taper_angle = value['taper_ang']
                fid = int(key)

                mwwrapper.set_tool_facemill(self.mw_dll, self.tool_id, diameter, flute_length,
                                            shoulder_length, corner_radius, outside_diameter, taper_angle)
                self.toolset[str(self.tool_id)] = (diameter, flute_length, fid)

            elif value['type'] == 'chamfer_mill':
                # required values for camfer
                tool_type = value['type']
                diameter = value['dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                corner_radius = value['corner_rad']
                taper_angle = value['taper_ang']
                outside_diameter = value['outside_dia']
                fid = int(key)
                mwwrapper.set_tool_chamfer(self.mw_dll, self.tool_id, diameter, flute_length,
                                           shoulder_length, corner_radius, taper_angle, outside_diameter)
                self.toolset[str(self.tool_id)] = (diameter, flute_length, fid)

            elif value['type'] == 'drill_mill':
                tool_type = value['type']
                diameter = value['dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                tip_angle = value['tip_ang']
                fid = int(key)

                mwwrapper.set_tool_drillmill(
                    self.mw_dll, self.tool_id, diameter, flute_length, shoulder_length, tip_angle)
                self.toolset[str(self.tool_id)] = (diameter, flute_length, fid)

            elif value['type'] == 'ball_mill':
                tool_type = value['type']
                diameter = value['dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                fid = int(key)

                mwwrapper.set_tool_ballmill(
                    self.mw_dll, self.tool_id, diameter, flute_length, shoulder_length)
                self.toolset[str(self.tool_id)] = (diameter, flute_length, fid)

            elif value['type'] == 'barrel_mill':
                tool_type = value['type']
                upper_diameter = value['upper_dia']
                max_diameter = value['max_dia']
                flute_length = value['flute_len']
                shoulder_length = 1.5*flute_length
                corner_radius = value['corner_rad']
                profile_radius = value['profile_rad']
                fid = int(key)

                mwwrapper.set_tool_barrelmill(self.mw_dll, self.tool_id, upper_diameter,
                                              max_diameter, flute_length, shoulder_length, corner_radius, profile_radius)
                self.toolset[str(self.tool_id)] = (
                    max_diameter, flute_length, fid)

            self.tool_id += 1

    def set_stock(self, bounds):
        """
        create workpiece in simulation environment
        :param bounds: dict, stock diagnose point position
        :return: None
        """

        mwwrapper.set_precision(self.mw_dll, self.precision)
        print("PRECISION IS", self.precision)

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
                              self.workpiece_pos["y_end"] -
                              self.workpiece_pos["y_init"],
                              self.workpiece_pos["z_end"] - self.workpiece_pos["z_init"])

    def sim(self, visualmode, writetrace):
        """

        :param visualmode: boolean, if pop up animation window
        :param writetrace: boolean, if record the simulation result
        :return: None
        """

        mwwrapper.set_visualization(self.mw_dll, visualmode)
        mwwrapper.config(self.mw_dll)
        f_toolpath = open(self.toolpathfile, 'r')
        f_toolpath.readline()  # skip name row

        x_start = None
        y_start = None
        z_start = None

        # use first tool by default
        mwwrapper.set_current_tool(self.mw_dll, 0)
        # calculate hom many lines in tool path file
        num_lines = sum(1 for _ in open(self.toolpathfile))
        current_line_idx = 1
        print(f"[]  CAM Simulation running {0}/{num_lines}", end="\r")
        isstart = False
        curr_tool_id_twincat = 0
        prev_tool_id_twincat = 0
        curr_tool_id = 0
        block_nr = 0

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

            if current_line_idx % cycleTime_mw == 0 or current_line_idx == num_lines-1:
                pos_list = list(map(float, line.strip().split(' ')))
                timestamp = pos_list[0]
                x_end = pos_list[1]
                y_end = pos_list[2]
                z_end = pos_list[3]
                S1Actrev = pos_list[4]
                Actfeed = pos_list[5]
                curr_tool_id_twincat = pos_list[6]
                if self.simType == 'vnck':
                    block_nr = pos_list[7]

                # check if tool is changed
                if curr_tool_id_twincat != prev_tool_id_twincat:
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
                                True,
                                writetrace,
                                self.root.encode())
                if writetrace:
                    mwwrapper.engagement_analysis(self.mw_dll)

                if visualmode:
                    # for acceleration, only 1/10 steps will be updated in frame
                    if self.cut_id % 10 == 0:
                        mwwrapper.visualization(
                            self.mw_dll, True, self.viewrange)
                    else:
                        mwwrapper.visualization(
                            self.mw_dll, False, self.viewrange)
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

        print(
            f"[\033[1;32mOK\033[0m]  CAM Simulation running {num_lines}/{num_lines}", end="\n")
        print(
            f"[\033[1;32mOK\033[0m]  Save the simulation result file in \033[1;34m{self.simfile}\033[0m")
        # need to encode in byte string
        mwwrapper.export_mesh(self.mw_dll, self.stlfile.encode())
        print(
            f"[\033[1;32mOK\033[0m]  Save the simulated mesh file in \033[1;34m{self.stlfile}\033[0m")

    # private functions:

    # def _set_tool(self, fDiameter, fHeight, machine_tool_id, **kwargs):
    #     """
    #     set each tool in simulation environment with give dimension
    #     :param fDiameter: float, cutter diameter
    #     :param fHeight: float, cutter shaft length
    #     :param machine_tool_id: string, tool number defined by NC program
    #     :param kwargs: additional parameter of chamfer tool
    #     :return: None
    #     """
    #     fDiameterTop = fDiameter
    #     fShoulderHeight = int(1.5 * fHeight)

    #     if 'cDiameterOut' in kwargs and 'taperangle' in kwargs:
    #         cDiameterOut = kwargs['cDiameterOut']
    #         taperangle = kwargs['taperangle']
    #         mwwrapper.set_tool_chamfer(self.mw_dll, fDiameter, cDiameterOut,
    #                                    fDiameterTop, fShoulderHeight, fHeight, taperangle, self.tool_id)
    #         self.toolset[str(self.tool_id)] = (
    #             fDiameter, fHeight, machine_tool_id, cDiameterOut, taperangle)
    #     else:
    #         mwwrapper.set_tool(self.mw_dll, fDiameter, fDiameterTop,
    #                            fShoulderHeight, fHeight, self.tool_id)
    #         self.toolset[str(self.tool_id)] = (
    #             fDiameter, fHeight, machine_tool_id)

    #     self.tool_id += 1

    def _find_tool_id(self, machine_tool_id):
        """
        find tool id in mw cam simulation based on tool number from NC program
        :param machine_tool_id: int, tool number from NC program
        :return: int, tool id in mw cam simulation
        """
        for key, value in self.toolset.items():
            if value[2] == machine_tool_id:
                return int(key)

        raise ValueError(
            "Don't find a tool that fixed the dimension, please check if all the tools are imported in mwcam")
