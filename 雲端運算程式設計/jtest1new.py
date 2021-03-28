import json
import sqlite3
from datetime import datetime


with open('scenic_spot_C_f.json' , 'r',encoding="utf-8") as reader:
    data = json.loads(reader.read())

conn = sqlite3.connect('../db.sqlite3')
#print(data)
 
for i in range(len(data['XML_Head']['Infos']['Info'])):
#for i in range(100):
    #print(data['XML_Head']['Infos']['Info'][i]['Name'])
    title = data['XML_Head']['Infos']['Info'][i]['Name']
    content = data['XML_Head']['Infos']['Info'][i]['Description']
    sqlstr = "INSERT INTO exam1_post values(?,?,?,?,?,?);"
    conn.execute(sqlstr, (None,title,content,'','',str(datetime.now())))
conn.commit()
conn.close()
