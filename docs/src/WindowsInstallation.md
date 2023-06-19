# Notes for Windows Users

## WSL Setup
It is recommend to use the Windows Subsystem for Linux (WSL) when developing on a windows machine.
Use the following [installation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) instructions to install usb support.

To mount the a pico device to the wsl instance, run the following in
an administrator powershell to find the correct bus and attach.

```
usbipd wsl list
usbipd wsl attach --busid <busid>
```

In the wsl instance, run the following to verify the device has mounted.

```
lsusb
```

TODO: add how to install udev permissions what is udev?
For debuging with the picoprobe, udev permissions have to 
be setup and restart everytime the probe is used.

```
sudo service udev restart && sudo udevadm trigger
```
