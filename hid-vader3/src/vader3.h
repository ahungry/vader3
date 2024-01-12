/*
 * Support for Flydigi Vader 3 via Bluetooth (hardware doesn't support FF in that mode).
 *
 * Learning References (tutorials/blogs):
 * https://www.nirenjan.com/2020/linux-hid-driver/
 *
 * Project References:
 * https://github.com/atar-axis/vader3
 */

#ifndef VADER3_H_FILE
#define VADER3_H_FILE

#include <linux/hid.h>
#include <linux/version.h>

#ifndef VERSION
#error "vader3 version not defined"
#endif

#define VADER3_VERSION __stringify(VERSION)

#endif
