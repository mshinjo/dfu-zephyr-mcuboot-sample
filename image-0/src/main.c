/*
 * Copyright (c) 2022 Mirai Shinjo
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#define IMAGE 0

int main(void)
{
	printk("%s: Hello World!\nThis message is from image-%d!\n", CONFIG_BOARD, IMAGE);
	return 0;
}
