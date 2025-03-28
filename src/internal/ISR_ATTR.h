/*
  DCF77rxtm - Arduino libary receiving and decoding DCF77 frames Copyright (c)
  2025 Wolfgang Schmieder.  All right reserved.

  Contributors:
  - Wolfgang Schmieder

  Project home: https://github.com/dac1e/DCF77rxtm/

  This library is free software; you can redistribute it and/or modify it
  the terms of the GNU Lesser General Public License as under published
  by the Free Software Foundation; either version 3.0 of the License,
  or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#pragma once

#ifndef DCF77_ISR_ATTR_INTERNAL_H_
#define DCF77_ISR_ATTR_INTERNAL_H_

#if defined (ESP32)
#include <esp_attr.h>
#endif

#if defined(ESP8266)
	// interrupt handler and related code must be in RAM on ESP8266,
	// according to issue #46.
	#define TEXT_ISR_ATTR ICACHE_RAM_ATTR
	#define TEXT_ISR_ATTR_INLINE ICACHE_RAM_ATTR	// Map to 'ICACHE_RAM_ATTR'
#elif defined(ESP32)
	#define TEXT_ISR_ATTR IRAM_ATTR
	#define TEXT_ISR_ATTR_INLINE IRAM_ATTR			// Map to 'IRAM_ATTR'
#else
	#define TEXT_ISR_ATTR
	#define TEXT_ISR_ATTR_INLINE inline				// Map to 'inline'
#endif

#if defined(ESP32)
	#define DATA_ISR_ATTR DRAM_ATTR
#else
	#define DATA_ISR_ATTR
#endif

#define TEXT_ISR_ATTR_0			TEXT_ISR_ATTR // level 0, attibute functions
#define TEXT_ISR_ATTR_1			TEXT_ISR_ATTR // level 1, attibute functions
#define TEXT_ISR_ATTR_2			TEXT_ISR_ATTR // level 2, attibute functions
#define TEXT_ISR_ATTR_3     TEXT_ISR_ATTR // level 3, attibute functions
#define TEXT_ISR_ATTR_4     TEXT_ISR_ATTR // level 4, attibute functions

#define TEXT_ISR_ATTR_0_INLINE	TEXT_ISR_ATTR_INLINE // level 0, IRAM_ATTR or ICACHE_RAM_ATTR on ESP. Otherwise 'inline'
#define TEXT_ISR_ATTR_1_INLINE	TEXT_ISR_ATTR_INLINE // level 1, IRAM_ATTR or ICACHE_RAM_ATTR on ESP. Otherwise 'inline'
#define TEXT_ISR_ATTR_2_INLINE	TEXT_ISR_ATTR_INLINE // level 2, IRAM_ATTR or ICACHE_RAM_ATTR on ESP. Otherwise 'inline'
#define TEXT_ISR_ATTR_3_INLINE  TEXT_ISR_ATTR_INLINE // level 3, IRAM_ATTR or ICACHE_RAM_ATTR on ESP. Otherwise 'inline'
#define TEXT_ISR_ATTR_4_INLINE  TEXT_ISR_ATTR_INLINE // level 4, IRAM_ATTR or ICACHE_RAM_ATTR on ESP. Otherwise 'inline'

#endif /* DCF77_ISR_ATTR_INTERNAL_H_ */
