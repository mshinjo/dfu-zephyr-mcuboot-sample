# Device Firmware Upgrade Sample with Zephyr & MCUboot

## How to use this repository
1. Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to set up your Zephyr development environment.

2. Make sure that the board you would like to use have flash partitions defined in Device Tree. For more information regarding flash partitions, visit [Flash map](https://docs.zephyrproject.org/latest/services/storage/flash_map/flash_map.html#flash-map-api).

3. Clone this repository
```
cd ~/zephyrproject/zephyr
git clone <this repository>
```

4. Build MCUboot
```
west build -p always -b <board name> ~/zephyrproject/bootloader/mcuboot/boot/zephyr -d build-mcuboot
```

5. Build the first image, image-0.
```
st-flash --reset --connect-under-reset erase
west build -p always -b <board name> dfu-zephyr-mcuboot-sample/image-0
```

6. Flash MCUboot to `boot_partition` specified in Device Tree. For STM32 MCUs, use `stlink` tool.
```
st-flash --reset --connect-under-reset write build-mcuboot/zephyr/zephyr.bin 0x8000000
```

7. Flash image-0 to `slot0_partition`.
```
st-flash --reset --connect-under-reset write build/zephyr/zephyr.signed.bin 0x8040000
```

8. You should see something similar to below.
```
*** Booting Zephyr OS build zephyr-v3.2.0-2310-gcebac69c8ae1 ***
I: Starting bootloader
I: Primary image: magic=unset, swap_type=0x1, copy_done=0x3, image_ok=0x3
I: Scratch: magic=unset, swap_type=0x1, copy_done=0x3, image_ok=0x3
I: Boot source: primary slot
I: Swap type: none
I: Bootloader chainload address offset: 0x40000
I: Jumping to the first image slot
*** Booting Zephyr OS build zephyr-v3.2.0-2310-gcebac69c8ae1 ***
nucleo_h743zi: Hello World!
This message is from image-0!
```

9. Build the second image, image-1.
```
west build -p always -b <board name> dfu-zephyr-mcuboot-sample/image-1
```

10. Flash image-1 to `slot1_partition`.
```
st-flash --reset --connect-under-reset write build/zephyr/zephyr.signed.confirmed.bin 0x8080000
```
11. You should see something similar to below.
```
*** Booting Zephyr OS build zephyr-v3.2.0-2310-gcebac69c8ae1 ***
I: Starting bootloader
I: Primary image: magic=unset, swap_type=0x1, copy_done=0x3, image_ok=0x3
I: Scratch: magic=unset, swap_type=0x1, copy_done=0x3, image_ok=0x3
I: Boot source: primary slot
I: Swap type: perm
I: Starting swap using scratch algorithm.
I: Bootloader chainload address offset: 0x40000
I: Jumping to the first image slot
*** Booting Zephyr OS build zephyr-v3.2.0-2310-gcebac69c8ae1 ***
nucleo_h743zi: Hello World!
This message is from image-1!
```

## Things to keep in mind
`CONFIG_MCUBOOT_SIGNATURE_KEY_FILE="bootloader/mcuboot/root-rsa-2048.pem"` in `prj.conf` should only be used for testing as it is an insecure public key.

## LICENSE
`dfu-zephyr-mcuboot-sample` is licensed under the [Apache License 2.0](https://github.com/mshinjo/dfu-zephyr-mcuboot-sample/blob/main/LICENSE).
