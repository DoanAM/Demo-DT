# from django.shortcuts import render
# from rest_framework import generics, status
# from .serializers import CncSerializer, AuxiliarySerializer, DriveSerializer, ProgSerializer, ToolSerializer, WcsSerializer, TestSerializer, getGenericSerializer
# from .models import Auxiliary, Cnc, Drive, Tool, Wcs, Prog, ToolsInChanger
# from rest_framework.views import APIView
# from rest_framework.viewsets import ModelViewSet
# from rest_framework.generics import ListAPIView
# from rest_framework.response import Response
# from rest_framework.decorators import api_view
# import logging
# import datetime
# import time
# from django.db.models import Window, F
# from django.db.models.functions import RowNumber

# logger = logging.getLogger(__name__)
# # Create your views here.

# model_dict = {"drive": Drive, "cnc": Cnc, "tool": Tool,
#               "wcs": Wcs, "prog": Prog, "auxiliary": Auxiliary}


# class GetAuxiliary(APIView):
#     def get(self, request, format=None):
#         queryset = Auxiliary.objects.last()
#         data = AuxiliarySerializer(queryset).data
#         return Response(data, status=status.HTTP_200_OK)


# class GetCurrentVal(APIView):
#     kwarg1 = "model"
#     kwarg2 = "field"

#     def get(self, request, format=None):
#         param1 = request.GET.get(self.kwarg1)
#         model = model_dict[param1]
#         field = request.GET.get(self.kwarg2)
#         queryset = model.objects.last()
#         serializer_class = getGenericSerializer(model, field)
#         data = serializer_class(queryset).data
#         return Response(data, status=status.HTTP_200_OK)


# class GetTimedData(APIView):
#     kwarg1 = "model"
#     kwarg2 = "field"
#     kwarg3 = "timespan"

#     def get(self, request, format=None):
#         param1 = request.GET.get(self.kwarg1)
#         model = model_dict[param1]

#         field = request.GET.get(self.kwarg2)

#         param3 = request.GET.get(self.kwarg3)

#         if param3 == "30min":
#             timespan = 30*60*1000
#         elif param3 == "1hr":
#             timespan = 60*60*1000
#         elif param3 == "1day":
#             timespan = 24*60*60*1000
#         elif param3 == "1month":
#             timespan = 30*24*60*60*1000

#         currentTime = round(time.time() * 1000)

#         queryset = model.objects.filter(
#             timestamp__gt=currentTime-timespan).all()  # slice this
#         total_rows = queryset.count()
#         max_rows = 500
#         step = max(1, total_rows // max_rows)
#         indexed_queryset = [(index + 1, obj) for index,
#                             obj in enumerate(queryset) if (index % step) == 0]
#         instances = [item[1] for item in indexed_queryset]

#         serializer_class = getGenericSerializer(model, field)
#         data = serializer_class(instances, many=True,).data

#         return Response(data)


# class GetTime(APIView):
#     def get(self, request, format=None):
#         current_datetime = datetime.datetime.now()
#         return Response(current_datetime, status=status.HTTP_200_OK)


# class GetWholeData(APIView):
#     def get(self, request, *args, **kwargs):
#         auxiliary = AuxiliarySerializer(Auxiliary.objects.last())
#         cnc = CncSerializer(Cnc.objects.last())
#         drive = DriveSerializer(Drive.objects.last())
#         prog = ProgSerializer(Prog.objects.last())
#         tool = ToolSerializer(Tool.objects.last())
#         wcs = WcsSerializer(Wcs.objects.last())

#         return Response({"cnc": cnc.data,
#                          "auxiliary": auxiliary.data,
#                          "drive": drive.data,
#                          "prog": prog.data,
#                          "tool": tool.data,
#                          "wcs": wcs.data})


# class GetLive3dPoints(APIView):

#     def is_between(num, a, b):
#         return a <= num <= b

#     def get(self, request):
#         currentTime = time.time()

#         latestPosVector = Cnc.objects.values(
#             "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").last()

#         latestCncX = Wcs.objects.last().x

#         queryset = Drive.objects.only(
#             "xfolldist", "yfolldist", "zfolldist", "s1acttrq", "s1follerr").last()
#         latestXfolldist = queryset.xfolldist
#         latestYfolldist = queryset.yfolldist
#         latestZfolldist = queryset.zfolldist
#         latestS1acttrq = queryset.s1acttrq
#         latestS1follerr = queryset.s1follerr

#         latestToolID = Tool.objects.last().id
#         latestToolDiameter = ToolsInChanger.objects.get(
#             tool_id=latestToolID).field_nominal_diameter
#         latestToolLength = ToolsInChanger.objects.get(
#             tool_id=latestToolID).nominal_overall_length

#         pointAmount = 60
#         timeIntervalBetweenPoints = int(1000/pointAmount)
#         latestTimestamp = Cnc.objects.last().timestamp
#         firstTimestamp = latestTimestamp - 1000
#         timestampList = list(
#             range(firstTimestamp, latestTimestamp, timeIntervalBetweenPoints))

#         posVectorList = []

#         for timePoint in timestampList:
#             posVector = Cnc.objects.values(
#                 "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").filter(timestamp__gt=timePoint).order_by("timestamp").first()
#             posVectorList.append(posVector)

#         latestProg = Prog.objects.last().programname
#         if latestProg == "none":
#             line = False
#             latestWcs = None
#         else:
#             latestWcs = Wcs.objects.values(
#                 "x", "y", "z", "minedgex", "minedgey", "minedgez", "maxedgex", "maxedgey", "maxedgez", "timestamp").last()
#             xMin = latestWcs["x"]+latestWcs["minedgex"]
#             yMin = latestWcs["y"]+latestWcs["minedgey"]
#             zMin = latestWcs["z"]+latestWcs["minedgez"]
#             xMax = latestWcs["x"]+latestWcs["maxedgex"]
#             yMax = latestWcs["y"]+latestWcs["maxedgey"]
#             zMax = latestWcs["z"]+latestWcs["maxedgez"]
#             for vector in posVectorList:
#                 if all([xMin < vector["xcurrpos"]/10000 < xMax,
#                        yMin < vector["ycurrpos"]/10000 < yMax,
#                        zMin < vector["zcurrpos"]/10000 < zMax]):
#                     line = True
#                 else:
#                     line = False
#                     break
#         print((time.time() - currentTime)*1000)

#         #####################################
#         secLatestTimestamp = Cnc.objects.last().timestamp - 500
#         seclatestPosVector = Cnc.objects.values(
#             "xcurrpos", "ycurrpos", "zcurrpos", "timestamp").filter(timestamp__gt=secLatestTimestamp).order_by("timestamp").first()
#         return Response({"latestPoint": latestPosVector,
#                          "secondLatestPoint": seclatestPosVector,
#                          "timestamp": latestTimestamp,
#                          "lastProg": latestProg,
#                          "line": line,
#                          "latestX": latestCncX,
#                          "posVectorList": posVectorList,
#                          "pointAmount": pointAmount,
#                          "s1acttrq": latestS1acttrq,
#                          "s1follerr": latestS1follerr,
#                          "xfolldist": latestXfolldist,
#                          "yfolldist": latestYfolldist,
#                          "zfolldist": latestZfolldist,
#                          "toolDiameter": latestToolDiameter,
#                          "toolLength": latestToolLength}, status=status.HTTP_200_OK)
