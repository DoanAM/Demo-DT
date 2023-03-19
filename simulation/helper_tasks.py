import os
import pandas as pd
import numpy as np
from pathlib import Path
from .models import PredictedData, Simulation
from django.core.files import File
import shutil
import csv
from django.conf import settings


def map_column_name_to_field_name(column_name, field_names):
    for field_name in field_names:
        if column_name.lower() == field_name.lower():
            return field_name
    return None  # Ignore columns that don't match any field names


def copyDll(filename):  # filename
    shutil.copy(Path(settings.BASE_DIR) / "simulation" / "machine_learning" / "Code" / "SimPy" / "MwCamSimLib.dll",
                Path(settings.MEDIA_ROOT) / "CSV_Dateien" / filename / "MwCamSimLib.dll")
    shutil.copy(Path(settings.BASE_DIR) / "simulation" / "machine_learning" / "Code" / "SimPy" / "mwsimutil.dll",
                Path(settings.MEDIA_ROOT) / "CSV_Dateien" / filename / "mwsimutil.dll")
    shutil.copy(Path(settings.BASE_DIR) / "simulation" / "machine_learning" / "Code" / "SimPy" / "mwSupport.dll",
                Path(settings.MEDIA_ROOT) / "CSV_Dateien" / filename / "mwSupport.dll")
    shutil.copy(Path(settings.BASE_DIR) / "simulation" / "machine_learning" / "Code" / "SimPy" / "mwVerifier.dll",
                Path(settings.MEDIA_ROOT) / "CSV_Dateien" / filename / "mwVerifier.dll")


def listStlFiles(path, fileName):
    pathPredData = Path(path) / "PredData.csv"
    pathSimData = Path(path) / "SimPathData.txt"
    pathMrs = Path(path) / "MRS"
    pred_data = pd.read_csv(
        pathPredData)

    df = pd.read_csv(pathSimData, sep=' ')
    for file in os.listdir(pathMrs):
        if file.endswith(".stl"):
            filepath = Path(pathMrs) / file
            relativeFilepath = Path(fileName) / "MRS" / file
            line = int(Path(file).stem)
            _df = df.iloc[line*10]
            timestamp = _df['Timestamp']

            diff = np.abs(pred_data["Timestamp"] - timestamp)
            timestampIdx = diff.idxmin()
            print("timestampIdx is ", timestampIdx)
            actualTimestamp = pred_data.loc[timestampIdx, "Timestamp"]

            obj = PredictedData.objects.get(Timestamp=actualTimestamp)
            with filepath.open(mode="rb") as f:
                obj.stlPath = File(f, name=relativeFilepath)
                obj.save()


def uploadToDatabase(pathToCsv=r"Data\CSV_Dateien\1679238901_abc\PredData.csv"):
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

            # Insert data into the database
            instance = PredictedData(**data_dict)
            instance.save()
        # for row in reader:
        #     data_dict = {}
        #     for i in range(1, len(header)):
        #         field_name = map_column_name_to_field_name(
        #             header[i], field_names)
        #         if field_name is not None and field_name in data_fields:
        #             data_dict[field_name] = row[i]
        #         data_dict['stlPath'] = None
        #         print("data_dict is: ", data_dict)
        #         instance = PredictedData(**data_dict)
        #         instance.save()
