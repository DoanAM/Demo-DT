from django.urls import path, re_path
from .views import SimulationView

urlpatterns = [
    path('upload-simulation', SimulationView.as_view())
]
