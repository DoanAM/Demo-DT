from django.shortcuts import render
from rest_framework import generics, status
from .serializers import CncSerializer, AuxiliarySerializer, DriveSerializer, ProgSerializer, ToolSerializer, WcsSerializer, TestSerializer
from .models import Auxiliary, Cnc, Drive, Tool, Wcs, Prog
from rest_framework.views import APIView
from rest_framework.generics import ListAPIView
from rest_framework.response import Response
import logging
import datetime

logger = logging.getLogger(__name__)
# Create your views here.


class GetAuxiliary(APIView):
    def get(self, request, format=None):
        queryset = Auxiliary.objects.last()
        data = AuxiliarySerializer(queryset).data
        return Response(data, status=status.HTTP_200_OK)


class GetXenc1Vel(APIView):
    def get(self, request, format=None):
        queryset = Drive.objects.last()
        data = TestSerializer(queryset).data
        return Response(data, status=status.HTTP_200_OK)


class GetTime(APIView):
    def get(self, request, format=None):
        current_datetime = datetime.datetime.now()
        return Response(current_datetime, status=status.HTTP_200_OK)


class GetWholeData(APIView):
    def get(self, request, *args, **kwargs):
        auxiliary = AuxiliarySerializer(Auxiliary.objects.last())
        cnc = CncSerializer(Cnc.objects.last())
        drive = DriveSerializer(Drive.objects.last())
        prog = ProgSerializer(Prog.objects.last())
        tool = ToolSerializer(Tool.objects.last())
        wcs = WcsSerializer(Wcs.objects.last())

        return Response({"cnc": cnc.data,
                         "auxiliary": auxiliary.data,
                         "drive": drive.data,
                         "prog": prog.data,
                         "tool": tool.data,
                         "wcs": wcs.data})
