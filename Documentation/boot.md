# lk2nd boot process

lk2nd provides mutliple ways to boot, each of which has advantages and limitations.

## Android boot.img

lk2nd is based on CAF lk and includes aboot implementation. It can boot android
boot image versions FIXME, that are stored at 512k offset from the start of the
`boot` partition (in lk2nd) or withoug the offset (for lk1st). The offset is
required so the next stage image doesn't overwrite the lk2nd itself.

## Fastboot boot

lk2nd provides a fastboot interface and allows one to boot an OS via USB.

## extlinux.conf

lk2nd provides a very rudimentary support for `extlinux.conf` file, similar to
u-boot and depthcharge.

The file shall be stored at an `ext2` formated partition as `/extlinux/extlinux.conf`
and may include the following commands:

- `linux <kernel>` - Path to the kernel image.
- `initrd <initramfs>` - Path to the initramfs file.
- `fdt <devicetree>` - Path to the devicetree.
- `fdtdir <directory>` - Path to automatically find the DT in.
- `append <cmdlie>` - Cmdline to boot the kernel with.

**Note:** lk2nd includes only a very rudimentary extlinux support at this time.
only commands listed above are considered and the file should contain only one
entry. All other commands are ignored.

### Example extlinux.conf

```
timeout 1
menu title Boot the OS
default MyOS

# Bootloader should pick the DT
label MyOS
    linux /vmlinuz
    initrd /initramfs
    fdtdir /dtbs
    append earlycon console=ttyMSM0,115200
```

