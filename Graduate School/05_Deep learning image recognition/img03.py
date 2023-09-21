import cv2
import numpy as np

oimg = cv2.imread('demo.jpg')
img = cv2.resize(oimg,(800,600))
gimg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
