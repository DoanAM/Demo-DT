from __future__ import absolute_import, unicode_literals
from simulation.machine_learning.Code.SimPy.main_vnck import SimHandler
from .models import PredictedData, Simulation
from celery import shared_task
from pathlib import Path
import os
import csv
import random
import string
import time
import sys
import shutil
import ctypes as ct
from ctypes import *


def uploadCsv(path):
    # r"\Data\CSV_Dateien\Versuchsteil_Quadrant_test\PredData.csv"
    with open(path) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            _, created = PredictedData.objects.get_or_create(
                timestamp=row[1],
                xcurrpos=row[2],
                ycurrpos=row[3],
            )


def copyDll(pathToFileParent):
    shutil.copy(r"simulation\machine_learning\Code\SimPy\MwCamSimLib.dll",
                pathToFileParent)


def getCsvDirectory():
    obj = Simulation.objects.get(sim_ID=1)
    print()


def getName():
    obj = Simulation.objects.last()
    pathToFile = obj.nc_file.url
    pathToFileParent = os.path.split(pathToFile)[0]
    fileName = Path(pathToFile).stem
    print(r"C:/Users/Minh/Documents/Uni/MasterThesis/Project/aicom-dt/" + pathToFileParent + "/"
          "PredData.csv")

# fix paths
# fix dlls


@shared_task
def runSimulation():
    obj = Simulation.objects.last()
    pathToFile = obj.nc_file.url
    print(pathToFile)
    pathToFileParent = os.path.split(pathToFile)[0]
    fileName = Path(pathToFile).stem
    instanceKey = ''.join(random.choices(
        string.ascii_uppercase + string.digits, k=10))
    print(pathToFileParent)
    os.popen(
        rf'copy C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\MwCamSimLib.dll C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\MwCamSimLib_{instanceKey}.dll')
    time.sleep(2)
    mwdll2 = ct.cdll.LoadLibrary(
        rf"C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\MwCamSimLib_{instanceKey}.dll")
    SimHandler(fileName, mwdll2, instanceKey)
    uploadCsv(r"C:/Users/Minh/Documents/Uni/MasterThesis/Project/aicom-dt/" + pathToFileParent + "/"
              "PredData.csv")
    obj.finished = True
    obj.save()
    time.sleep(5)
