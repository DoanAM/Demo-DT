# Generated by Django 4.1.3 on 2022-11-23 09:31

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = []

    operations = [
        migrations.CreateModel(
            name="Simulation",
            fields=[
                (
                    "timestamp",
                    models.BigIntegerField(
                        db_column="Timestamp", primary_key=True, serialize=False
                    ),
                ),
            ],
        ),
    ]