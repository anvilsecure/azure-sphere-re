# Azure Sphere Reverse Engineering

Microsoft recently held a [closed security bounty challenge](https://www.microsoft.com/en-us/msrc/azure-security-lab-archive?rtc=1) for Azure Sphere, an application platform for internet-connected devices. While we did not participate in the three-month challenge which closed in August 2020, we were curious about the Azure Sphere devices which were designed with the [“seven properties of highly secured devices”](https://azure.microsoft.com/en-us/services/azure-sphere/#security) in mind. 

Since development boards are cheap, we bought a few and took them apart. We tested the [Seeed MT3620 Mini Dev Board](https://www.seeedstudio.com/MT3620-Mini-Dev-Board-p-2919.html) running MS Azure Sphere OS 20.05. 

We developed several tools to help with the exploration and identified a couple issues that were also identified by teams participating in the closed bounty challenge.

The issues we and others found have been fixed in the latest release, so our reverse engineering notes may be out of date.

## Issues

During our reverse engineering, we identified three potential issues with the MS Azure Sphere operating system:  

* [ASXipFS Device Nodes](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#asxipfs-device-nodes) - It was possible to create app images with device nodes to allow an app to access devices it otherwise could not access.
* [Peripheral Disable DoS](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#peripheral-disable-dos) - A malicious app on the device can disable peripherals used by other apps.
* [Image Metadata Parsing DoS](https://github.com/anvilventures/azure-sphere-re/wiki/Issues#peripheral-disable-dos) - Our image metadata parsing fuzzer can reliably cause the device to become non-bootable and require a recovery action.

## Reverse Engineering Notes

We compiled our notes together in the form of a [GitHub Wiki](https://github.com/anvilventures/azure-sphere-re/wiki). 

## Tools

Our [tools](https://github.com/anvilventures/azure-sphere-re/wiki/Tools) include:

* [Anvil Azure Sphere Test App](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/anvil_azure_sphere_test_app) - Spawns a busybox shell for system exploration and includes a few other testing commands.
* [Toolchain/Libc](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/toolchain) - A compiled [musl libc](https://musl.libc.org) and gcc toolchain for the Azure Sphere devices. Mainly useful for a more complete set of headers.
* [Package Tools](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/package_tools) - A set of Python scripts to parse image metadata, sign images with a developer certificate, and upload images.
* [ASXipFS Unpacker](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/ASXipFS_unpacker) - A modified [cramfs-tools](https://github.com/npitre/cramfs-tools) project to extract the files from an ASXipFS file system.
* [Recovery Entry](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/recovery) - A simple Python script to put the device into recovery mode.
* [Fuzzers](https://github.com/anvilventures/azure-sphere-re/tree/main/tools/fuzzers) - Some fuzzers to test image metadata parsing and HTTP parsing.

# Additional Projects

Other information security companies and teams have also published their findings and notes on the MS Azure Sphere device:

* [Reverse Engineering of Azure Sphere](https://github.com/Wiz-IO/azure-sphere-reverse-engineering)
* [Azure Sphere Internals - Overview](https://www.comae.com/posts/2020-08-12_azure-sphere-internals-overview/)
* [Vulnerability Spotlight: Microsoft issues security update for Azure Sphere](https://blog.talosintelligence.com/2020/07/vuln-spotlight-azure-sphere-july-2020.html)
* [Vulnerability Spotlight: Remote code execution, privilege escalation bugs in Microsoft Azure Sphere](https://blog.talosintelligence.com/2020/08/vuln-spotlight-microsoft-azure-aug-2020.html)
