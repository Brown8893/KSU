from bs4 import BeautifulSoup
import requests
import os
 
input_image = input("請輸入要下載的圖片：")

response = requests.get("https://unsplash.com/s/photos/bear")
soup = BeautifulSoup(response.text, "lxml")
 
results = soup.find_all("img", {"class": "_2UpQX"}, limit=5)

image_links = [result.get("src") for result in results] 

for index, link in enumerate(image_links):  
    if not os.path.exists("images"):
        os.mkdir("images")  # 建立資料夾          
        img = requests.get(link)  # 下載圖片           