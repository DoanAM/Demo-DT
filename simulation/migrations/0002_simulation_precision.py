# Generated by Django 4.1.3 on 2023-02-06 20:37

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ("simulation", "0001_initial"),
    ]

    operations = [
        migrations.AddField(
            model_name="simulation",
            name="precision",
            field=models.FloatField(blank=True, null=True),
        ),
    ]
