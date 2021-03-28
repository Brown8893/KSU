# _*_ coding: utf-8 _*_
#剖析json array
import json


#input_file = open('attractions_zh-tw.json')
input_file = json.load(open('attractions_zh-tw.json'))
json_array = json.load(input_file)


for item in json_array:
    print("id:" + item['id'])
    print("name:" + item['name'])