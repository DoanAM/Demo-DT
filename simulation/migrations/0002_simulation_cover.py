# Generated by Django 4.1.3 on 2022-11-23 16:26

from django.db import migrations, models
import simulation.models


class Migration(migrations.Migration):

    dependencies = [
        ("simulation", "0001_initial"),
    ]

    operations = [
        migrations.AddField(
            model_name="simulation",
            name="cover",
            field=models.FileField(
                blank=True, null=True, upload_to=simulation.models.upload_path
            ),
        ),
    ]
