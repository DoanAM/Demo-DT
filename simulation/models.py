from django.db import models


# Create your models here.
class Simulation(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True)

    def __str__(self):
        return self.timestamp
