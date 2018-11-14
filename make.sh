arm-none-eabi-gcc -o0 -DRPIBPLUS -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g ts.s t.ld t.c -o kernel.elf
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
