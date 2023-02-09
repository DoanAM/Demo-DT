from django.db import models
import time
import os
from pathlib import Path


def upload_path(instance, filename):
    timestamp = str(round(time.time()))
    path = Path("CSV_Dateien", timestamp + "_" +
                os.path.splitext(filename)[0], timestamp + "_" + filename)
    return "CSV_Dateien/"+'/'.join([timestamp + "_" + os.path.splitext(filename)[0], timestamp + "_" + filename])


# Create your models here.


class Simulation(models.Model):
    sim_ID = models.AutoField(primary_key=True)
    timestamp = models.BigIntegerField(
        db_column='Timestamp')
    nc_file = models.FileField(blank=True, null=True, upload_to=upload_path)
    csv_file = models.FileField(blank=True, null=True)
    precision = models.FloatField(blank=True, null=True)
    finished = models.BooleanField(default=False)

    def __str__(self):
        return self.timestamp


class PredictedData(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )
    xcurrpos = models.FloatField(db_column='XCurrPos', blank=True, null=True)
    ycurrpos = models.FloatField(db_column='YCurrPos', blank=True, null=True)
    zcurrpos = models.FloatField(db_column='ZCurrPos', blank=True, null=True)
    s1actrev = models.FloatField(db_column='S1Actrev', blank=True, null=True)
    actfeed = models.FloatField(db_column='Actfeed', blank=True, null=True)
    area = models.FloatField(db_column='Area', blank=True, null=True)
    toolID = models.IntegerField(db_column='ToolID', blank=True, null=True)
    depth = models.FloatField(db_column='Depth', blank=True, null=True)
    width = models.FloatField(db_column='Width', blank=True, null=True)
    removal_volume = models.FloatField(
        db_column='Removal_Volume', blank=True, null=True)
    angles = models.FloatField(db_column='Angles', blank=True, null=True)
    s1ActAccel = models.FloatField(
        db_column='S1ActAccel', blank=True, null=True)
    xCurrVel = models.FloatField(db_column='XCurrVel', blank=True, null=True)
    xCurrAccel = models.FloatField(
        db_column='XCurrAccel', blank=True, null=True)
    yCurrVel = models.FloatField(db_column='YCurrVel', blank=True, null=True)
    yCurrAccel = models.FloatField(
        db_column='YCurrAccel', blank=True, null=True)
    zCurrVel = models.FloatField(db_column='ZCurrVel', blank=True, null=True)
    zCurrAccel = models.FloatField(
        db_column='ZCurrAccel', blank=True, null=True)
    angle_Mean = models.FloatField(
        db_column='Angle_Mean', blank=True, null=True)
    angle_Sin = models.FloatField(
        db_column='Angle_Sin', blank=True, null=True)
    angle_Cos = models.FloatField(
        db_column='Angle_Cos', blank=True, null=True)
    chipThickness = models.FloatField(
        db_column='ChipThickness', blank=True, null=True)
    TaskID = models.IntegerField(
        db_column='taskID', blank=True, null=True)
    predOriginS1ActTrq = models.FloatField(
        db_column='PredOriginS1ActTrq', blank=True, null=True)
    predOriginXActTrq = models.FloatField(
        db_column='PredOriginXActTrq', blank=True, null=True)
    predOriginYActTrq = models.FloatField(
        db_column='PredOriginYActTrq', blank=True, null=True)
    predOriginY2ActTrq = models.FloatField(
        db_column='PredOriginY2ActTrq', blank=True, null=True)
    predOriginZActTrq = models.FloatField(
        db_column='PredOriginZActTrq', blank=True, null=True)
    simulation = models.ForeignKey(
        Simulation, on_delete=models.CASCADE, db_column='Simulation',)
    stlPath = models.FileField(max_length=255,
                               blank=True, null=True)
