# _*_ coding: utf-8 _*_
# 程式 8-8b.py (Python 3 version)  

import sqlite3

conn = sqlite3.connect('test.sqlite')
c = conn.cursor()
print ("Opened database successfully")

#INSERT  增
c.execute("INSERT INTO demo (id, name, hint) \
      VALUES (25, 'Brown','NICE')")

#SELECT  查
cursor = c.execute("SELECT id, name, hint  from demo")
for row in cursor:
   print ("ID = ", row[0])
   print ("Name = ", row[1])
   print ("Hint = ", row[2], "\n")

print ("Operation done successfully")
conn.commit()
conn.close()

