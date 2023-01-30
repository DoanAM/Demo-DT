from .models import Prog, Wcs, StlFile
from django.db.models import F, Func, Value
from live_data.liveMrs.main import createStock
import time


def getLastProg():
    currentTimestamp = round(time.time() * 1000)
    lastProg = Prog.objects.exclude(programname="none").last()
    timestamp1 = lastProg.timestamp
    print(lastProg.timestamp)
    print(lastProg.programname)
    fileName = str(currentTimestamp) + "_" + str(lastProg.programname)
    obj2 = Wcs.objects.filter(timestamp__lt=timestamp1).order_by(
        F('timestamp').desc()).first()
    x = abs(obj2.maxedgex - obj2.minedgex)
    y = abs(obj2.maxedgey - obj2.minedgey)
    z = abs(obj2.maxedgez - obj2.minedgez)
    print(x, y, z)
    createStock(obj2.minedgex, obj2.minedgey, obj2.minedgez,
                obj2.maxedgex, obj2.maxedgey, obj2.maxedgez, fileName)


def debug():
    progList = Prog.objects.exclude(programname="none").values_list(
        "programname", flat=True).distinct()
    # get second last programm
    print(progList[1])
    # get timestamp of second last programm
    timestampSecondLast = Prog.objects.filter(
        programname=progList[1]).last().timestamp
    checkQuerySet = StlFile.objects.filter(
        programname=progList[0]).filter(timestamp__gt=timestampSecondLast)
    print(len(checkQuerySet))
    print(timestampSecondLast)
