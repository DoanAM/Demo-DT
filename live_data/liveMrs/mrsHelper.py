from ..models import Prog, Wcs, LiveMrs
from django.db.models import F, Func, Value
from live_data.liveMrs.mwWrapper import createStock
import time
from pathlib import Path
from django.core.files import File
from django.conf import settings


def doCut():
    currentTimestamp = round(time.time() * 1000)
    # latest instance of latest Prog
    lastProg = Prog.objects.exclude(programname="none").last()

    #print("Latest Prog is: ", lastProg.programname)
    # check Create Stock or just DoCut()
    progList = Prog.objects.exclude(programname="none").values_list(
        "programname", flat=True).distinct()
    # get second last programm
    #print("Second Last Prog is: ", progList[1])
    # get timestamp of second last programm
    timestampSecondLast = Prog.objects.filter(
        programname=progList[1]).last().timestamp
    # check if anything has been created already after last Programm
    checkQuerySet = LiveMrs.objects.filter(
        programname=lastProg.programname).filter(timestamp__gt=timestampSecondLast)
    #print("checkQuerySet is: ", checkQuerySet)

    if len(checkQuerySet) == 0:
        timestamp1 = lastProg.timestamp
        #print("Timestamp of last Prog: ", lastProg.timestamp)
        #print("Name of last Prog", lastProg.programname)
        fileName = str(currentTimestamp) + "_" + \
            str(lastProg.programname) + ".stl"
        obj2 = Wcs.objects.filter(timestamp__lt=timestamp1).order_by(
            F('timestamp').desc()).first()
        tempStockLocation = Path(settings.MEDIA_ROOT) / "temp" / fileName

        createStock(obj2.minedgex, obj2.minedgey, obj2.minedgez,
                    obj2.maxedgex, obj2.maxedgey, obj2.maxedgez, tempStockLocation)
        print("Generated File")
        with tempStockLocation.open(mode="rb") as f:
            stlFile = File(f, name=Path(fileName))
            LiveMrs.objects.create(timestamp=currentTimestamp,
                                   stlFile=stlFile, programname=lastProg.programname)
        tempStockLocation.unlink()
        return "success"
    else:
        print("Raw Stock Already Exists")
        return "raw stock already exists"


def debug():
    progList = Prog.objects.exclude(programname="none").values_list(
        "programname", flat=True).distinct()
    # get second last programm
    print(progList[1])
    # get timestamp of second last programm
    timestampSecondLast = Prog.objects.filter(
        programname=progList[1]).last().timestamp
    checkQuerySet = LiveMrs.objects.filter(
        programname=progList[0]).filter(timestamp__gt=timestampSecondLast)
    print(len(checkQuerySet))
    print(timestampSecondLast)
