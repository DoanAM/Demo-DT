# Generated by Django 4.1.3 on 2022-11-25 15:13

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ("simulation", "0002_simulation_cover"),
    ]

    operations = [
        migrations.AddField(
            model_name="simulation",
            name="sim_ID",
            field=models.PositiveBigIntegerField(
                default=0, primary_key=True, serialize=False
            ),
            preserve_default=False,
        ),
        migrations.AlterField(
            model_name="simulation",
            name="timestamp",
            field=models.BigIntegerField(db_column="Timestamp"),
        ),
    ]
