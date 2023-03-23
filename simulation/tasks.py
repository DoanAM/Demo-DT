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
from .helper_tasks import copyDll, listStlFiles, map_column_name_to_field_name
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


@shared_task
def runSimulation(timestamp, precision):
    #obj = Simulation.objects.last()
    obj = Simulation.objects.get(timestamp=timestamp)
    pathToFile = obj.nc_file.url
    #pathToFile = r"C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\Versuchsteil_Quadrant_7\Versuchsteil_Quadrant_7.NC"
    print("Path to File is: ", pathToFile)
    pathToFileParent = os.path.split(pathToFile)[0]
    fileName = Path(pathToFile).stem
    instanceKey = ''.join(random.choices(
        string.ascii_uppercase + string.digits, k=10))
    print("Path to Fileparent is: ", pathToFileParent)
    copyDll(fileName)
    time.sleep(2)
    mwdll2 = ct.cdll.LoadLibrary(
        str(Path(settings.MEDIA_ROOT) / "CSV_Dateien" / fileName / "MwCamSimLib.dll"))

    SimHandler(fileName, mwdll2, precision, instanceKey, )

    pathToCsv = Path(settings.MEDIA_ROOT) / "CSV_Dateien" / \
        fileName / "PredData.csv"

    with open(pathToCsv, "r") as f:
        reader = csv.reader(f)
        header = next(reader)
        # Map the column names to the field names
        field_names = [f.name for f in PredictedData._meta.get_fields()]
        data_fields = [field for field in header if field in field_names]
        print("Data_fields is: ", data_fields)
        for row in reader:
            # Create a dictionary of field names and values from the row
            data_dict = {field: value for field, value in zip(
                header, row) if field in data_fields}
            data_dict['simulation'] = obj
            data_dict['stlPath'] = None
            # Insert data into the database
            instance = PredictedData(**data_dict)
            instance.save()

    listStlFiles(Path(settings.MEDIA_ROOT) /
                 "CSV_Dateien" / fileName, fileName)
    obj.finished = True
    obj.save()
    # time.sleep(5)


@shared_task
def testTask(number):
    print(number)
