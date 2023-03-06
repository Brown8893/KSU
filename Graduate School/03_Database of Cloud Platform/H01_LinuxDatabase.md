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
