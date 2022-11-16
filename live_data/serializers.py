from rest_framework import serializers
from .models import Auxiliary


class AuxiliarySerializer(serializers.ModelSerializer):
    class Meta:
        model = Auxiliary
        fields = ('time', 'activatemicrojetmediumexternal2', 'activatemicrojetmediuminternal2',
                  'vacuumactivate', 'coolingunitactivate', 'activateblowclearworkpiece')
