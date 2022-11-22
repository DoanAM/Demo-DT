from django.urls import path, include
from .views import index

urlpatterns = [
    path('debug/', include('live_data.urls')),
    path('home', index),
    path('simulation', index),
]
