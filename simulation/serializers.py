from rest_framework import serializers
from .models import Simulation
import datetime


class SimulationSerializer(serializers.ModelSerializer):
    class Meta:
        model = Simulation
        fields = ['timestamp', 'cover']
