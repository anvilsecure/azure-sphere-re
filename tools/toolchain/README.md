# Toolchain/Libc

The SDK provided by Microsoft is very limited and does not expose the underlining Linux/libc functions. The functions are there, just hidden from the SDK. There are a couple of ways to call the standard libc functions. You could copy the libc.so from the recovery [Firmware](https://github.com/anvilventures/azure-sphere-re/wiki/Firmware) into the azurespheresdk and add your own function prototypes. We started that way, and then just compiled our own [musl libc](https://musl.libc.org/) matching the same version used by Microsoft.

# Using

Unpack the arm-linux-musleabihf.tar.xz and add `<unpack_dir>/bin ` directory to your `$PATH`
