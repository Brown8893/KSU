# _*_ coding: utf-8 _*_
# 程式 8-7.py (Python 3 version)
#!/usr/bin/env python3
import json, datetime


#res = requests.get('https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&orderby=time&minmag=5&limit=10')

AA = open('attractions_en.json','r',encoding="utf-8")
Tainan = json.load(AA)

print("臺南旅遊網-景點資訊：")
for eq in Tainan['']:
    print("ID:{}".format(eq['']['id']))
    print("景點:{}".format(eq['']['name']))
    print("地址:{}".format(eq['']['address']))
    #et = float(eq['properties']['time']) /1000.0
    #d=datetime.datetime.fromtimestamp(et).strftime('%Y-%m-%d %H:%M:%S')
    #print("時間:{}".format(d))
