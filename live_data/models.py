from django.db import models


def upload_path(instance, filename):
    return '/'.join("img"+filename)


class Auxiliary(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True)
    activatemicrojetmediumexternal2 = models.BooleanField(
        db_column='ActivateMicrojetMediumExternal2', blank=True, null=True)
    activatemicrojetmediuminternal2 = models.BooleanField(
        db_column='ActivateMicrojetMediumInternal2', blank=True, null=True)
    vacuumactivate = models.BooleanField(
        db_column='VacuumActivate', blank=True, null=True)
    coolingunitactivate = models.BooleanField(
        db_column='CoolingUnitActivate', blank=True, null=True)
    activateblowclearworkpiece = models.BooleanField(
        db_column='ActivateBlowClearWorkpiece', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'auxiliary'


class Cnc(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True,)
    xcurrpos = models.IntegerField(db_column='XCurrPos', blank=True, null=True)
    xactpos = models.IntegerField(db_column='XActPos', blank=True, null=True)
    zcurrpos = models.IntegerField(db_column='ZCurrPos', blank=True, null=True)
    zactpos = models.IntegerField(db_column='ZActPos', blank=True, null=True)
    ycurrpos = models.IntegerField(db_column='YCurrPos', blank=True, null=True)
    yactpos = models.IntegerField(db_column='YActPos', blank=True, null=True)
    y2currpos = models.IntegerField(
        db_column='Y2CurrPos', blank=True, null=True)
    y2actpos = models.IntegerField(db_column='Y2ActPos', blank=True, null=True)
    s1actrev = models.IntegerField(db_column='S1Actrev', blank=True, null=True)
    s1currrev = models.IntegerField(
        db_column='S1Currrev', blank=True, null=True)
    s1cmdrev = models.IntegerField(db_column='S1Cmdrev', blank=True, null=True)
    actfeed = models.IntegerField(db_column='Actfeed', blank=True, null=True)
    actblocknr = models.IntegerField(
        db_column='Actblocknr', blank=True, null=True)
    tbvec0 = models.IntegerField(blank=True, null=True)
    tbvec1 = models.IntegerField(blank=True, null=True)
    tbvec2 = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'cnc'


class Drive(models.Model):

    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True)

    xenc2pos = models.IntegerField(db_column='XEnc2Pos', blank=True, null=True)

    xacttrq = models.SmallIntegerField(
        db_column='XActTrq', blank=True, null=True)

    xfolldist = models.IntegerField(
        db_column='XFollDist', blank=True, null=True)

    xenc1vel = models.IntegerField(db_column='XEnc1Vel', blank=True, null=True)

    xenc2vel = models.IntegerField(db_column='XEnc2Vel', blank=True, null=True)

    xenc1pos = models.IntegerField(db_column='XEnc1Pos', blank=True, null=True)

    xenc1acc = models.IntegerField(db_column='XEnc1Acc', blank=True, null=True)

    xvelerror = models.IntegerField(
        db_column='XVelError', blank=True, null=True)

    xmottemp = models.IntegerField(db_column='XMotTemp', blank=True, null=True)

    zenc2pos = models.IntegerField(db_column='ZEnc2Pos', blank=True, null=True)

    zacttrq = models.SmallIntegerField(
        db_column='ZActTrq', blank=True, null=True)

    zfolldist = models.IntegerField(
        db_column='ZFollDist', blank=True, null=True)

    zenc1vel = models.IntegerField(db_column='ZEnc1Vel', blank=True, null=True)

    zenc2vel = models.IntegerField(db_column='ZEnc2Vel', blank=True, null=True)

    zenc1pos = models.IntegerField(db_column='ZEnc1Pos', blank=True, null=True)

    zenc1acc = models.IntegerField(db_column='ZEnc1Acc', blank=True, null=True)

    zvelerror = models.IntegerField(
        db_column='ZVelError', blank=True, null=True)

    zmottemp = models.IntegerField(db_column='ZMotTemp', blank=True, null=True)

    yenc2pos = models.IntegerField(db_column='YEnc2Pos', blank=True, null=True)

    yacttrq = models.SmallIntegerField(
        db_column='YActTrq', blank=True, null=True)

    yfolldist = models.IntegerField(
        db_column='YFollDist', blank=True, null=True)

    yenc1vel = models.IntegerField(db_column='YEnc1Vel', blank=True, null=True)

    yenc2vel = models.IntegerField(db_column='YEnc2Vel', blank=True, null=True)

    yenc1pos = models.IntegerField(db_column='YEnc1Pos', blank=True, null=True)

    yenc1acc = models.IntegerField(db_column='YEnc1Acc', blank=True, null=True)

    yvelerror = models.IntegerField(
        db_column='YVelError', blank=True, null=True)

    ymottemp = models.IntegerField(db_column='YMotTemp', blank=True, null=True)

    y2enc2pos = models.IntegerField(
        db_column='Y2Enc2Pos', blank=True, null=True)

    y2acttrq = models.SmallIntegerField(
        db_column='Y2ActTrq', blank=True, null=True)

    y2folldist = models.IntegerField(
        db_column='Y2FollDist', blank=True, null=True)

    y2enc1vel = models.IntegerField(
        db_column='Y2Enc1Vel', blank=True, null=True)

    y2enc2vel = models.IntegerField(
        db_column='Y2Enc2Vel', blank=True, null=True)

    y2enc1pos = models.IntegerField(
        db_column='Y2Enc1Pos', blank=True, null=True)

    y2enc1acc = models.IntegerField(
        db_column='Y2Enc1Acc', blank=True, null=True)

    y2velerror = models.IntegerField(
        db_column='Y2VelError', blank=True, null=True)

    y2mottemp = models.IntegerField(
        db_column='Y2MotTemp', blank=True, null=True)

    s1encpos = models.IntegerField(db_column='S1EncPos', blank=True, null=True)

    s1acttrq = models.SmallIntegerField(
        db_column='S1ActTrq', blank=True, null=True)

    s1follerr = models.IntegerField(
        db_column='S1FollErr', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'drive'


class Prog(models.Model):

    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)
    materialnnumber = models.IntegerField(
        db_column='Materialnumber', blank=True, null=True)
    serialnumber = models.IntegerField(
        db_column='Serialnumber', blank=True, null=True)
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

    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )

    id = models.BigIntegerField(db_column='ID', blank=True, null=True)

    number = models.IntegerField(db_column='Number', blank=True, null=True)
    category = models.CharField(max_length=81, blank=True, null=True)

    artnr = models.CharField(
        db_column='ArtNr', max_length=81, blank=True, null=True)

    name = models.CharField(
        db_column='Name', max_length=81, blank=True, null=True)

    length = models.FloatField(db_column='Length', blank=True, null=True)

    diameter = models.FloatField(db_column='Diameter', blank=True, null=True)
    path = models.FloatField(db_column='Path', blank=True, null=True)

    life = models.FloatField(db_column='Life', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'tool'


class Wcs(models.Model):

    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )

    isactive = models.SmallIntegerField(
        db_column='isActive', blank=True, null=True)

    x = models.FloatField(db_column='X', blank=True, null=True)

    y = models.FloatField(db_column='Y', blank=True, null=True)

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


class Images(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )
    img = models.ImageField(upload_to="images/")
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)


""" class Videos(models.Model):
    id = models.AutoField(primary_key=True)
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)
    video_file = models.FileField(blank=True, null=True) """
