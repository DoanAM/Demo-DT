from django.shortcuts import render
from rest_framework import generics, status
from .serializers import AuxiliarySerializer
from .models import Auxiliary
from rest_framework.views import APIView
from rest_framework.response import Response
import logging
logger = logging.getLogger(__name__)
# Create your views here.


class GetAuxiliary(APIView):
    def get(self, request, format=None):
        queryset = Auxiliary.objects.last()
        data = AuxiliarySerializer(queryset).data
        return Response(data, status=status.HTTP_200_OK)
