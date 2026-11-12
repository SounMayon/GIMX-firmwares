# Build EMUG29PS4

The GitHub Actions workflow builds this target on Ubuntu 26.04 with the AVR compiler and libraries available in that release's package repositories.

To reproduce the build:

```sh
sudo apt-get update
sudo apt-get install --yes make gcc-avr avr-libc binutils-avr
make -C EMUG29PS4 clean all
```

The baseline build passed with the branch's current source and bundled LUFA version `130901`. Keep that as the comparison point before changing LUFA or the USB/serial protocol.

The firmware relays G29 PS4 HID control and output reports to the GIMX application. Successful compilation does not prove PS4 authentication, device enumeration, report correctness or force feedback. Those require captures and hardware checks with a real G29, adapter and console.

The shared project roadmap and audit findings are in [GIMX ROADMAP](https://github.com/SounMayon/GIMX/blob/GIMX-Reborn/ROADMAP.md).
