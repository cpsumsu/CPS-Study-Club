Start here: https://app.hackthebox.com/starting-point

On environment Kali Linux and connect to HTB

Explain the linux command: https://explainshell.com/

Always ask google: https://www.google.com/

# Meow

1. Check port 23 running service

   `nmap -p 23 -sV TARGET_IP`

2. telnet service is running, execute `telnet`

   `telnet TARGET_IP`

3. login with `root`

4. login succeed
5. `ls` to show what's there
6. `cat flag.txt`

# Fawn

1. Check port 21 (FTP) running service

   `nmap -p 21 -sV TARGET_IP`

2. ftp service is running, execute `ftp`

   `ftp TARGET_IP`

3. login with name `anonymous` without password

4. `ls` and there is a *flag.txt*

5. copy the file to current directory

   ftp>`get flag.txt`

6. exit ftp by command `bye`, then `cat flag.txt`

# Dancing

1. Check port 443 (SMB) running service

   `nmap -p 443 -sV TARGET_IP`

2. SMB service is running, see what is sharing in the server

   `smbclient -L TARGET_IP`

3. We are able to access with a blank password for the folder *WorkShares*

   `smbclient //TARGET_IP/WorkShares`

4. list the files in folder *WorkShares* smb: \> `ls`

5. Check the file *James.P* owns, the flag is inside *flag.txt*

6. smb: \James.P\> `get flag.txt`

# Redeemer

1. Check the TCP port opened on the machine, `-T5` used for quicker enum, `-sS` is check for the TCP SYN scan (half of the TCP handshake), `-sV` is used to check the version of the service

   `nmap -p 1000-9999 -sSV -T5 TARGET_IP`

2. port 6379/tcp is opened for **Redis** service **version 5.0.7**, Redis is an **in-memory database**

3. connect to Redis server, `-h` means host

   `redis-cli -h TARGET_IP`

5. Connected success, select the first database in Redis: `select 0`

6. List all the keys in this database: `keys *`, the flag is in the *flag* key

7. Look at the value of the key *flag* by `get flag`

