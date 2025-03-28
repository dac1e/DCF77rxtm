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

#ifndef DCF77tm_H_
#define DCF77tm_H_


#include <stdint.h>
#include <Printable.h>
#include <Print.h>

#ifndef ARDUINO_ARCH_AVR
#define HAS_STD_CTIME true
#endif

#ifdef ARDUINO_ARCH_MBED
typedef arduino::Printable printable_t;
typedef arduino::Print print_t;
#else
typedef Printable printable_t;
typedef Print print_t;
#endif

#if HAS_STD_CTIME
  /** Use std::tm and std::time_t */
  #include <ctime>


  namespace DCF77 {
    // See  https://en.cppreference.com/w/cpp/chrono/c/time_t
    using time_t = std::time_t;
    using tm = std::tm;
  }

  // See https://en.cppreference.com/w/cpp/chrono/c/tm
  struct PrintableDCF77tm : public DCF77::tm, public printable_t {

  static size_t print(print_t& p, const DCF77::tm& time);
#else
  /** Define own tm and time_t */
  namespace DCF77 {

    // See https://en.cppreference.com/w/cpp/chrono/c/time_t
    using time_t = uint32_t;

    // See https://en.cppreference.com/w/cpp/chrono/c/tm
    struct tm {
      int tm_sec;
      int tm_min;
      int tm_hour;
      int tm_mday;
      int tm_mon;   // [0..11]
      int tm_year;  // years since 1900
      int tm_wday;
      int tm_yday;
      int tm_isdst; // daylight savings active = 1
    };
  }

  struct PrintableDCF77tm : public DCF77::tm, public printable_t {
#endif /* HAS_STD_CTIME */
    static size_t print(print_t& p, const PrintableDCF77tm& time) {
  		return time.printTo(p);
  	}

    /**
     * Implementation of the Printable interface, which
     * allows to print this tm structure.
     *
     * @return The number of printed characters.
     *
     * Example:
     *   PrintableDCF77tm tm;
     *
     *   tm.tm_hour = 15;
     *   tm.tm_min = 10;
     *   tm.tm_sec = 30;
     *   tm.tm_mday = 23;
     *   tm.tm_mon = 1;
     *   tm.tm_year = 2025 - DCF77::TM_YEAR_BASE;
     *   tm.tm_isdst = 0;
     *
     *   Serial.println(tm);
     */
    size_t printTo(print_t& p) const override;
  };

  namespace DCF77 {
    /**
      * TM_YEAR_BASE is the offset between the Anno Domini
      * year and tm_year field in the tm structure.
      *
      * The Anno Domini year is tm.tm_year + DCF77::TM_YEAR_BASE;
      */
    static constexpr int TM_YEAR_BASE = 1900;

    /**
     * Convert a time stamp to a tm structure without time zone conversion.
     *  Hence a local time stamp will return a local tm structure and
     *  a UTC time stamp will return a UTC tm structure.
     *
     *  @param[out] tm The time structure will carry the result.
     *  @param[in] timestamp The timestamp to be converted.
     */
    void timestamp_to_tm(DCF77::tm& tm, const DCF77::time_t timestamp, const int isdst);

    /**
     * Convert a tm structure to a time stamp without time zone conversion.
     *  Hence a local tm structure will return a local time stamp and
     *  a UTC tm structure will return a UTC time stamp.
     *
     *  @param[in] tm the tm structure to be converted
     *  @return the time stamp result.
     *  */
    DCF77::time_t tm_to_timestamp(const DCF77::tm& tm);
  }

#endif /* DCF77tm_H_ */
