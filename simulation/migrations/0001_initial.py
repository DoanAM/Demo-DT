# Generated by Django 4.1.3 on 2023-02-02 20:10

from django.db import migrations, models
import django.db.models.deletion
import simulation.models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Simulation',
            fields=[
                ('sim_ID', models.AutoField(primary_key=True, serialize=False)),
                ('timestamp', models.BigIntegerField(db_column='Timestamp')),
                ('nc_file', models.FileField(blank=True, null=True, upload_to=simulation.models.upload_path)),
                ('csv_file', models.FileField(blank=True, null=True, upload_to='')),
                ('finished', models.BooleanField(default=False)),
            ],
        ),
        migrations.CreateModel(
            name='PredictedData',
            fields=[
                ('timestamp', models.BigIntegerField(db_column='Timestamp', primary_key=True, serialize=False)),
                ('xcurrpos', models.FloatField(blank=True, db_column='XCurrPos', null=True)),
                ('ycurrpos', models.FloatField(blank=True, db_column='YCurrPos', null=True)),
                ('zcurrpos', models.FloatField(blank=True, db_column='ZCurrPos', null=True)),
                ('s1actrev', models.FloatField(blank=True, db_column='S1Actrev', null=True)),
                ('actfeed', models.FloatField(blank=True, db_column='Actfeed', null=True)),
                ('area', models.FloatField(blank=True, db_column='Area', null=True)),
                ('toolID', models.IntegerField(blank=True, db_column='ToolID', null=True)),
                ('depth', models.FloatField(blank=True, db_column='Depth', null=True)),
                ('width', models.FloatField(blank=True, db_column='Width', null=True)),
                ('removal_volume', models.FloatField(blank=True, db_column='Removal_Volume', null=True)),
                ('angles', models.FloatField(blank=True, db_column='Angles', null=True)),
                ('s1ActAccel', models.FloatField(blank=True, db_column='S1ActAccel', null=True)),
                ('xCurrVel', models.FloatField(blank=True, db_column='XCurrVel', null=True)),
                ('xCurrAccel', models.FloatField(blank=True, db_column='XCurrAccel', null=True)),
                ('yCurrVel', models.FloatField(blank=True, db_column='YCurrVel', null=True)),
                ('yCurrAccel', models.FloatField(blank=True, db_column='YCurrAccel', null=True)),
                ('zCurrVel', models.FloatField(blank=True, db_column='ZCurrVel', null=True)),
                ('zCurrAccel', models.FloatField(blank=True, db_column='ZCurrAccel', null=True)),
                ('angle_Mean', models.FloatField(blank=True, db_column='Angle_Mean', null=True)),
                ('angle_Sin', models.FloatField(blank=True, db_column='Angle_Sin', null=True)),
                ('angle_Cos', models.FloatField(blank=True, db_column='Angle_Cos', null=True)),
                ('chipThickness', models.FloatField(blank=True, db_column='ChipThickness', null=True)),
                ('TaskID', models.IntegerField(blank=True, db_column='taskID', null=True)),
                ('predOriginS1ActTrq', models.FloatField(blank=True, db_column='PredOriginS1ActTrq', null=True)),
                ('predOriginXActTrq', models.FloatField(blank=True, db_column='PredOriginXActTrq', null=True)),
                ('predOriginYActTrq', models.FloatField(blank=True, db_column='PredOriginYActTrq', null=True)),
                ('predOriginY2ActTrq', models.FloatField(blank=True, db_column='PredOriginY2ActTrq', null=True)),
                ('predOriginZActTrq', models.FloatField(blank=True, db_column='PredOriginZActTrq', null=True)),
                ('stlPath', models.FileField(blank=True, max_length=255, null=True, upload_to='')),
                ('simulation', models.ForeignKey(db_column='Simulation', on_delete=django.db.models.deletion.CASCADE, to='simulation.simulation')),
            ],
        ),
    ]
