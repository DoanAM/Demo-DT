from rest_framework import serializers
from .models import Simulation, PredictedData
import datetime
import string
import os


class SimulationSerializer(serializers.ModelSerializer):
    timestamp = serializers.SerializerMethodField(source='timestamp')
    nc_file = serializers.SerializerMethodField(source='nc_file')

    class Meta:
        model = Simulation
        fields = '__all__'

    def get_timestamp(self, obj):
        time = round(obj.timestamp/1000)
        return (datetime.datetime.fromtimestamp(time).strftime('%Y-%m-%d %H:%M:%S'))

    def get_nc_file(self, obj):
        filename = os.path.basename(str(obj.nc_file))
        return filename.split("_", 1)[1]


class PredictedDataSerializer(serializers.ModelSerializer):
    stlPath = serializers.SerializerMethodField(source='stlPath')

    class Meta:
        model = PredictedData
        fields = '__all__'

    def get_stlPath(self, obj):
        return obj.stlPath.url
