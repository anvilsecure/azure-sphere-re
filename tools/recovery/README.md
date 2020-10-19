# Recovery

This is a simple script that uses FTDI's bitbang mode to put the MediaTek dev kit into recovery mode.

This script does require you to physically hit the reset button. We could do the reset automatically by putting the recovery UART (/dev/ttyUSB4) into bitband mode, but we preferred to leave it it available to the OS as a regular UART. The debug UART (/dev/ttyUSB0) can also be used to enter recovery mode, but not reset, hence the need to physically reset.

# Using

1. Install dependencies:

```
> pip3 install pylibftdi
```

2. Run the script:

```
> ./recovery_hold.py
DEBUG_RTS is now high.... reset to enter recovery. Interrupt/hit enter to release DEBUG_RTS
```

3. Press the reset button on the dev board. If a console is connected to the Pluton/Recovery UART, you can see the log messages and the request for an XMODEM transfer. At this point the recovery bootloader could be loaded via your serial console:

```
> miniterm /dev/ttyUSB4 115200
--- Miniterm on /dev/ttyUSB4  115200,8,N,1 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
[1BL] BOOT: 70900000/00000001/01000000
G=4761e15b786d9e997e43dd9fe0124c367af806044c9dbc43783fd9132b529735d94f17509e6749db8c6f61414a2ba47cc6066efde63d91cd556583f170fe178f
D=78220a871a841178948a7e2c27603b0f2e073082778af0fc1f3890f6efc66f0b8f368520c0cfaf5831a7d6873fbb3ed10a00b299ca4a7a5b5410e30bcfb8a0d9,N=2420a197b6bd4565a9e974c848c4f157a857fd4c7d9bcbfb7337d45b07937add
[PLUTON] Logging initialized
[PLUTON] Booting HLOS core

RECOVERY
0000362000008A01020A00008FC8C833
CCCCC[1BL] BOOT: 70900000/00000000/01010000
```

