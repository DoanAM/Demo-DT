from django.db import models


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

    # Field name made lowercase.
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)

    materialnnumber = models.IntegerField(
        db_column='Materialnumber', blank=True, null=True)

    serialnumber = models.IntegerField(
        db_column='Serialnumber', blank=True, null=True)

    operation = models.CharField(
        db_column='Operation', max_length=81, blank=True, null=True)

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


class StlFile(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True, )
    StlFile = models.FileField(blank=True, null=True)
    programname = models.CharField(
        db_column='Programname', max_length=81, blank=True, null=True)


class ToolsInChanger(models.Model):
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    tool_id = models.BigIntegerField(db_column='Tool ID', primary_key=True)
    # Field name made lowercase.
    name = models.TextField(db_column='Name', blank=True, null=True)
    # Field name made lowercase.
    category = models.TextField(db_column='Category', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    dominating_property = models.TextField(
        db_column='dominating Property', blank=True, null=True)
    vendor = models.TextField(blank=True, null=True)
    # Field renamed to remove unsuitable characters.
    max_tool_path = models.TextField(
        db_column='max. tool path', blank=True, null=True)
    # Field renamed to remove unsuitable characters.
    max_tool_life = models.TextField(
        db_column='max. tool life', blank=True, null=True)
    # Field renamed to remove unsuitable characters.
    article_number = models.TextField(
        db_column='article number', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    current_total_path = models.FloatField(
        db_column='current total Path', blank=True, null=True)
    # Field renamed to remove unsuitable characters.
    current_total_life = models.FloatField(
        db_column='current total life', blank=True, null=True)
    # Field renamed to remove unsuitable characters.
    tool_number = models.BigIntegerField(
        db_column='tool number', blank=True, null=True)
    comment = models.TextField(blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_body_length = models.FloatField(
        db_column='real Body Length', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_reference_bodylength = models.FloatField(
        db_column='real Reference BodyLength', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters. Field renamed because it started with '_'.
    field_real_diameter = models.TextField(
        db_column='real Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_shoulder_length = models.TextField(
        db_column='real Shoulder Length', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_flutelength = models.TextField(
        db_column='real FluteLength', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_overall_length = models.TextField(
        db_column='real Overall Length', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_shoulder_diameter = models.TextField(
        db_column='real Shoulder Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_tip_angle = models.TextField(
        db_column='real Tip Angle', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_corner_radius = models.TextField(
        db_column='real Corner Radius', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_number_of_flutes = models.TextField(
        db_column='real Number Of Flutes', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_shaft_diameter = models.TextField(
        db_column='real Shaft Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_threadpitch = models.TextField(
        db_column='real ThreadPitch', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    real_tipdiameter = models.TextField(
        db_column='real TipDiameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters. Field renamed because it started with '_'.
    field_nominal_diameter = models.FloatField(
        db_column='nominal Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_flutelength = models.TextField(
        db_column='nominal FluteLength', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_number_of_flutes = models.TextField(
        db_column='nominal Number Of Flutes', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_shoulder_diameter = models.TextField(
        db_column='nominal Shoulder Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_shoulder_length = models.TextField(
        db_column='nominal Shoulder Length', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_shaft_diameter = models.FloatField(
        db_column='nominal Shaft Diameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_overall_length = models.FloatField(
        db_column='nominal Overall Length', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_tip_angle = models.TextField(
        db_column='nominal Tip Angle', blank=True, null=True)
    # Field name made lowercase.
    taperangle = models.TextField(
        db_column='TaperAngle', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_tipdiameter = models.TextField(
        db_column='nominal TipDiameter', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_corner_radius = models.TextField(
        db_column='nominal Corner Radius', blank=True, null=True)
    # Field name made lowercase.
    threadangle = models.TextField(
        db_column='ThreadAngle', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_threadpitch = models.TextField(
        db_column='nominal ThreadPitch', blank=True, null=True)
    # Field name made lowercase. Field renamed to remove unsuitable characters.
    nominal_body_length = models.TextField(
        db_column='nominal Body Length', blank=True, null=True)

    class Meta:
        db_table = "toolsInChanger"
