# LinuxDatabase
### 1. Download and Install Linux CentOS7
![image](https://user-images.githubusercontent.com/33440699/223036052-052e97ec-2da8-443f-98f3-3652ed7d527d.png)
### 2. Start Install MariaDB
* 先更新 CentOS Linux 系統上的套件 ```sudo yum update```
![image](https://user-images.githubusercontent.com/33440699/223045686-535e49da-2354-467c-bd1f-3087fbed3394.png)
* 安裝 MariaDB 伺服器 ```sudo yum install mariadb mariadb-client -y```
![image](https://user-images.githubusercontent.com/33440699/223168377-5df69c3f-17a3-465c-830c-2fa84243bb03.png)
* 啟動 MariaDB 伺服器 ```sudo systemctl start mariadb```
* 每次開機自動開啟 MariaDB 伺服器 ```sudo systemctl enable mariadb```
* 檢視 MariaDB 啟動狀態 ```sudo systemctl status mariadb```
![image](https://user-images.githubusercontent.com/33440699/223168868-98752f04-e249-4b27-aa8d-1b5aadfe5141.png)
* 加強 MariaDB 安全性 ```sudo mysql_secure_installation```
![image](https://user-images.githubusercontent.com/33440699/223169930-43edd1e1-ef58-4ce3-8ab4-982357aa5cf8.png)
* 檢視 MariaDB 版本 ```mysql -V```
![image](https://user-images.githubusercontent.com/33440699/223170169-e98efb1c-84f6-492d-a801-6fed18252a1c.png)
* 登入 MariaDB 資料庫並查看 ```mysql -u root -h localhost -p```
![image](https://user-images.githubusercontent.com/33440699/223170522-f404c2b3-500d-4edb-abbe-2fc222e0d876.png)
* 建立一個資料庫 ```create database ie```
![image](https://user-images.githubusercontent.com/33440699/223171183-f4e5d02a-5dee-4e50-b886-a29d4b5e8629.png)
* 建立使用者給資料庫權限 ```CREATE USER ‘brown’@‘%’ IDENTIFIED BY ‘ksu’;```  ```GRANT ALL PRIVILEGES ON ie.* TO brown@localhost;```
![image](https://user-images.githubusercontent.com/33440699/223172101-09cfe34a-cd34-4d25-bc7a-5eb1739e4d0a.png)
* 進行遠端連線設定 ```sudo vi /etc/my.cnf.d/server.cnf```
![image](https://user-images.githubusercontent.com/33440699/223172967-ce24ee5b-bbd5-4678-8972-2da5a32a9303.png)
* 設port為(3306)並重新啟動 ```sudo firewall-cmd --zone=public --add-port=3306/tcp --permanent```
![image](https://user-images.githubusercontent.com/33440699/223173451-693735f1-ebfc-4ac2-8bfe-f78050cd6d6e.png)
* client端連線 ```mysql -u root -h 192.168.0.2 -p```
![image](https://user-images.githubusercontent.com/33440699/223180208-3d2f5bd8-c5ad-4cc4-a3af-1207b47cccb1.png)
