from __future__ import absolute_import, unicode_literals
import os
from celery import Celery

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'digital_twin.settings')
app = Celery('digital_twin')
app.config_from_object('django.conf:settings', namespace='CELERY')

app.autodiscover_tasks()
