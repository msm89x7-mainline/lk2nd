// SPDX-License-Identifier: BSD-3-Clause
/* Copyright (c) 2023 Nikita Travkin <nikita@trvn.ru> */

#include <stdlib.h>
#include <debug.h>
#include <target.h>
#include <list.h>
#include <lib/bio.h>
#include <lib/fs.h>

#include <lk2nd/boot.h>

#include "boot.h"

/**
 * lk2nd_scan_devices() - Scan filesystems and try to boot
 */
static void lk2nd_scan_devices(void)
{
	struct bdev_struct *bdevs = bio_get_bdevs();
	char mountpoint[16];
	bdev_t *bdev;
	int ret;

	dprintf(INFO, "boot: Trying to boot...\n");

	list_for_every_entry(&bdevs->list, bdev, bdev_t, node) {

		/* Skip top level block devices. */
		if (!bdev->is_subdev)
			continue;

		snprintf(mountpoint, sizeof(mountpoint), "/%s", bdev->name);
		ret = fs_mount(mountpoint, "ext2", bdev->name);
		if (ret < 0)
			continue;

		/* TODO: THIS MUST BE DEBUG ONLY!!! */
		dprintf(INFO, "Scanning %s ...\n", bdev->name);
		dprintf(INFO, "%s\n", mountpoint);
		//print_file_tree(mountpoint, " ");

		lk2nd_try_extlinux(mountpoint);
	}
}

/**
 * lk2nd_boot() - Try to boot the OS.
 *
 * This method is supposed to be called from aboot.
 * If appropriate OS is found, it will be booted, and this
 * method will never return.
 */
void lk2nd_boot(void)
{
	lk2nd_boot_dump_devices();
	dprintf(INFO, "boot: Trying to boot from the file system\n");
	lk2nd_scan_devices();
}
