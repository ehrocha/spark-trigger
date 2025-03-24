Before you start, make sure your WSL distro is using the vhci_hcd module, this is what usbipd uses to check if you can assign USB bus to the WSL distro:
```sudo modprobe vhci_hcd``` 

To work with you ESP32 in WSL do the following:
1. Open windows terminal with admin privileges
2. Use usbipd to list the devices:
```
usbipd list
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
1-5    1bcf:2a02  Integrated Webcam                                             Not shared
1-7    187c:0550  AW-ELC                                                        Not shared
1-8    0d62:3740  WinUsb Device, USB Input Device                               Not shared
1-14   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not shared
4-1    17ef:60a9  USB Input Device                                              Not shared
4-2    17ef:60ee  USB Input Device                                              Not shared
4-3    10c4:ea60  Silicon Labs CP210x USB to UART Bridge (COM3)                 Not shared
4-4    046d:08b6  Logi Webcam C920e                                             Not shared
```
3. Bind and attach the ESP32 device to WSL
```
usbipd bind --busid 4-3
usbipd attach --wsl --busid 4-3
```


In order to start your BLE project you also need to define Service and characteristics UUID for the Bluetooth device.
For this you can use the [online uuid generator](https://www.uuidgenerator.net/version4)
