from django.urls import path, include
from .views import index
from django.views.generic import RedirectView

urlpatterns = [
    path('', RedirectView.as_view(url='/home', permanent=True)),
    path('debug/', include('live_data.urls')),
    path('simulationAPI/', include('simulation.urls')),
    path('home', index),
    path('simulation', index),
]
