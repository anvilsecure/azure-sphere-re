# Azure Sphere Reverse Engineering

Microsoft held a [closed security bounty challenge](https://www.microsoft.com/en-us/msrc/azure-security-lab-archive?rtc=1) from June 1st through August 31st, 2020. While we did not participate in the closed challenge, we found the Azure Sphere devices interesting and since the development boards are cheap, we bought a few and took them apart. We developed several tools to help with the exploration and identified a couple issues that were also identified by people involved in the bounty challenge.

We tested on the [Seed MT3620 Mini Dev Board](https://www.seeedstudio.com/MT3620-Mini-Dev-Board-p-2919.html) running MS Azure Sphere OS 20.05. Currently the latest released version is 20.08 Update 1. Most of the issues we and others found have been fixed in the current release and our reverse engineering notes maybe out of date.

## Issues

During our reverse engineering we identified three potential issues with MS Azure Sphere device.  

* [ASXipFS Device Nodes](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#asxipfs-device-nodes) - It was possible to create app images with device nodes allowing access to devices an app otherwise would not have access too.
* [Peripheral Disable DoS](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#peripheral-disable-dos) - A malicious app on the device can disable peripherals used by other apps.
* [Image Metadata Parsing DoS](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#peripheral-disable-dos) - Our image metadata parsing fuzzer can reliably cause the device to become non-bootable and require a recovery action.

## Reverse Engineering Notes

We compiled our notes together in a form of a GitHub Wiki and is available [here](https://github.com/anvilventures/azure-sphere-re/wiki). 

## Tools

Our [tools](https://github.com/anvilventures/azure-sphere-re/wiki/Tools) include:

* [Anvil Azure Sphere Test App](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/anvil_azure_sphere_test_app) - Spawns a busybox shell for system exploration and includes a few other testing commands.
* [Toolchain/Libc](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/toolchain) - A compiled [musl libc](https://musl.libc.org) and gcc toolchain for the Azure Sphere devices. Mainly useful for a more complete set of headers.
* [Package Tools](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/package_tools) - Some python scripts to parse image metadata, sign images with a developer certificate, and upload images.
* [ASXipFS Unpacker](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/ASXipFS_unpacker) - A modified [cramfs-tools](https://github.com/npitre/cramfs-tools) project to extract the files from an ASXipFS file system.
* [Recovery Entry](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/recovery) - Simple python script to put the device into recovery mode.
* [Fuzzers](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/fuzzers) - Some fuzzers to test image metadata parsing and HTTP parsing.

# Additional Projects

A number of companies and groups have also published their findings and notes on the MS Azure Sphere device:

* https://github.com/Wiz-IO/azure-sphere-reverse-engineering
* https://www.comae.com/posts/2020-08-12_azure-sphere-internals-overview/
* https://blog.talosintelligence.com/2020/07/vuln-spotlight-azure-sphere-july-2020.html
* https://blog.talosintelligence.com/2020/08/vuln-spotlight-microsoft-azure-aug-2020.html