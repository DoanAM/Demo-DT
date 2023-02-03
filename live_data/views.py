from django.shortcuts import render
from rest_framework import generics, status
from .serializers import CncSerializer, AuxiliarySerializer, DriveSerializer, ProgSerializer, ToolSerializer, WcsSerializer, TestSerializer, getGenericSerializer
from .models import Auxiliary, Cnc, Drive, Tool, Wcs, Prog
from rest_framework.views import APIView
from rest_framework.viewsets import ModelViewSet
from rest_framework.generics import ListAPIView
from rest_framework.response import Response
from rest_framework.decorators import api_view
import logging
import datetime
import time

logger = logging.getLogger(__name__)
# Create your views here.

model_dict = {"drive": Drive, "cnc": Cnc, "tool": Tool,
              "wcs": Wcs, "prog": Prog, "auxiliary": Auxiliary}


class GetAuxiliary(APIView):
    def get(self, request, format=None):
        queryset = Auxiliary.objects.last()
        data = AuxiliarySerializer(queryset).data
        return Response(data, status=status.HTTP_200_OK)


class GetCurrentVal(APIView):
    kwarg1 = "model"
    kwarg2 = "field"

    def get(self, request, format=None):
        param1 = request.GET.get(self.kwarg1)
        model = model_dict[param1]
        field = request.GET.get(self.kwarg2)
        queryset = model.objects.last()
        serializer_class = getGenericSerializer(model, field)
        data = serializer_class(queryset).data
        return Response(data, status=status.HTTP_200_OK)


class GetTimedData(APIView):
    kwarg1 = "model"
    kwarg2 = "field"
    kwarg3 = "timespan"

    def get(self, request, format=None):
        param1 = request.GET.get(self.kwarg1)
        model = model_dict[param1]

        field = request.GET.get(self.kwarg2)

        param3 = request.GET.get(self.kwarg3)

        if param3 == "30min":
            timespan = 30*60*1000
        elif param3 == "1hr":
            timespan = 60*60*1000
        elif param3 == "1day":
            timespan = 24*60*60*1000
        elif param3 == "1month":
            timespan = 30*24*60*60*1000

        currentTime = round(time.time() * 1000)

        queryset = model.objects.filter(
            timestamp__gt=currentTime-timespan).all()
        serializer_class = getGenericSerializer(model, field)
        data = serializer_class(queryset, many=True,).data

        return Response(data)


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


class GetLive3dPoints(APIView):
    def is_between(num, a, b):
        return a <= num <= b

    def get(self, request, *args, **kwargs):
        pointAmount = 10
        timeIntervalBetweenPoints = int(1000/10)
        latestTimestamp = Cnc.objects.last().timestamp
        posVectorList = []
        latestPosVector = Cnc.objects.values(
            "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").last()
        firstTimestamp = latestTimestamp - 1000
        timestampList = list(
            range(firstTimestamp, latestTimestamp, timeIntervalBetweenPoints))
        for time in timestampList:
            posVector = Cnc.objects.values(
                "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").filter(timestamp__gt=time).order_by("timestamp").first()
            posVectorList.append(posVector)
        latestProg = Prog.objects.last().programname
        if latestProg == "none":
            line = False
            latestWcs = None
        else:
            latestWcs = Wcs.objects.values(
                "x", "y", "z", "minedgex", "minedgey", "minedgez", "maxedgex", "maxedgey", "maxedgez", "timestamp").last()
            xMin = latestWcs["x"]+latestWcs["minedgex"]
            yMin = latestWcs["y"]+latestWcs["minedgey"]
            zMin = latestWcs["z"]+latestWcs["minedgez"]
            xMax = latestWcs["x"]+latestWcs["maxedgex"]
            yMax = latestWcs["y"]+latestWcs["maxedgey"]
            zMax = latestWcs["z"]+latestWcs["maxedgez"]
            for vector in posVectorList:
                if all([xMin < vector["xcurrpos"]/10000 < xMax,
                       yMin < vector["ycurrpos"]/10000 < yMax,
                       zMin < vector["zcurrpos"]/10000 < zMax]):
                    line = True
                else:
                    line = False
                    break

        #####################################
        latestTimestamp = Cnc.objects.last().timestamp
        latestPosVector = Cnc.objects.values(
            "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").last()
        secLatestTimestamp = Cnc.objects.last().timestamp - 500
        seclatestPosVector = Cnc.objects.values(
            "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").filter(timestamp__gt=secLatestTimestamp).order_by("timestamp").first()
        #latestProg = Prog.objects.last().programname
        # if latestProg == "none":
        #     line = False
        #     latestWcs = None
        # else:
        #     latestWcs = Wcs.objects.values(
        #         "x", "y", "z", "minedgex", "minedgey", "minedgez", "maxedgex", "maxedgey", "maxedgez", "timestamp").last()
        #     xMin = latestWcs["x"]+latestWcs["minedgex"]
        #     yMin = latestWcs["y"]+latestWcs["minedgey"]
        #     zMin = latestWcs["z"]+latestWcs["minedgez"]
        #     xMax = latestWcs["x"]+latestWcs["maxedgex"]
        #     yMax = latestWcs["y"]+latestWcs["maxedgey"]
        #     zMax = latestWcs["z"]+latestWcs["maxedgez"]
        #     if (seclatestPosVector["xcurrpos"]/10000 < xMin or
        #         seclatestPosVector["xcurrpos"]/10000 > xMax or
        #         seclatestPosVector["ycurrpos"]/10000 < yMin or
        #         seclatestPosVector["ycurrpos"]/10000 > yMax or
        #         seclatestPosVector["zcurrpos"]/10000 < zMin or
        #             seclatestPosVector["zcurrpos"]/10000 > zMax):
        #         line = False
        #     else:
        #         line = True

        return Response({"latestPoint": latestPosVector,
                         "secondLatestPoint": seclatestPosVector,
                         "timestamp": secLatestTimestamp,
                         "lastProg": latestProg, "line": line,
                         "latestWcs": latestWcs,
                         "posVectorList": posVectorList,
                         "pointAmount": pointAmount}, status=status.HTTP_200_OK)
