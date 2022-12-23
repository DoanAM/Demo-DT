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


def set_tool(mwdll, fDiameter, fDiameterTop, fShoulderHeight, fHeight, tool_id):
    """
    create end milling tool in mw cam simulation
    :param mwdll: dll file
    :param fDiameter: cutter diameter
    :param fDiameterTop: holder diameter
    :param fShoulderHeight: whole shaft length
    :param fHeight: cutter shaft length
    :param tool_id: tool id in mw cam
    :return: None
    """
    fDiameter_c = ct.c_float(fDiameter)
    fDiameterTop_c = ct.c_float(fDiameterTop)
    fShoulderHeight_c = ct.c_float(fShoulderHeight)
    fHeight_c = ct.c_float(fHeight)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool(fDiameter_c, fDiameterTop_c,
                   fShoulderHeight_c, fHeight_c, tool_id_c)


def set_tool_chamfer(mwdll, cDiameter, cDiameterOut, cDiameterTop, cShoulderHeight, cHeight, taperangle, tool_id):
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
    cDiameter_c = ct.c_float(cDiameter)
    cDiameterOut_c = ct.c_float(cDiameterOut)
    cDiameterTop_c = ct.c_float(cDiameterTop)
    cShoulderHeight_c = ct.c_float(cShoulderHeight)
    cHeight_c = ct.c_float(cHeight)
    taperangle_c = ct.c_float(taperangle)
    tool_id_c = ct.c_int(tool_id)
    mwdll.set_tool_chamfer(cDiameter_c, cDiameterOut_c, cDiameterTop_c,
                           cShoulderHeight_c, cHeight_c, taperangle_c, tool_id_c)


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
    kernel32 = ct.WinDLL('kernel32', use_last_error=True)
    kernel32.FreeLibrary.argtypes = [ct.wintypes.HMODULE]
    kernel32.FreeLibrary(mwdll._handle)
