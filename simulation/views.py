from django.shortcuts import render
from django.db.models import F
from rest_framework import status
from .serializers import SimulationSerializer, PredictedDataSerializer
from .models import Simulation, PredictedData
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.decorators import api_view
import time
from django.http import FileResponse
from .tasks import runSimulation

# Create your views here.


class SimulationView(APIView):
    queryset = Simulation.objects.all()
    serializer_class = SimulationSerializer

    def post(self, request, *args, **kwargs):
        nc_file = request.data['nc_file']
        timestamp = round(time.time() * 1000)
        Simulation.objects.create(timestamp=timestamp, nc_file=nc_file)
        runSimulation.delay()  # this is a race condition. pass object as arg into runSimulation()
        return Response({"Message: Simulation created"}, status=200)


class GetSimulationsView(APIView):
    serializer_class = SimulationSerializer

    def get(self, request, *args, **kwargs):
        queryset = Simulation.objects.filter(
            finished=True).only("timestamp")
        #queryset = Simulation.objects.all()
        data = SimulationSerializer(queryset, many=True).data
        return Response(data, status=status.HTTP_200_OK)


class GetSimulationDataView(APIView):
    kwarg1 = "simulation"

    def get(self, request, format=None):
        param1 = request.GET.get(self.kwarg1)
        querysetLarge = PredictedData.objects.filter(
            simulation=param1).all().order_by("timestamp")
        querysetLargeCount = querysetLarge.count()
        querysetReduced = querysetLarge[0: querysetLargeCount:100]
        # querysetReduced = querysetLarge.exclude(
        # stlPath__exact="").all()
        serializer_class = PredictedDataSerializer
        data = serializer_class(querysetReduced, many=True,).data

        return Response(data, status=status.HTTP_200_OK)


class DebugView(APIView):

    def get(self, request, format=None):
        queryset = PredictedData.objects.exclude(
            stlPath__exact="").all().order_by("timestamp")
        #data = queryset.stlPath.url
        serializer_class = PredictedDataSerializer
        data = serializer_class(queryset, many=True).data
        return Response(data, status=status.HTTP_200_OK)
