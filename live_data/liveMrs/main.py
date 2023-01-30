import ctypes as ct
from ctypes import *
import time
import pathlib
from django.conf import settings


def doCut():
    # r"C:\Users\Minh\OneDrive\MasterThesis\Skripts\LiveMRS\Lesson02_StartMesh.stl"
    startMeshLocation = r"Lesson02_StartMesh.stl"
    pathStock = ct.c_char_p(
        startMeshLocation.encode())
    x_start_c = ct.c_float(-5)
    y_start_c = ct.c_float(-5)
    z_start_c = ct.c_float(-5)
    x_end_c = ct.c_float(5)
    y_end_c = ct.c_float(5)
    z_end_c = ct.c_float(5)

    # init
    mw_dll = ct.cdll.LoadLibrary(r"MwCamSimLib/x64/Debug/MwCamSimLib.dll")
    mw_dll.init()
    mw_dll.set_precision(ct.c_float(1))
    mw_dll.set_stock(pathStock)
    mw_dll.createTool()
    mw_dll.cut(x_start_c, y_start_c, z_start_c, x_end_c, y_end_c, z_end_c)


def createStock(xStart, yStart, zStart, xEnd, yEnd, zEnd, location):
    libraryPath = pathlib.Path(settings.BASE_DIR, "live_data",
                               "liveMrs", "MwCamSimLib", "x64", "Debug", "MwCamSimLib.dll")
    location_c = ct.c_char_p(location.encode())
    x_start_c = ct.c_float(xStart)
    y_start_c = ct.c_float(yStart)
    z_start_c = ct.c_float(zStart)
    x_end_c = ct.c_float(xEnd)
    y_end_c = ct.c_float(yEnd)
    z_end_c = ct.c_float(zEnd)
    mw_dll = ct.cdll.LoadLibrary(str(libraryPath))
    mw_dll.init()
    mw_dll.set_precision(ct.c_float(1))
    mw_dll.new_stock(x_start_c, y_start_c, z_start_c,
                     x_end_c, y_end_c, z_end_c, location_c)


if __name__ == "__main__":
    start_time = time.time()

    createStock(-5, -5, -5, 5, 5, 5,
                "C:\\Users\\Minh\\OneDrive\\MasterThesis\\Skripts\\LiveMRS\\StartMesh.stl")
    pathlib.Path(
        "C:\\Users\\Minh\\OneDrive\\MasterThesis\\Skripts\\LiveMRS\\StartMesh.stl").unlink()
    createStock(0, 0, 0, 5, 5, 5,
                "C:\\Users\\Minh\\OneDrive\\MasterThesis\\Skripts\\LiveMRS\\StartMesh2.stl")

    end_time = time.time()
    print("Total execution time: ", end_time - start_time)
