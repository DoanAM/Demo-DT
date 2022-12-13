import os
import pandas as pd
import numpy as np
from pathlib import Path
from .models import PredictedData
from django.core.files import File


def copyDll(filename):
    os.popen(
        rf'copy C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\MwCamSimLib.dll C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\{filename}\MwCamSimLib.dll')
    os.popen(
        rf'copy C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\mwsimutil.dll C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\{filename}\mwsimutil.dll')
    os.popen(
        rf'copy C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\mwSupport.dll C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\{filename}\mwSupport.dll')
    os.popen(
        rf'copy C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\simulation\machine_learning\Code\SimPy\mwVerifier.dll C:\Users\Minh\Documents\Uni\MasterThesis\Project\aicom-dt\Data\CSV_Dateien\{filename}\mwVerifier.dll')


def listStlFiles(path, relativePath):
    pathPredData = Path(path) / "PredData.csv"
    pathSimData = Path(path) / "SimPathData.txt"
    pathMrs = Path(path) / "MRS"
    pred_data = pd.read_csv(
        pathPredData)

    df = pd.read_csv(pathSimData, sep=' ')
    for file in os.listdir(pathMrs):
        if file.endswith(".stl"):
            filepath = Path(pathMrs) / file
            relativeFilepath = Path(relativePath) / "MRS" / file
            line = int(Path(file).stem)
            _df = df.iloc[line]
            timestamp = _df['Timestamp']

            pred_timestamp = pred_data.loc[:, 'Timestamp']
            timestampIdx = np.searchsorted(pred_timestamp, timestamp)
            actualTimestamp = pred_timestamp.iloc[timestampIdx]

            obj = PredictedData.objects.get(timestamp=actualTimestamp)
            with filepath.open(mode="rb") as f:
                obj.stlPath = File(f, name=filepath.name)
                obj.save()
