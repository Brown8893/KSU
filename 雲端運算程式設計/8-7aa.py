# _*_ coding: utf-8 _*_
# 程式 8-7aa.py (Python 3 version)

import json

fp = open('attractions_zh-tw.json','r',encoding="utf-8")
Tainan_travel = json.load(fp)
eq = Tainan_travel['class_list'] 
#eq[4]["data_list"][0]["title"]   "title"
print("旅遊人數明細表")
#'data_list'
for i in range(0,8):
    print(eq[i]["class_name"])
    #'title'
    for j in range(0,len(eq[i]["data_list"])):
        print(eq[i]["data_list"][j]["title"]) 
    print('-------------------------------')
     