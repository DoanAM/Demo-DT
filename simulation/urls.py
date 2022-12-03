from django.urls import path, re_path
from .views import SimulationView, GetSimulationsView

urlpatterns = [
    path('upload-simulation', SimulationView.as_view()),
    path('get-simulation', GetSimulationsView.as_view()),
]
