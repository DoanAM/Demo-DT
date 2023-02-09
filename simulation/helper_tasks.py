import os
import pandas as pd
import numpy as np
from pathlib import Path
from .models import PredictedData
from django.core.files import File
import shutil
from django.conf import settings


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
            _df = df.iloc[line]
            timestamp = _df['Timestamp']

            pred_timestamp = pred_data.loc[:, 'Timestamp']
            timestampIdx = np.searchsorted(pred_timestamp, timestamp)
            actualTimestamp = pred_timestamp.iloc[timestampIdx]

            obj = PredictedData.objects.get(timestamp=actualTimestamp)
            with filepath.open(mode="rb") as f:
                obj.stlPath = File(f, name=relativeFilepath)
                obj.save()
