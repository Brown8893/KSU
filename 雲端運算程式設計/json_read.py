# _*_ coding: utf-8 _*_

import json, datetime

#res = requests.get('https://citypark.tainan.gov.tw/App/parking.ashx?verCode=5177E3481D&type=1&ftype=1&exportTo=2')

fp = open('Tainan_bus.json','r')
parking = json.load(fp)

print("大台南公車定時定位資料")
for eq in parking['features']:
    print("車牌號碼:{}".format(eq['properties']['PlateNumb']))
    print("司機ID:{}".format(eq['properties']['OperatorID']))
    print("路線ID:{}".format(eq['properties']['RouteUID']))
    print("公車名稱:{}".format(eq['RouteName']['Zh_tw']))
    print("起訖站:{}".format(eq['RouteName']['En']))
    #et = float(eq['properties']['time']) /1000.0
    #d=datetime.datetime.fromtimestamp(et).strftime('%Y-%m-%d %H:%M:%S')
    #print("時間:{}".format(d))
