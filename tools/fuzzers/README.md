# Azure Sphere Fuzzing

These fuzzers all use [boofuzz](https://github.com/jtpereyda/boofuzz) to generate test cases and share a common arguments:

```
> ./boo_config_wifi.py -h
usage: boo_config_wifi.py [-h] [--target TARGET] [--gui] [--start START]

optional arguments:
  -h, --help       show this help message and exit
  --target TARGET
  --gui
  --start START
```

* --target - Specifies the target to fuzz, defaults to 192.168.35.2
* --gui - Launches the boofuzz console gui
* -- start - Specifies the starting test case

## WiFi Configuration

Fuzzes the PSK and EAP-TLS configuration settings:

```
> ./boo_config_wifi.py --gui
```

# HTTP Get Requests

Runs through all the GET URLs and tries fuzzing HTTP headers and the request format.

```
> ./boo_get.py --gui
```

# Image Metadata

This fuzzer uses an existing image as a template and creates a boofuzz configuration for the metadata and then side loads the image. This fuzzer requires the [package_tools](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/package_tools) and [requests](https://github.com/psf/requests).

```
> ./image_metadata_fuzzer.py --gui templates/dev_enable_caps.bin
```

The template image can be any file with the Image Metadata. This includes enabling capabilities, or applications.

The pluton debug console can be used to view some log messages that get generated from the invalid metadata:

```
> miniterm /dev/ttyUSB4 115200
--- Miniterm on /dev/ttyUSB4  115200,8,N,1 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
[1BL] BOOT: 70900000/00000000/01010000
G=4761e15b786d9e997e43dd9fe0124c367af806044c9dbc43783fd9132b529735d94f17509e6749db8c6f61414a2ba47cc6066efde63d91cd556583f170fe178f
D=78220a871a841178948a7e2c27603b0f2e073082778af0fc1f3890f6efc66f0b8f368520c0cfaf5831a7d6873fbb3ed10a00b299ca4a7a5b5410e30bcfb8a0d9,N=21ab2a8b38bc7f77c688887e35d448a30d579160c57e6bf65e54854ecfe0bd12
[PLUTON] Logging initialized
[PLUTON] Booting HLOS core
[PLUTON] !! ERROR: component metadata footer is invalid
[PLUTON] !! ERROR: ValidateImage failed!
```

