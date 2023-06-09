# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Auxiliary(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    activatemicrojetmediumexternal2 = models.SmallIntegerField(
        db_column='ActivateMicrojetMediumExternal2', blank=True, null=True)  # Field name made lowercase.
    activatemicrojetmediuminternal2 = models.SmallIntegerField(
        db_column='ActivateMicrojetMediumInternal2', blank=True, null=True)  # Field name made lowercase.
    # Field name made lowercase.
    vacuumactivate = models.SmallIntegerField(
        db_column='VacuumActivate', blank=True, null=True)
    # Field name made lowercase.
    coolingunitactivate = models.SmallIntegerField(
        db_column='CoolingUnitActivate', blank=True, null=True)
    activateblowclearworkpiece = models.SmallIntegerField(
        db_column='ActivateBlowClearWorkpiece', blank=True, null=True)  # Field name made lowercase.

    class Meta:
        managed = False
        db_table = 'auxiliary'


class Cnc(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    # Field name made lowercase.
    xcurrpos = models.IntegerField(db_column='XCurrPos', blank=True, null=True)
    # Field name made lowercase.
    xactpos = models.IntegerField(db_column='XActPos', blank=True, null=True)
    # Field name made lowercase.
    zcurrpos = models.IntegerField(db_column='ZCurrPos', blank=True, null=True)
    # Field name made lowercase.
    zactpos = models.IntegerField(db_column='ZActPos', blank=True, null=True)
    # Field name made lowercase.
    ycurrpos = models.IntegerField(db_column='YCurrPos', blank=True, null=True)
    # Field name made lowercase.
    yactpos = models.IntegerField(db_column='YActPos', blank=True, null=True)
    # Field name made lowercase.
    y2currpos = models.IntegerField(
        db_column='Y2CurrPos', blank=True, null=True)
    # Field name made lowercase.
    y2actpos = models.IntegerField(db_column='Y2ActPos', blank=True, null=True)
    # Field name made lowercase.
    s1actrev = models.IntegerField(db_column='S1Actrev', blank=True, null=True)
    # Field name made lowercase.
    s1currrev = models.IntegerField(
        db_column='S1Currrev', blank=True, null=True)
    # Field name made lowercase.
    s1cmdrev = models.IntegerField(db_column='S1Cmdrev', blank=True, null=True)
    # Field name made lowercase.
    actfeed = models.IntegerField(db_column='Actfeed', blank=True, null=True)
    # Field name made lowercase.
    actblocknr = models.IntegerField(
        db_column='Actblocknr', blank=True, null=True)
    tbvec0 = models.IntegerField(blank=True, null=True)
    tbvec1 = models.IntegerField(blank=True, null=True)
    tbvec2 = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'cnc'


class Drive(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    # Field name made lowercase.
    xenc2pos = models.IntegerField(db_column='XEnc2Pos', blank=True, null=True)
    # Field name made lowercase.
    xacttrq = models.SmallIntegerField(
        db_column='XActTrq', blank=True, null=True)
    # Field name made lowercase.
    xfolldist = models.IntegerField(
        db_column='XFollDist', blank=True, null=True)
    # Field name made lowercase.
    xenc1vel = models.IntegerField(db_column='XEnc1Vel', blank=True, null=True)
    # Field name made lowercase.
    xenc2vel = models.IntegerField(db_column='XEnc2Vel', blank=True, null=True)
    # Field name made lowercase.
    xenc1pos = models.IntegerField(db_column='XEnc1Pos', blank=True, null=True)
    # Field name made lowercase.
    xenc1acc = models.IntegerField(db_column='XEnc1Acc', blank=True, null=True)
    # Field name made lowercase.
    xvelerror = models.IntegerField(
        db_column='XVelError', blank=True, null=True)
    # Field name made lowercase.
    xmottemp = models.IntegerField(db_column='XMotTemp', blank=True, null=True)
    # Field name made lowercase.
    zenc2pos = models.IntegerField(db_column='ZEnc2Pos', blank=True, null=True)
    # Field name made lowercase.
    zacttrq = models.SmallIntegerField(
        db_column='ZActTrq', blank=True, null=True)
    # Field name made lowercase.
    zfolldist = models.IntegerField(
        db_column='ZFollDist', blank=True, null=True)
    # Field name made lowercase.
    zenc1vel = models.IntegerField(db_column='ZEnc1Vel', blank=True, null=True)
    # Field name made lowercase.
    zenc2vel = models.IntegerField(db_column='ZEnc2Vel', blank=True, null=True)
    # Field name made lowercase.
    zenc1pos = models.IntegerField(db_column='ZEnc1Pos', blank=True, null=True)
    # Field name made lowercase.
    zenc1acc = models.IntegerField(db_column='ZEnc1Acc', blank=True, null=True)
    # Field name made lowercase.
    zvelerror = models.IntegerField(
        db_column='ZVelError', blank=True, null=True)
    # Field name made lowercase.
    zmottemp = models.IntegerField(db_column='ZMotTemp', blank=True, null=True)
    # Field name made lowercase.
    yenc2pos = models.IntegerField(db_column='YEnc2Pos', blank=True, null=True)
    # Field name made lowercase.
    yacttrq = models.SmallIntegerField(
        db_column='YActTrq', blank=True, null=True)
    # Field name made lowercase.
    yfolldist = models.IntegerField(
        db_column='YFollDist', blank=True, null=True)
    # Field name made lowercase.
    yenc1vel = models.IntegerField(db_column='YEnc1Vel', blank=True, null=True)
    # Field name made lowercase.
    yenc2vel = models.IntegerField(db_column='YEnc2Vel', blank=True, null=True)
    # Field name made lowercase.
    yenc1pos = models.IntegerField(db_column='YEnc1Pos', blank=True, null=True)
    # Field name made lowercase.
    yenc1acc = models.IntegerField(db_column='YEnc1Acc', blank=True, null=True)
    # Field name made lowercase.
    yvelerror = models.IntegerField(
        db_column='YVelError', blank=True, null=True)
    # Field name made lowercase.
    ymottemp = models.IntegerField(db_column='YMotTemp', blank=True, null=True)
    # Field name made lowercase.
    y2enc2pos = models.IntegerField(
        db_column='Y2Enc2Pos', blank=True, null=True)
    # Field name made lowercase.
    y2acttrq = models.SmallIntegerField(
        db_column='Y2ActTrq', blank=True, null=True)
    # Field name made lowercase.
    y2folldist = models.IntegerField(
        db_column='Y2FollDist', blank=True, null=True)
    # Field name made lowercase.
    y2enc1vel = models.IntegerField(
        db_column='Y2Enc1Vel', blank=True, null=True)
    # Field name made lowercase.
    y2enc2vel = models.IntegerField(
        db_column='Y2Enc2Vel', blank=True, null=True)
    # Field name made lowercase.
    y2enc1pos = models.IntegerField(
        db_column='Y2Enc1Pos', blank=True, null=True)
    # Field name made lowercase.
    y2enc1acc = models.IntegerField(
        db_column='Y2Enc1Acc', blank=True, null=True)
    # Field name made lowercase.
    y2velerror = models.IntegerField(
        db_column='Y2VelError', blank=True, null=True)
    # Field name made lowercase.
    y2mottemp = models.IntegerField(
        db_column='Y2MotTemp', blank=True, null=True)
    # Field name made lowercase.
    s1encpos = models.IntegerField(db_column='S1EncPos', blank=True, null=True)
    # Field name made lowercase.
    s1acttrq = models.SmallIntegerField(
        db_column='S1ActTrq', blank=True, null=True)
    # Field name made lowercase.
    s1follerr = models.IntegerField(
        db_column='S1FollErr', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'drive'


class Prog(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    # Field name made lowercase.
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)
    # Field name made lowercase.
    materialnumber = models.IntegerField(
        db_column='Materialnumber', blank=True, null=True)
    # Field name made lowercase.
    serialnumber = models.IntegerField(
        db_column='Serialnumber', blank=True, null=True)
    # Field name made lowercase.
    operation = models.CharField(
        db_column='Operation', max_length=81, blank=True, null=True)
    # Field name made lowercase.
    m190 = models.SmallIntegerField(db_column='M190', blank=True, null=True)
    # Field name made lowercase.
    m191 = models.SmallIntegerField(db_column='M191', blank=True, null=True)
    # Field name made lowercase.
    m192 = models.SmallIntegerField(db_column='M192', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'prog'


class Tool(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    # Field name made lowercase.
    id = models.BigIntegerField(db_column='ID', blank=True, null=True)
    # Field name made lowercase.
    number = models.IntegerField(db_column='Number', blank=True, null=True)
    category = models.CharField(max_length=81, blank=True, null=True)
    # Field name made lowercase.
    artnr = models.CharField(
        db_column='ArtNr', max_length=81, blank=True, null=True)
    # Field name made lowercase.
    name = models.CharField(
        db_column='Name', max_length=81, blank=True, null=True)
    # Field name made lowercase.
    length = models.FloatField(db_column='Length', blank=True, null=True)
    # Field name made lowercase.
    diameter = models.FloatField(db_column='Diameter', blank=True, null=True)
    # Field name made lowercase.
    path = models.FloatField(db_column='Path', blank=True, null=True)
    # Field name made lowercase.
    life = models.FloatField(db_column='Life', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'tool'


class Wcs(models.Model):
    # Field name made lowercase.
    timestamp = models.BigIntegerField(db_column='Timestamp')
    # Field name made lowercase.
    isactive = models.SmallIntegerField(
        db_column='isActive', blank=True, null=True)
    # Field name made lowercase.
    x = models.FloatField(db_column='X', blank=True, null=True)
    # Field name made lowercase.
    y = models.FloatField(db_column='Y', blank=True, null=True)
    # Field name made lowercase.
    z = models.FloatField(db_column='Z', blank=True, null=True)
    alpha = models.FloatField(blank=True, null=True)
    beta = models.FloatField(blank=True, null=True)
    gamma = models.FloatField(blank=True, null=True)
    # Field name made lowercase.
    minedgex = models.FloatField(db_column='MinEdgeX', blank=True, null=True)
    # Field name made lowercase.
    minedgey = models.FloatField(db_column='MinEdgeY', blank=True, null=True)
    # Field name made lowercase.
    minedgez = models.FloatField(db_column='MinEdgeZ', blank=True, null=True)
    # Field name made lowercase.
    maxedgex = models.FloatField(db_column='MaxEdgeX', blank=True, null=True)
    # Field name made lowercase.
    maxedgey = models.FloatField(db_column='MaxEdgeY', blank=True, null=True)
    # Field name made lowercase.
    maxedgez = models.FloatField(db_column='MaxEdgeZ', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'wcs'
