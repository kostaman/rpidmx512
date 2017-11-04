/**
 * @file rdmdevice.h
 *
 */
/* Copyright (C) 2017 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
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

#ifndef RDMDEVICE_H_
#define RDMDEVICE_H_

#include <stdint.h>
#include <stdbool.h>

struct _rdm_device_info_data {
	/*@shared@*//*@null@*/uint8_t *data;
	uint8_t length;
};

#include "rdm.h"

#define DEVICE_SN_LENGTH		4	///<

class RDMDevice {
public:
	RDMDevice(void);
	~RDMDevice(void);

	bool Load(void);

	const uint8_t *GetUID(void) const;

	uint8_t GetExtMonLevel(void) const;

	void SetLabel(const struct _rdm_device_info_data *);
	void GetLabel(struct _rdm_device_info_data *);

	void SetManufacturerId(const struct _rdm_device_info_data *);
	void GetManufacturerId(struct _rdm_device_info_data *);

	void SetManufacturerName(const struct _rdm_device_info_data *);
	void GetManufacturerName(struct _rdm_device_info_data *);

	void Dump(void);

private:
	bool isMaskSet(uint16_t);

public:
    static void staticCallbackFunction(void *p, const char *s);

private:
    void callbackFunction(const char *s);

#if defined (__circle__)
private:
    void printf (const char *fmt, ...);
#endif

private:
    uint32_t m_bSetList;
	uint8_t m_aDeviceUID[RDM_UID_SIZE];
	uint8_t m_aDeviceSN[DEVICE_SN_LENGTH];
	char m_aDeviceRootLabel[RDM_DEVICE_LABEL_MAX_LENGTH];
	uint8_t m_nDeviceRootLabelLength;
	char m_aDeviceManufacturerName[RDM_MANUFACTURER_LABEL_MAX_LENGTH];
	uint8_t m_nDdeviceManufacturerNameLength;
	uint16_t m_nProductCategory;
	uint16_t m_nProductDetail;
	uint8_t m_nExtMonLevel;
};

#endif /* RDMDEVICE_H_ */
