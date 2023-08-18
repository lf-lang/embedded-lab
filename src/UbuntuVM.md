# Notes for VM users

## Accessing USB Devices

If you are using the [pre-configured VM image](https://vm.lf-lang.org/), you need to ensure that it can access the RP2040 on the USB port of the host computer. For more information about configuring VirtualBox to allow this, see [this article](https://www.tecmint.com/enable-usb-in-virtualbox/).

## Installing the Extension Pack

To enable USB-2 support (and [various other features](https://www.virtualbox.org/manual/ch01.html#intro-installing)), an additional [extension pack](https://www.oracle.com/virtualization/technologies/vm/downloads/virtualbox-downloads.html#extpack) must be installed on the _host machine_.

 - [Installation instructions for Arch Linux](https://computingforgeeks.com/install-latest-virtualbox-and-extension-pack-in-arch-linux/?expand_article=1)
 - [Installation instructions for Ubuntu 22.04](https://linuxconfig.org/virtualbox-extension-pack-installation-on-ubuntu-22-04-jammy-jellyfish-linux)
 - [Installation instructions for Mac and Windows](https://www.nakivo.com/blog/how-to-install-virtualbox-extension-pack/)
