"""
MW CAM simulation interface
"""
import ctypes as ct
from ctypes import *


def load(dllfile):
    """
    import dll file
    :param dllfile: str, file path of dll file
    :return: None
    """
    mwdll = ct.cdll.LoadLibrary(dllfile)

    return mwdll


def init(mwdll):
    """
    init mw cam simulation
    :param mwdll: dll
    :return: None
    """
    mwdll.init()


def load_file(mwdll, featurefile):
    """
    create result file and add to cam simulation
    :param mwdll: dll
    :param featurefile: str, simulation result file path
    :return: None
    """

    file = ct.c_char_p(featurefile)
    mwdll.load_file(file)


def set_stock(mwdll, init_x, init_y, init_z, end_x, end_y, end_z):
    """
    create workpiece model
    :param mwdll: dll
    :param init_x: int, x coordinate of start point in wcs
    :param init_y: int, y coordinate of start point in wcs
    :param init_z: int, z coordinate of start point in wcs
    :param end_x: int, x coordinate of end point in wcs
    :param end_y: int, y coordinate of end point in wcs
    :param end_z: int, z coordinate of end point in wcs
    :return: None
    """
    init_x_c = ct.c_float(init_x)
    init_y_c = ct.c_float(init_y)
    init_z_c = ct.c_float(init_z)
    end_x_c = ct.c_float(end_x)
    end_y_c = ct.c_float(end_y)
    end_z_c = ct.c_float(end_z)

    mwdll.set_stock(init_x_c, init_y_c, init_z_c, end_x_c, end_y_c, end_z_c)


def set_tool_endmill(mwdll, tool_id, diameter, flute_length, shoulder_length):
    diameter_c = ct.c_float(diameter)
    flute_length_c = ct.c_float(flute_length)
    shoulder_length_c = ct.c_float(shoulder_length)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_endmill(tool_id_c, diameter_c,
                           flute_length_c, shoulder_length_c)


def set_tool_facemill(mwdll, tool_id, diameter, flute_length, shoulder_length, corner_radius, outside_diameter,
                      taper_angle):
    diameter_c = ct.c_float(diameter)
    flute_length_c = ct.c_float(flute_length)
    shoulder_length_c = ct.c_float(shoulder_length)
    corner_radius_c = ct.c_float(corner_radius)
    outside_diameter_c = ct.c_float(outside_diameter)
    taper_angle_c = ct.c_float(taper_angle)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_facemill(tool_id_c, diameter_c, flute_length_c, shoulder_length_c, corner_radius_c,
                            outside_diameter_c, taper_angle_c)


def set_tool_chamfer(mwdll, tool_id, diameter, flute_length, shoulder_length, corner_radius, taper_angle,
                     outside_diameter):
    """
    create chamfer tool in mw cam simulation
    :param mwdll: dll
    :param cDiameter: cutter diameter
    :param cDiameterOut: outside diameter
    :param cDiameterTop: holder diameter
    :param cShoulderHeight: shaft length
    :param cHeight: cutter shaft length
    :param taperangle: chamfer angle
    :param tool_id: tool id in mw cam
    :return: None
    """
    diameter_c = ct.c_float(diameter)
    flute_length_c = ct.c_float(flute_length)
    shoulder_length_c = ct.c_float(shoulder_length)
    corner_radius_c = ct.c_float(corner_radius)
    taper_angle_c = ct.c_float(taper_angle)
    outside_diameter_c = ct.c_float(outside_diameter)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_chamfer(tool_id_c, diameter_c, flute_length_c, shoulder_length_c, corner_radius_c, taper_angle_c,
                           outside_diameter_c)


def set_tool_drillmill(mwdll, tool_id, diameter, flute_length, shoulder_length, tip_angle):
    diameter_c = ct.c_float(diameter)
    flute_length_c = ct.c_float(flute_length)
    shoulder_length_c = ct.c_float(shoulder_length)
    tip_angle_c = ct.c_float(tip_angle)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_drillmill(tool_id_c, diameter_c,
                             flute_length_c, shoulder_length_c, tip_angle_c)


def set_tool_ballmill(mwdll, tool_id, diameter, flute_length, shoulder_length):
    diameter_c = ct.c_float(diameter)
    shoulder_length_c = ct.c_float(shoulder_length)
    flute_length_c = ct.c_float(flute_length)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_ballmill(tool_id_c, diameter_c,
                            flute_length_c, shoulder_length_c)


# (self.mw_dll, shaftDiameter,shaftHeight, fluteDiameter,fluteHeight,cornerRadius,profileRadius,self.tool_id)
def set_tool_barrelmill(mwdll, tool_id, upper_diameter, max_diameter, flute_length, shoulder_length, corner_radius,
                        profile_radius):
    upper_diameter_c = ct.c_float(upper_diameter)
    max_diameter_c = ct.c_float(max_diameter)
    flute_length_c = ct.c_float(flute_length)
    shoulder_length_c = ct.c_float(shoulder_length)
    corner_radius_c = ct.c_float(corner_radius)
    profile_radius_c = ct.c_float(profile_radius)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_barrelmill(tool_id_c, upper_diameter_c, max_diameter_c, flute_length_c, shoulder_length_c,
                              corner_radius_c, profile_radius_c)


def set_current_tool(mwdll, tool_id):
    """
    set cutting tool in current simulation step
    :param mwdll: dll
    :param tool_id: tool id plan to be changed
    :return: None
    """
    tool_idx_c = ct.c_int(tool_id)
    mwdll.set_current_tool(tool_idx_c)


def config(mwdll):
    """
    configure the simulation environment
    :param mwdll: dll file
    :return:
    """
    mwdll.config()


def DoCut(mwdll, x_start, y_start, z_start, x_end, y_end, z_end, s1actrev, actfeed, timestamp, tool_id, cut_id, iscut, istrace, path):
    """
    execute a single step cutting simulation
    :param mwdll: dll file
    :param x_start: float, x coordinate in start point
    :param y_start: float, y coordinate in start point
    :param z_start: float, z coordinate in start point
    :param x_end: float, x coordinate in end point
    :param y_end: float, y coordinate in end point
    :param z_end: float, z coordinate in end point
    :param s1actrev: int, target motor speed
    :param actfeed: int, target feed rate
    :param timestamp: int, timestamp
    :param tool_id: int, used tool id in current step
    :param cut_id: int, cutting step index
    :param iscut: bool, if execute material removal simulation
    :param istrace: bool, if record the data
    :return: None
    """

    x_start_c = ct.c_float(x_start)
    y_start_c = ct.c_float(y_start)
    z_start_c = ct.c_float(z_start)

    x_end_c = ct.c_float(x_end)
    y_end_c = ct.c_float(y_end)
    z_end_c = ct.c_float(z_end)

    s1actrev_c = ct.c_float(s1actrev)
    actfeed_c = ct.c_float(actfeed)

    tool_id_c = ct.c_int(tool_id)

    cut_id_c = ct.c_int(cut_id)
    timestamp_c = ct.c_longlong(timestamp)
    iscut_c = ct.c_bool(iscut)
    istrace_c = ct.c_bool(istrace)

    path_c = ct.c_char_p(path)

    mwdll.DoCut(x_start_c, y_start_c, z_start_c, x_end_c, y_end_c, z_end_c,
                s1actrev_c, actfeed_c, timestamp_c, tool_id_c, cut_id_c, iscut_c, istrace_c, path_c)


def engagement_analysis(mwdll):
    """
    execute engagement analysis and record the result
    :param mwdll: dll file
    :return: None
    """
    mwdll.engagement_analysis()


def set_precision(mwdll, precision):
    """
    set modeling precision
    :param mwdll: dll file
    :param precision: float, precision value
    :return: None
    """
    precision_c = ct.c_float(precision)
    mwdll.set_precision(precision_c)


def set_visualization(mwdll, isvisual):
    """
    set if show the simulation animation
    :param mwdll: dll file
    :param isvisual: boolean, setting mode
    :return: None
    """
    isvisual_c = ct.c_bool(isvisual)
    mwdll.set_visualization(isvisual_c)


def visualization(mwdll, ishow_in_this_turn, viewrange):
    """
    update frame in visualization
    :param mwdll: dll file
    :param ishow_in_this_turn: boolean, if update the frame
    :param viewrange: visualized coordinate range
    :return: None
    """
    ishow_in_this_turn_c = ct.c_bool(ishow_in_this_turn)
    viewrange_c = ct.c_int(viewrange)
    mwdll.visualization(ishow_in_this_turn_c, viewrange_c)


def export_mesh(mwdll, stlfile):
    """
    save generated CAD model
    :param mwdll: dll file
    :param stlfile: str, model file save path
    :return: None
    """
    stlfile_c = ct.c_char_p(stlfile)
    mwdll.export_mesh(stlfile_c)


def window_close(mwdll):
    """
    close the animation window
    :param mwdll: dll file
    :return: None
    """
    mwdll.window_close()


def unloadMwDll(mwdll):
    print("Removing MW DLL")
    kernel32 = ct.WinDLL('kernel32')
    kernel32.FreeLibrary.argtypes = [ct.wintypes.HMODULE]
    kernel32.FreeLibrary(mwdll._handle)
