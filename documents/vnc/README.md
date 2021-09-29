#### Systemd Service

###### 1. Install the TightVNC server software

```
$ sudo apt-get install tightvncserver
```    

###### 2. Start server and configure a password

```
/usr/bin/tightvncserver
```

There is no need to create a view only password, unless you have a specific need.

When the server starts it will tell you which virtual desktop has been setup. 
In this case: New 'X' desktop is raspberrypi:1

says that it's virtual desktop 1. You would connect to this using :1 at the end of
the IP address in the client, this is the one we will setup to start automatically later.

You can run multiple instances. Each time you start tightvncserver it will use
the next available desktop, but in most cases you will just need one.

###### 3. Adding TightVNC to systemd startup
```
[Unit]
Description=TightVNC remote desktop server
After=sshd.service

[Service]
Type=dbus
ExecStart=/usr/bin/tightvncserver -geometry 1600x900 :1
User=pi
Type=forking

[Install]
WantedBy=multi-user.target
```

###### 4. Change the file so it is owned by root
```
$ sudo chown root:root /etc/systemd/system/tightvncserver.service
```
###### 5. Make the file executable by running
```
$ sudo chmod 755 /etc/systemd/system/tightvncserver.service
```
###### 6. Enable startup at boot using
```
$ sudo systemctl enable tightvncserver.service
```
###### 7. Reboot. Check if VNCserver is listed in the running units
```
$ systemctl list-units | grep vnc
  tightvncserver.service     loaded active running   TightVNC remote desktop server
```
###### 8. Changing and reloading the service
```
$ sudo systemctl daemon-reload
$ sudo systemctl restart  tightvncserver.service
```


#### System LAN Settings

RPi <--LAN--> Desktop <--> Internet

On Windows:
  1. LAN settings detects 2 connections
  2. Go to the main connection's settings (one that's connected to the internet)
  3. Properties -> Sharing 
  	Check - Allow sharing network users to connect ....
  	Uncheck - Allow ... to control or disable the shared internet connection

  4. Now in the network & sharing center, 2 connections will become 1 

On RPi (Jessie):   
	```ifconfig``` - IP will have changed   
      Ex: ```169.254.202.18``` would've become ```192.168.137.218```
		
To login to RPi without knowing it's IP address ?
On Windows :    
  open cmd, run ```arp -a```, will list all network interfaces' IP addressess.
