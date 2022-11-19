from django.urls import path
from .views import GetAuxiliary
from .views import GetWholeData
from .views import GetTime
from .views import GetXenc1Vel

urlpatterns = [
    path('get-auxiliary', GetAuxiliary.as_view()),
    path('get-all', GetWholeData.as_view()),
    path('get-time', GetTime.as_view()),
    path('get-enc', GetXenc1Vel.as_view()),

]
