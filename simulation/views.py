from django.shortcuts import render
from rest_framework import generics, status
from .serializers import SimulationSerializer
from .models import Simulation
from rest_framework.views import APIView
from rest_framework.viewsets import ModelViewSet
from rest_framework.generics import ListAPIView
from rest_framework.response import Response
from rest_framework.decorators import api_view
import logging
import datetime
import time
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
