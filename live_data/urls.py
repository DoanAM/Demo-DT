from django.urls import path, re_path
from .views import GetAuxiliary
from .views import GetWholeData
from .views import GetTime
from .views import GetCurrentVal
from .views import GetTimedData

urlpatterns = [
    path('get-auxiliary', GetAuxiliary.as_view()),
    path('get-all', GetWholeData.as_view()),
    path('get-time', GetTime.as_view()),
    re_path(r'^get-cur/$', GetCurrentVal.as_view()),
    re_path(r'^get-timedData/$', GetTimedData.as_view()),
]
