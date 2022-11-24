from django.db import models


def upload_path(instance, filename):
    return '/'.join(['covers', str(instance.timestamp), filename])

# Create your models here.


class Simulation(models.Model):
    timestamp = models.BigIntegerField(
        db_column='Timestamp', primary_key=True)
    cover = models.FileField(blank=True, null=True, upload_to=upload_path)

    def __str__(self):
        return self.timestamp
