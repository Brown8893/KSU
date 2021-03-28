# -*- coding: utf-8 -*-
"""
Created on Thu Oct 22 00:43:21 2020

@author: 20200925
"""

import pandas  #python數據分析函式庫
import matplotlib.pyplot as plt
dataset = pandas.read_csv('international-airline-passengers.csv', 
                          usecols=[1], engine='python', skipfooter=3)
plt.plot(dataset)
plt.show()