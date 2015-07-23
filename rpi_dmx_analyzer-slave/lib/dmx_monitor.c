/**
 * @file monitor.c
 *
 */
/* Copyright (C) 2015 by Arjan van Vught <pm @ http://www.raspberrypi.org/forum/>
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

#include <dmx_devices.h>
#include <stdio.h>

#include "dmx.h"
#include "console.h"
#include "monitor.h"

static uint32_t dmx_packets_previous = 0;			///<
static uint32_t function_count_previous = 0;		///<
static uint32_t dmx_available_count_previous = 0;	///<

/**
 * @ingroup monitor
 */
void monitor_update(void)
{
	monitor_time_uptime(MONITOR_LINE_TIME);

	monitor_dmx_data(MONITOR_LINE_DMX_DATA, dmx_data);

	const struct _total_statistics *total_statistics = total_statistics_get();
	const uint32_t total_packets = total_statistics->dmx_packets + total_statistics->rdm_packets;

	console_clear_line(MONITOR_LINE_PACKETS);
	printf("Packets : %ld, DMX %ld, RDM %ld\n\n", total_packets, total_statistics->dmx_packets, total_statistics->rdm_packets);

	const uint16_t dmx_updates_per_second = total_statistics->dmx_packets - dmx_packets_previous;

	printf("\nDMX updates/sec %d  \n\n", dmx_updates_per_second);

	if (dmx_updates_per_second != 0) {
		const struct _dmx_statistics *dmx_statistics = dmx_get_statistics();
		printf("Slots in packet %d      \n", (uint16_t)dmx_statistics->slots_in_packet);
		printf("Slot to slot    %d      \n", (uint16_t)dmx_statistics->slot_to_slot);
		printf("Break to break  %ld     \n", dmx_statistics->break_to_break);
	} else {
		printf("Slots in packet --     \n");
		printf("Slot to slot    --     \n");
		printf("Break to break  --     \n");
	}

	dmx_packets_previous = total_statistics->dmx_packets;

	const struct _dmx_devices_statistics *dmx_devices_statistics = dmx_devices_get_statistics();
	const uint32_t function_count_per_second = dmx_devices_statistics->function_count - function_count_previous;
	const uint32_t dmx_available_count_per_second = dmx_devices_statistics->dmx_available_count - dmx_available_count_previous;

	monitor_line(MONITOR_LINE_STATS, "%ld / %ld", function_count_per_second, dmx_available_count_per_second);

	function_count_previous = dmx_devices_statistics->function_count;
	dmx_available_count_previous = dmx_devices_statistics->dmx_available_count;
}