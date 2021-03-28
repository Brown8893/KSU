# -*- coding: utf-8 -*-
"""
Created on Thu Oct 22 01:06:01 2020

@author: 20200925
"""
import pandas  #python數據分析函式庫
import matplotlib.pyplot as plt
dataset = pandas.read_csv('international-airline-passengers.csv', 
                          usecols=[1], engine='python', skipfooter=3)


import numpy as np
from scipy import stats
import pandas as pd
import matplotlib.pyplot as plt
import statsmodels.api as sm
from statsmodels.graphics.api import qqplot
# 畫出 ACF 12 期的效應
sm.graphics.tsa.plot_acf(dataset, lags=12)
plt.show()
# 畫出 PACF 12 期的效應
sm.graphics.tsa.plot_pacf(dataset, lags=12)
plt.show()