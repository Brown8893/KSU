# _*_ coding: utf-8 _*_
# 程式 8-8a.py (Python 3 version)

import sqlite3
conn = sqlite3.connect('scores.sqlite')
conn.execute('Insert into student values(117,"資工類");')
cursor = conn.execute('select * from student;')
conn.commit()

for row in cursor:
    print('no {}: {}'.format(row[0],row[1]))
conn.close()    
