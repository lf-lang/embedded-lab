# Notes for Windows Users

## WSL Setup
It is recommend to use the Windows Subsystem for Linux (WSL) when developing on a Windows machine.
Use the following [installation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) instructions to install USB support.

To mount the a Pico device to the WSL instance, run the following in
an administrator powershell to find the correct bus and attach:

```
usbipd list
usbipd bind --busid <busid>
usbipd attach --wsl --busid <busid>
```

In the WSL instance, run the following to verify the device has mounted:

```
lsusb
```
> **Troubleshooting: udev in WSL**
>
> Due to USB being unofficially supported for WSL, 
> the [udev](https://wiki.archlinux.org/title/Udev) service daemon might need to be restarted after attaching
> usb devices to the WSL instance as outlined above. 
> This has particularly been an issue when debugging with openocd.
> Run the following commands to restart the udev daemon and reapply udev rules. 
> ```bash
> $ sudo service udev restart 
> $ sudo udevadm trigger
> ```

