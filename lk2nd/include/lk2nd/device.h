/* SPDX-License-Identifier: BSD-3-Clause */
#ifndef LK2ND_DEVICE_H
#define LK2ND_DEVICE_H

#include <boot.h>

struct lk2nd_panel {
	const char *name;
	const char *old_compatible;
	const char *compatible;
	int compatible_size;
	const char *ts_compatible;
};

struct lk2nd_device {
	const char *compatible;
	const char *model;
	const char *battery;
	const char **dtbfiles;
	int dtbcount;

	struct lk2nd_panel panel;

#if WITH_LK2ND_DEVICE_2ND
	const char *cmdline;
	const char *bootloader;
	const char *serialno;
	const char *device;
	const char *carrier;
	const char *radio;
#endif
};
extern struct lk2nd_device lk2nd_dev;


unsigned char *lk2nd_device_update_cmdline(const char *cmdline, enum boot_type boot_type);

bool lk2nd_device2nd_have_atags(void) __PURE;
void lk2nd_device2nd_copy_atags(void *tags, const char *cmdline,
				void *ramdisk, unsigned ramdisk_size);

#endif /* LK2ND_DEVICE_H */
