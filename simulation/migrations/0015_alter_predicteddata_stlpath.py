# Generated by Django 4.1.3 on 2022-12-13 18:40

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ("simulation", "0014_alter_predicteddata_stlpath"),
    ]

    operations = [
        migrations.AlterField(
            model_name="predicteddata",
            name="stlPath",
            field=models.FileField(blank=True, max_length=255, null=True, upload_to=""),
        ),
    ]