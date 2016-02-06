/**
 * @file bw_spi_dio.c
 *
 */
/* Copyright (C) 2014 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifdef DEBUG
extern int printf(const char *format, ...);
#endif
#include "tables.h"
#include "util.h"
#include "dmx.h"
#include "bw_spi_dio.h"

#define DMX_FOOTPRINT	7

static const char device_label[] = "bw_spi_dio";
static const uint8_t device_label_len = MIN(sizeof(device_label) / sizeof(device_label[0]), RDM_DEVICE_LABEL_MAX_LENGTH);

static const struct _rdm_personality rdm_personality = { DMX_FOOTPRINT, "Digital output 7-lines", 22 };
static const struct _rdm_sub_devices_info sub_device_info = {DMX_FOOTPRINT, 1, 1, /* start address */0, /* sensor count */0, "", 0, &rdm_personality};

/**
 * @ingroup DEV
 *
 * @param dmx_device_info
 */
static void bw_spi_dio(dmx_device_info_t *dmx_device_info) {
	int i;
	uint8_t data = 0;
	uint16_t dmx_data_index = dmx_device_info->dmx_start_address ;
	const uint8_t *dmx_data = dmx_get_data();

	for (i = 0; i < DMX_FOOTPRINT; i++) {

		if (dmx_data_index > DMX_UNIVERSE_SIZE)
			break;

		if ((dmx_data[dmx_data_index] & (uint8_t)0x80) != 0) {	// 0-127 is off, 128-255 is on
			data = data | (uint8_t)(1 << i);
		}

		dmx_data_index++;
	}

	bw_spi_dio_output(&dmx_device_info->device_info, data);
}

INITIALIZER(devices, bw_spi_dio)

/**
 * @ingroup DEV
 *
 * @param dmx_device_info
 */
static void bw_spi_dio_init(dmx_device_info_t *dmx_device_info) {
	struct _rdm_sub_devices_info *rdm_sub_devices_info =  &(dmx_device_info)->rdm_sub_devices_info;
#ifdef DEBUG
	printf("device init <bw_spi_dio_init>\n");
#endif
	(void)bw_spi_dio_start(&(dmx_device_info->device_info));
	bw_spi_dio_fsel_mask(&dmx_device_info->device_info, 0x7F);
	bw_spi_dio_output(&dmx_device_info->device_info, 0);

	_memcpy(rdm_sub_devices_info, &sub_device_info, sizeof(struct _rdm_sub_devices_info));
	dmx_device_info->rdm_sub_devices_info.dmx_start_address = dmx_device_info->dmx_start_address;
	_memcpy(dmx_device_info->rdm_sub_devices_info.device_label, device_label, device_label_len);
	dmx_device_info->rdm_sub_devices_info.device_label_length = device_label_len;
}

INITIALIZER(devices_init, bw_spi_dio_init)
