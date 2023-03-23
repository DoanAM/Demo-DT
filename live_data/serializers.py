from rest_framework import serializers
from .models import Auxiliary, Cnc, Drive, Prog, Tool, Wcs
import datetime


class AuxiliarySerializer(serializers.ModelSerializer):
    class Meta:
        model = Auxiliary
        fields = '__all__'


class CncSerializer(serializers.ModelSerializer):
    class Meta:
        model = Cnc
        fields = '__all__'


class DriveSerializer(serializers.ModelSerializer):
    class Meta:
        model = Drive
        fields = '__all__'


class DriveSerializer(serializers.ModelSerializer):
    class Meta:
        model = Drive
        fields = '__all__'


class ProgSerializer(serializers.ModelSerializer):
    class Meta:
        model = Prog
        fields = '__all__'


class ToolSerializer(serializers.ModelSerializer):
    class Meta:
        model = Tool
        fields = '__all__'


class WcsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Wcs
        fields = '__all__'


class TestSerializer(serializers.ModelSerializer):
    x = serializers.SerializerMethodField(source='timestamp')
    y = serializers.IntegerField(source="xenc1vel")

    class Meta:
        model = Drive
        fields = ['x', 'y']

    def get_x(self, obj):
        time = round(obj.timestamp/1000)
        return (datetime.datetime.fromtimestamp(time))


def getGenericSerializer(model_arg, field_arg):
    class GenericSerializer(serializers.ModelSerializer):
        x = serializers.SerializerMethodField(source='timestamp')
        y = serializers.IntegerField(source=field_arg)

        class Meta:
            model = model_arg
            fields = ['x', 'y']

        def get_x(self, obj):
            time = round(obj.timestamp/1000)
            return (datetime.datetime.fromtimestamp(time).strftime('%Y-%m-%d %H:%M:%S'))

    return GenericSerializer
