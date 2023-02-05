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
from .helper_tasks import copyDll, listStlFiles
from django.conf import settings


def uploadCsv(path):
    with open(path) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            _, created = PredictedData.objects.get_or_create(
                timestamp=row[1],
                xcurrpos=row[2],
                ycurrpos=row[3],
                zcurrpos=row[4],
                s1actrev=row[5]
                # simulation=simulationObj
            )


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
    #obj = Simulation.objects.last()
    #pathToFile = obj.nc_file.url
    pathToFile = r"C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\Versuchsteil_Quadrant_7\Versuchsteil_Quadrant_7.NC"
    print("Path to File is: ", pathToFile)
    pathToFileParent = os.path.split(pathToFile)[0]
    fileName = Path(pathToFile).stem
    instanceKey = ''.join(random.choices(
        string.ascii_uppercase + string.digits, k=10))
    print("Path to Fileparent is: ", pathToFileParent)
    copyDll(fileName)
    time.sleep(2)
    mwdll2 = ct.cdll.LoadLibrary(
        str(Path(settings.MEDIA_ROOT) / fileName / "MwCamSimLib.dll"))

    SimHandler(fileName, mwdll2, instanceKey)

    # pathToCsv = Path(settings.MEDIA_ROOT) / fileName / "PredData.csv"

    # with open(pathToCsv) as f:
    #     reader = csv.reader(f)
    #     next(reader)
    #     for row in reader:
    #         _, created = PredictedData.objects.get_or_create(
    #             timestamp=row[1],
    #             xcurrpos=row[2],
    #             ycurrpos=row[3],
    #             zcurrpos=row[4],
    #             s1actrev=row[5],
    #             simulation=obj,
    #             stlPath=None
    #         )

    # listStlFiles(Path(settings.MEDIA_ROOT) / fileName, fileName)
    # obj.finished = True
    # obj.save()
    # time.sleep(5)
