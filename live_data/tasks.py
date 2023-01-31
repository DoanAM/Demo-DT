from celery import shared_task
import requests
import numpy as np
import cv2
import time
from .models import Prog, Images
from django.conf import settings
from pathlib import Path
from django.core.files.images import ImageFile
from live_data.liveMrs.mrsHelper import doCut


@shared_task
def task_one():
    timestamp = round(time.time()*1000)
    tokenUrl = "https://10.42.3.15/api/Camera/CreateCameraImageUrl"
    proxies = {
        'http': 'http://GuehringServer:skfSm2gf%243g%25Tl@10.42.5.1:8080',
        'https': 'http://GuehringServer:skfSm2gf%243g%25Tl@10.42.5.1:8080',
    }
    token = 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJBcGlCYXNpYyI6ImZhbHNlIiwiQXBpQXV0b21hdGlvbiI6InRydWUiLCJDb2NrcGl0QXBwIjoidHJ1ZSIsIkNhbWVyYUFwcCI6InRydWUiLCJBbGVydEFwcCI6ImZhbHNlIiwiUmVtb3RlTGlua0FwcCI6ImZhbHNlIiwic3ViIjoiYWljb20iLCJleHAiOjE2NzQ5OTk4MTAsImlzcyI6ImxvY2FsaG9zdCIsImF1ZCI6ImxvY2FsaG9zdCJ9.NVxYtXOuTzWrq6P9FB8o3766mZ9INGzNI6bVHXpJniI'
    try:
        lastProg = Prog.objects.last().programname
        print(lastProg)
        # print(obj.programname)
        with requests.Session() as s:
            s.headers = {'Authorization': token}
            s.verify = False
            responseToken = s.get(tokenUrl, proxies=proxies)
            responseImg = s.get("https://10.42.3.15"+responseToken.json()
                                ["imageUrl"], proxies=proxies)

            # Load image as string from file/database

            i = np.frombuffer(responseImg.content, dtype=np.uint8)

            im = cv2.imdecode(i, cv2.IMREAD_UNCHANGED)
            tempPath = Path(settings.MEDIA_ROOT) / "temp" / f"{timestamp}.jpg"
            cv2.imwrite(str(tempPath), im)
            # upload file to DB
            with tempPath.open(mode="rb") as f:
                imgFile = ImageFile(f, name=Path(f"{timestamp}.jpg"))
                Images.objects.create(timestamp=timestamp,
                                      img=imgFile, programname=lastProg)
            # remove temp file
            tempPath.unlink()

        return "success"
    except:
        return "failure"


@shared_task
def task_two():
    try:
        doCut()
        return "success"
    except:
        return "doCut Failed"
