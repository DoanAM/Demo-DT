# Generated by Django 4.1.3 on 2022-11-25 15:33

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ("simulation", "0003_simulation_sim_id_alter_simulation_timestamp"),
    ]

    operations = [
        migrations.DeleteModel(
            name="Simulation",
        ),
    ]
