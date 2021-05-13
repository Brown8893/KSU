# -*- coding: utf-8 -*-
"""
Created on Mon May 10 21:01:22 2021

@author: Brown
"""

import PIL.Image as Image
import os
path='./Mask/'



def start(Path):
    filelist = os.listdir(Path)
    for file in filelist:
        img = Image.open(Path + '/'+file).convert('RGB')
        print(img)
        print(file)
        img.save('./Masks/'+file)
    print('Done!')

start(path)