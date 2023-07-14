# Notes for Windows Users

## WSL Setup
It is recommend to use the Windows Subsystem for Linux (WSL) when developing on a Windows machine.
Use the following [installation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) instructions to install USB support.

To mount the a Pico device to the WSL instance, run the following in
an administrator powershell to find the correct bus and attach.

```
usbipd wsl list
usbipd wsl attach --busid <busid>
```

In the WSL instance, run the following to verify the device has mounted.

```
lsusb
```

TODO: add how to install udev permissions what is udev?
For debuging with the picoprobe, udev permissions have to 
be setup and restart everytime the probe is used.

```
sudo service udev restart && sudo udevadm trigger
```

