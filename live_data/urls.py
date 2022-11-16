from django.urls import path
from .views import GetAuxiliary

urlpatterns = [
    path('get-auxiliary', GetAuxiliary.as_view())
]
