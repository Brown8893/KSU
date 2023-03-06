# LinuxDatabase
### 1. Download and Install Linux CentOS7
![image](https://user-images.githubusercontent.com/33440699/223036052-052e97ec-2da8-443f-98f3-3652ed7d527d.png)
### 2. start Install MariaDB
* 先更新 CentOS Linux 系統上的套件 ```sudo yum update```
![image](https://user-images.githubusercontent.com/33440699/223045686-535e49da-2354-467c-bd1f-3087fbed3394.png)
* 安裝 MariaDB 伺服器 ```sudo yum install mariadb-server```
![image](https://user-images.githubusercontent.com/33440699/223049139-65ce267c-8a6e-43be-b86e-6f567a16dedb.png)
* 啟用 MariaDB 的 service ```sudo systemctl enable mariadb```
![image](https://user-images.githubusercontent.com/33440699/223060865-1ffe087d-9b4f-425a-b74b-d208cd31f241.png)
* 立即啟動 MariaDB 的 service ```sudo systemctl start mariadb```
![image](https://user-images.githubusercontent.com/33440699/223061302-77774256-66f3-486c-98fb-723fe98be64e.png)
* 檢查 MariaDB 伺服器是否有正常啟動 ```systemctl status mariadb```
