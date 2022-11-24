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

# Create your views here.


class SimulationView(APIView):
    queryset = Simulation.objects.all()
    serializer_class = SimulationSerializer

    def post(self, request, *args, **kwargs):
        cover = request.data['cover']
        timestamp = round(time.time() * 1000)
        Simulation.objects.create(timestamp=timestamp, cover=cover)
        return Response({"Message: Simulation created"}, status=200)
