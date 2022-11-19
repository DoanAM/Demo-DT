from rest_framework import serializers
from .models import Auxiliary, Cnc, Drive, Prog, Tool, Wcs
import datetime


class AuxiliarySerializer(serializers.ModelSerializer):
    class Meta:
        model = Auxiliary
        exclude = ['timestamp']


class CncSerializer(serializers.ModelSerializer):
    class Meta:
        model = Cnc
        exclude = ['timestamp']


class DriveSerializer(serializers.ModelSerializer):
    class Meta:
        model = Drive
        exclude = ['timestamp']


class DriveSerializer(serializers.ModelSerializer):
    class Meta:
        model = Drive
        exclude = ['timestamp']


class ProgSerializer(serializers.ModelSerializer):
    class Meta:
        model = Prog
        exclude = ['timestamp']


class ToolSerializer(serializers.ModelSerializer):
    class Meta:
        model = Tool
        exclude = ['timestamp']


class WcsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Wcs
        exclude = ['timestamp']


class TestSerializer(serializers.ModelSerializer):
    x = serializers.SerializerMethodField(source='timestamp')
    y = serializers.IntegerField(source='xenc1vel')

    class Meta:
        model = Drive
        fields = ['x', 'y']

    def get_x(self, obj):
        time = round(obj.timestamp/1000)
        return (datetime.datetime.fromtimestamp(time))
