# Anvil Azure Sphere Test App

This is a testing app we built, mainly to launch a busybox shell bound on port 4444. It also contains a few other commands that we built to asses the RE and exploration process.

# Building

The test app has a Makefile to build and deploy the app using the musle libc.

1. Ensure `arm-linux-musleabihf-gcc` and `azsphere` are in your `$PATH`.

```shell
> echo $PATH
/opt/anvil_azure_sphere_sdk/bin/ /opt/azurespheresdk/Tools ...
```

2. Build with the Makefile

```shell
> make
arm-linux-musleabihf-gcc -I./azureroot/include/ -g -march=armv7ve -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -std=c11 -Wno-pointer-sign -ggdb -O0 -fPIC -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-omit-frame-pointer -fno-exceptions -fstack-protector-strong -c -o main.o main.c 
...
cp main ./approot/bin/app
cp app_manifest.json ./approot/app_manifest.json
azsphere -v image-package pack-application -i ./approot -x ./bin/busybox -o main.imagepackage -s 5 -h sample_hardware.json
Azure Sphere Utility version 20.4.10.6179
Copyright (C) Microsoft Corporation. All rights reserved.

Start time (UTC): Wednesday, 23 September 2020 18:14:53
verbose: Creating image package.
verbose: Azure Sphere application image package written.
verbose: Appending metadata.
verbose: Wrote metadata:
  Section: Identity
    Image Type:           Application
    Component ID:         61ae5c57-98cd-4a0a-8b60-9509505c7617
    Image ID:             eef5d367-ae2c-42eb-861f-8f2c453133df
  Section: Signature
    Signing Type:         ECDsa256
    Cert:                 a8d5cc6958f48710140d7a26160fc1cfc31f5df0
  Section: Debug
    Image Name:           AzureBusybox
    Built On (UTC):       9/23/20 6:14:54 PM
    Built On (Local):     9/23/20 6:14:54 PM
  Section: Temporary Image
    Remove image at boot: False
    Under development:    True
  Section: ABI Depends
    Depends on:           ApplicationRuntime, version 5

verbose: Packaging completed successfully.
verbose: Output file is at: main.imagepackage
Command completed in 00:00:01.0806463.

```

## Deploying

Use the `azsphere` CLI tool to side load the application. The Makefile has a deploy target to do this automatically:

```shell
> make deploy
azsphere device sideload deploy --imagepackage main.imagepackage
Deploying '/azsphereapp/main.imagepackage' to the attached device.
Image package '/azsphereapp/main.imagepackage' has been deployed to the attached device.
```

### Deploy Issues

You may get an error, such as:

```
error: Could not deploy application to device: Installation failed; check if application development capability is enabled ('azsphere device enable-development').
```

If so, it is probably because the device ran out of space to store the app. If you have other apps installed, you may need to delete them and try again. If you are not using the debugger, you can manually remove GDB and free up some space:

```
> azsphere device sl delete -i 61ae5c57-98cd-4a0a-8b60-9509505c7617
Component '61ae5c57-98cd-4a0a-8b60-9509505c7617' deleted.
```

Depending on the version, the component ID for gdb maybe different. You can use the `azsphere device app show-status` command to list installed apps, and delete component IDs that do not match your apps:

```
> azsphere device app show-status
61ae5c57-98cd-4a0a-8b60-9509505c7617
App state: running

1689d8b2-c835-2e27-27ad-e894d6d15fa9
App state: running
```



# Running

The app binds a shell on port 4444. Connect using netcat:

```
> nc 192.168.35.2 4444

=========================================
Welcome to Anvil's Azure Sphere Test App!
=========================================
> 
```

Basic online help lists the available commands:

```
> help
help - Displays commands and descriptions
busybox - Execs a busybox ash shell (no pty, so no prompt and no ^C or ^Z)
peripheral - Calls the security-manager to enable/disable peripherals
local_file - Reads/Writes/Deletes the local mutable file
creds - Reads and displays the cred information at /proc/self/attr/exec
caps - Looks up the capability bits for a given pid
azspio - Some simple tests on an azspio socket
```

 The most important command is the `busybox` command. This launches the busybox shell:

```
> busybox
ls -l /
drwxr-x--x    2 sys      appman           0 Jan  1 01:38 dev
drwxr-xr-x    1 root     root           124 Jan  1  1970 etc
drwxr-xr-x    1 root     root            60 Jan  1  1970 lib
drwxr-xr-x    1 root     root           104 Jan  1  1970 mnt
dr-xr-xr-x   39 root     root             0 Jan  1  1970 proc
drwxr-xr-x    4 root     root             0 Jan  1 00:07 run
lrwxrwxrwx    1 root     root            16 Jan  1  1970 tmp -> var/volatile/tmp
drwxr-xr-x    1 root     root            32 Jan  1  1970 usr
drwxr-xr-x    1 root     root            52 Jan  1  1970 var
id
uid=1007 gid=1007 groups=15(net-config)
```

Using the busybox shell, you can explore the system. Just keep in mind, because there is no pty, busybox will not display a prompt or handle interrupts like ^C or ^Z, so be careful in trying to kill or suspend tasks.



