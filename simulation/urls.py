from django.urls import path, re_path
from .views import SimulationView, GetSimulationsView, GetSimulationDataView, DebugView

urlpatterns = [
    path('upload-simulation', SimulationView.as_view()),
    path('get-simulation', GetSimulationsView.as_view()),
    path('debug', DebugView.as_view()),
    re_path(r'^get-simulationData/$', GetSimulationDataView.as_view())
]
