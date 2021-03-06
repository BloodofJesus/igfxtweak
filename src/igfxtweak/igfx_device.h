﻿#pragma once
#include "config.h"
#include <stdint.h>

int igfx_device_find(uint32_t *address, uint16_t *ven, uint16_t *dev);
int igfx_device_get_iobase(uint32_t address, uint32_t bar0, uint32_t bar1, uint32_t *iobase_l, uint32_t *iobase_h);
int igfx_device_read(uint8_t *address, uint32_t size, uint8_t *data);
int igfx_device_write(uint8_t *address, uint32_t size, uint8_t *data);
void igfx_device_unmap(void);
