#######################
#    User Config      #
#######################
import os
import json
from django.conf import settings
from pathlib import Path
from ....models import Simulation
"""
Following configuration should be defined by user in the specific application context
"""
absolute_data_path = Path(
    settings.MEDIA_ROOT, "CSV_Dateien")

work_path = settings.BASE_DIR
# data root folder both for VNCK data and Real machine data:
data_rootpath = os.path.relpath(absolute_data_path, work_path)

# "c:\\Users\\Minh\\OneDrive\\MasterThesis\\Input\\aicom-cl-main\\Data\\CSV_Dateien"
#os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), "Data", "CSV_Dateien")
#os.path.relpath(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), "Data", "CSV_Dateien"), os.path.dirname(__file__))
# "..\\..\\Data\\CSV_Dateien"


# real tool path:
toolpath_filename = 'PathData.txt'

# mw cam simulation result based on real cnc data:
result_real_filename = 'ResultData.txt'

# generated CAD model based on real cnc data
mesh_real_filename = 'MeshData.stl'

# sim tool path:
simtoolpath_filename = 'SimPathData.txt'

# mw cam simulation result based on simulated cnc data:
result_sim_filename = 'SimResultData.txt'

# generated CAD model based on simulated cnc data:
mesh_sim_filename = 'SimMeshData.stl'

# raw machine cnc file
cnc_filename = 'CNCData.csv'

# raw tool file
tool_filename = 'ToolData.csv'

# raw feature file for model learning
train_feature_filename = 'TrainData.csv'

# standardized feature file for model learning
std_train_feature_filename = 'TrainDataStd.csv'

# standardized padding feature file for model learning
std_padding_train_feature_filename = 'TrainPaddingData.csv'

# raw feature file for model evaluation
eval_feature_filename = 'EvalData.csv'

# standardized feature file for model evaluation
std_eval_feature_filename = 'EvalDataStd.csv'

# standardized padding feature file for model learning
std_padding_eval_feature_filename = 'EvalPaddingData.csv'

# raw feature file for application(test)
test_feature_filename = 'TestData.csv'

# standardized feature file for application(test)
std_test_feature_filename = 'TestDataStd.csv'

# standardized padding feature file for application(test)
std_padding_test_feature_filename = 'TestPaddingData.csv'

# inference value for application(test)
pred_filename = 'PredData.csv'
# storage filename for statistic properties for data set:
statistics_json_filename = 'statistic.json'

# machine learning model save path
model_rootpath = "./model/save"

# tool_dict for Versuchsteil Quadrant. Keys are the tool number. Values are diameter and shaft length of the tool
toolJsonPath = os.path.join(os.path.dirname(
    __file__), "tools.json")
with open(toolJsonPath, 'r') as f:
    toolsJson = json.load(f)

ToolDict = toolsJson

bounds = {'x_init': 0, 'y_init': 0, 'z_init': -30,
          'x_end': 90, 'y_end': 95, 'z_end': 0}

# whole feature columns for the feature preprocessing
feature_cols = ["S1Actrev", "Actfeed", "Area", "Depth", "Width", "Removal_Volume", "Angle_Mean", "Angle_Sin",
                "Angle_Cos", "ChipThickness", "S1ActAccel", "XCurrAccel", "YCurrAccel", "ZCurrAccel", "XCurrVel",
                "YCurrVel", "ZCurrVel"]

# model selection:
modelname = "LSTM"

selected_feature_cols = ["S1Actrev", "Actfeed", "S1ActAccel", "XCurrAccel", "YCurrAccel", "ZCurrAccel", "XCurrVel",
                         "YCurrVel", "ZCurrVel", "Area", "Depth", "Width", "Removal_Volume", "Angle_Mean"]

label_cols = ["S1ActTrq", "XActTrq", "YActTrq", "Y2ActTrq", "ZActTrq"]

# hyper parameter for LSTM model:
params_lstm = dict(batch_size=64,
                   learning_rate=1e-3,
                   epochs=50,
                   lstm_hidden_dims=10,
                   share_hidden_dim=[32, 64],
                   sub_hidden_dims=[64, 32, 1],
                   window_size=10,
                   lstm_layers_num=1,
                   # pre-trained model path
                   modelpath=os.path.join(os.path.dirname(
                       __file__), "model", "save", "LSTM", "multi_best.pth")
                   )
# modelpath="./model/save/LSTM/multi_best.pth")

#######################
#    Sim Config       #
#######################
"""
Following configs are for the simulation software. Please only change the value if it is necessary
"""

# cycle time in microsecond in VNCK
cycleTime_vnck = 1000

# channel index in VNCK
channel = 0

# TwinCAT installation path
TcAdsDll_32_folderpath = 'C:\TwinCAT\Common32'
TcAdsDll_64_folderpath = 'C:\TwinCAT\Common64'

# dll path for VNCK:
kernelv_mt_folderpath = os.path.join(os.path.dirname(
    __file__), "kernelv_mt.dll")  # '.\\kernelv_mt.dll'
kernelv_mt64_folderpath = os.path.join(os.path.dirname(
    __file__), "kernelv_mt64.dll")  # '.\\kernelv_mt64.dll'

# lis file for VNCK:
startupfile = os.path.join(os.path.dirname(
    __file__), "listen", "hochlauf.lis").encode()  # b".\\listen\\hochlauf.lis"


# precision of stock in mw cam:
precision_default = Simulation.objects.last().precision

# dll path for mw cam
mwcamlib_path = os.path.join(os.path.dirname(
    __file__), "MwCamSimLib.dll")  # ".\\MwCamSimLib.dll"

# cycle time in millisecond in mw cam:
cycleTime_mw = 10
