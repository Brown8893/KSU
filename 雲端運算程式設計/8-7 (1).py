# _*_ coding: utf-8 _*_
# 程式 8-7.py (Python 3 version)

import json, datetime

#res = requests.get('https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&orderby=time&minmag=5&limit=10')

fp = open('Tainan_bus.json','r')
earthquakes = json.load(fp)

print("大台南公車定時定位資料：")
for eq in earthquakes:
    print("車牌:{}".format(eq['PlateNumb']))
    print("路線ID:{}".format(eq[' ']['RouteID']))
    #et = float(eq['']['time']) /1000.0
    #d=datetime.datetime.fromtimestamp(et).strftime('%Y-%m-%d %H:%M:%S')
    #print("時間:{}".format(d))
