from django.db import models
from django.contrib.postgres.fields import ArrayField
import time
import os
from pathlib import Path


# def upload_path(instance, filename):
#     timestamp = str(round(time.time()))
#     path = Path("CSV_Dateien", timestamp + "_" +
#                 os.path.splitext(filename)[0], timestamp + "_" + filename)
#     return "CSV_Dateien/"+'/'.join([timestamp + "_" + os.path.splitext(filename)[0], timestamp + "_" + filename])


# # Create your models here.


# class Simulation(models.Model):
#     sim_ID = models.AutoField(primary_key=True)
#     timestamp = models.BigIntegerField(
#         db_column='Timestamp')
#     nc_file = models.FileField(blank=True, null=True, upload_to=upload_path)
#     csv_file = models.FileField(blank=True, null=True)
#     precision = models.FloatField(blank=True, null=True)
#     finished = models.BooleanField(default=False)

#     def __str__(self):
#         return self.timestamp


# class PredictedData(models.Model):
#     Timestamp = models.BigIntegerField(
#         db_column='Timestamp', primary_key=True, )
#     XCurrPos = models.FloatField(db_column='XCurrPos', blank=True, null=True)
#     YCurrPos = models.FloatField(db_column='YCurrPos', blank=True, null=True)
#     ZCurrPos = models.FloatField(db_column='ZCurrPos', blank=True, null=True)
#     S1Actrev = models.FloatField(db_column='S1Actrev', blank=True, null=True)
#     Actfeed = models.FloatField(db_column='Actfeed', blank=True, null=True)
#     Area = models.FloatField(db_column='Area', blank=True, null=True)
#     ToolID = models.IntegerField(db_column='ToolID', blank=True, null=True)
#     Depth = models.FloatField(db_column='Depth', blank=True, null=True)
#     Width = models.FloatField(db_column='Width', blank=True, null=True)
#     Removal_Volume = models.FloatField(
#         db_column='Removal_Volume', blank=True, null=True)
#     Angles = models.TextField(db_column='Angles', blank=True, null=True)
#     S1ActAccel = models.FloatField(
#         db_column='S1ActAccel', blank=True, null=True)
#     XCurrVel = models.FloatField(db_column='XCurrVel', blank=True, null=True)
#     XCurrAccel = models.FloatField(
#         db_column='XCurrAccel', blank=True, null=True)
#     YCurrVel = models.FloatField(db_column='YCurrVel', blank=True, null=True)
#     YCurrAccel = models.FloatField(
#         db_column='YCurrAccel', blank=True, null=True)
#     ZCurrVel = models.FloatField(db_column='ZCurrVel', blank=True, null=True)
#     ZCurrAccel = models.FloatField(
#         db_column='ZCurrAccel', blank=True, null=True)
#     Angle_Mean = models.FloatField(
#         db_column='Angle_Mean', blank=True, null=True)
#     Angle_Sin = models.FloatField(
#         db_column='Angle_Sin', blank=True, null=True)
#     Angle_Cos = models.FloatField(
#         db_column='Angle_Cos', blank=True, null=True)
#     ChipThickness = models.FloatField(
#         db_column='ChipThickness', blank=True, null=True)
#     taskID = models.IntegerField(
#         db_column='taskID', blank=True, null=True)
#     PredOriginS1ActTrq = models.FloatField(
#         db_column='PredOriginS1ActTrq', blank=True, null=True)
#     PredOriginXActTrq = models.FloatField(
#         db_column='PredOriginXActTrq', blank=True, null=True)
#     PredOriginYActTrq = models.FloatField(
#         db_column='PredOriginYActTrq', blank=True, null=True)
#     PredOriginY2ActTrq = models.FloatField(
#         db_column='PredOriginY2ActTrq', blank=True, null=True)
#     PredOriginZActTrq = models.FloatField(
#         db_column='PredOriginZActTrq', blank=True, null=True)
#     simulation = models.ForeignKey(
#         Simulation, on_delete=models.CASCADE, db_column='Simulation',)
#     stlPath = models.FileField(max_length=255,
#                                blank=True, null=True)
