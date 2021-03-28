# -*- coding: utf-8 -*-
"""
Created on Wed Oct 21 20:15:05 2020

@author: 20200925
"""

#pip install beautifulsoup4
#pip install requests

import requests
response = requests.get("https://travel.ettoday.net/category/%E6%A1%83%E5%9C%92/")

import requests
from bs4 import BeautifulSoup
response = requests.get("https://travel.ettoday.net/category/%E6%A1%83%E5%9C%92/")
soup = BeautifulSoup(response.text, "html.parser")
print(soup.prettify())  #輸出排版後的HTML內容

result = soup.find("h3")
print(result)
result = soup.find_all("h3", itemprop="headline", limit=3)
print(result)
result = soup.find_all(["h3", "p"], limit=2)
print(result)
result = soup.find("h3", itemprop="headline")
print(result.select_one("a"))
result = soup.find("div", itemprop="itemListElement")
print(result.select("a"))
titles = soup.find("p", class_="summary")
print(titles)
titles = soup.find_all("p", class_="summary", limit=3)
print(titles)
titles = soup.select(".summary", limit=3)
print(titles)
result = soup.find("a", itemprop="url")
parents = result.find_parents("h3")
print(parents)
result = soup.find("h3", itemprop="headline")
previous_node = result.find_previous_siblings("a")
print(previous_node)
result = soup.find("h3", itemprop="headline")
next_node = result.find_next_siblings("p")
print(next_node)

titles = soup.find_all("h3", itemprop="headline")
for title in titles:
    print(title.select_one("a"))
titles = soup.find_all("h3", itemprop="headline")
for title in titles:
    print(title.select_one("a").get("href"))
titles = soup.find_all("h3", itemprop="headline")
for title in titles:
    print(title.select_one("a").getText())