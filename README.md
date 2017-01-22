
#WakePi

Wake on LAN system for Raspberry Pi implemented with ESP8266

##Working

The application in the ESP can connect the system to local wifi and
listen to orders sended through wol packets in the password field.

We can use it through internet with port forwarding in our router


##Usage

Program ESP8266 and connect anything to a digital pin for activate/deactivate this pin.
See this image to choose the ESP pin with the external pin [2](http://www.14core.com/wp-content/uploads/2015/06/Node-MCU-Pin-Out-Diagram1.png):
![Nodemcu](http://www.14core.com/wp-content/uploads/2015/06/Node-MCU-Pin-Out-Diagram1.png "ESP8266 Nodemcu external pins")

Install **wol** packet and send a magic packet with this command [1](https://wiki.archlinux.org/index.php/Wake-on-LAN):

```bash

    wol 00:00:00:00:00:00 --port=9 --passwd=1-2-3-4-5-6

```
Put your Nodemcu Mac address and in the passwd field your personal command

If you want to send it through internet, you need to do port forwarding
in your router and send the command with this syntax:

```bash

    wol -p forwarded_port -i router_IP 00:00:00:00:00:00 -passwd=1-2-3-4-5-6

```
Put your external port in forwarded_port and your router ip address in router_IP.
In your router, the forwarded_port send the packet to a static ip corresponding
to your ESP8266.

That's all, enjoy

##Bibliography
[Wake-On-Lan(1)](https://wiki.archlinux.org/index.php/Wake-on-LAN)
[ESP8266 Nodemcu photo(2)](http://www.14core.com/wp-content/uploads/2015/06/Node-MCU-Pin-Out-Diagram1.png)
[Arduino](https://www.arduino.cc/)
[Configure Arduino IDE for ESP8266](http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/)
