/*
 * Codepage definitions for libphdi
 *
 * Copyright (C) 2015-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBPHDI_CODEPAGE_H )
#define _LIBPHDI_CODEPAGE_H

#include <libphdi/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBPHDI_CODEPAGES
{
	LIBPHDI_CODEPAGE_ASCII				= 20127,

	LIBPHDI_CODEPAGE_ISO_8859_1			= 28591,
	LIBPHDI_CODEPAGE_ISO_8859_2			= 28592,
	LIBPHDI_CODEPAGE_ISO_8859_3			= 28593,
	LIBPHDI_CODEPAGE_ISO_8859_4			= 28594,
	LIBPHDI_CODEPAGE_ISO_8859_5			= 28595,
	LIBPHDI_CODEPAGE_ISO_8859_6			= 28596,
	LIBPHDI_CODEPAGE_ISO_8859_7			= 28597,
	LIBPHDI_CODEPAGE_ISO_8859_8			= 28598,
	LIBPHDI_CODEPAGE_ISO_8859_9			= 28599,
	LIBPHDI_CODEPAGE_ISO_8859_10			= 28600,
	LIBPHDI_CODEPAGE_ISO_8859_11			= 28601,
	LIBPHDI_CODEPAGE_ISO_8859_13			= 28603,
	LIBPHDI_CODEPAGE_ISO_8859_14			= 28604,
	LIBPHDI_CODEPAGE_ISO_8859_15			= 28605,
	LIBPHDI_CODEPAGE_ISO_8859_16			= 28606,

	LIBPHDI_CODEPAGE_KOI8_R				= 20866,
	LIBPHDI_CODEPAGE_KOI8_U				= 21866,

	LIBPHDI_CODEPAGE_WINDOWS_874			= 874,
	LIBPHDI_CODEPAGE_WINDOWS_932			= 932,
	LIBPHDI_CODEPAGE_WINDOWS_936			= 936,
	LIBPHDI_CODEPAGE_WINDOWS_949			= 949,
	LIBPHDI_CODEPAGE_WINDOWS_950			= 950,
	LIBPHDI_CODEPAGE_WINDOWS_1250			= 1250,
	LIBPHDI_CODEPAGE_WINDOWS_1251			= 1251,
	LIBPHDI_CODEPAGE_WINDOWS_1252			= 1252,
	LIBPHDI_CODEPAGE_WINDOWS_1253			= 1253,
	LIBPHDI_CODEPAGE_WINDOWS_1254			= 1254,
	LIBPHDI_CODEPAGE_WINDOWS_1255			= 1255,
	LIBPHDI_CODEPAGE_WINDOWS_1256			= 1256,
	LIBPHDI_CODEPAGE_WINDOWS_1257			= 1257,
	LIBPHDI_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBPHDI_CODEPAGE_US_ASCII			LIBPHDI_CODEPAGE_ASCII

#define LIBPHDI_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBPHDI_CODEPAGE_ISO_8859_1
#define LIBPHDI_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBPHDI_CODEPAGE_ISO_8859_2
#define LIBPHDI_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBPHDI_CODEPAGE_ISO_8859_3
#define LIBPHDI_CODEPAGE_ISO_NORTH_EUROPEAN		LIBPHDI_CODEPAGE_ISO_8859_4
#define LIBPHDI_CODEPAGE_ISO_CYRILLIC			LIBPHDI_CODEPAGE_ISO_8859_5
#define LIBPHDI_CODEPAGE_ISO_ARABIC			LIBPHDI_CODEPAGE_ISO_8859_6
#define LIBPHDI_CODEPAGE_ISO_GREEK			LIBPHDI_CODEPAGE_ISO_8859_7
#define LIBPHDI_CODEPAGE_ISO_HEBREW			LIBPHDI_CODEPAGE_ISO_8859_8
#define LIBPHDI_CODEPAGE_ISO_TURKISH			LIBPHDI_CODEPAGE_ISO_8859_9
#define LIBPHDI_CODEPAGE_ISO_NORDIC			LIBPHDI_CODEPAGE_ISO_8859_10
#define LIBPHDI_CODEPAGE_ISO_THAI			LIBPHDI_CODEPAGE_ISO_8859_11
#define LIBPHDI_CODEPAGE_ISO_BALTIC			LIBPHDI_CODEPAGE_ISO_8859_13
#define LIBPHDI_CODEPAGE_ISO_CELTIC			LIBPHDI_CODEPAGE_ISO_8859_14

#define LIBPHDI_CODEPAGE_ISO_LATIN_1			LIBPHDI_CODEPAGE_ISO_8859_1
#define LIBPHDI_CODEPAGE_ISO_LATIN_2			LIBPHDI_CODEPAGE_ISO_8859_2
#define LIBPHDI_CODEPAGE_ISO_LATIN_3			LIBPHDI_CODEPAGE_ISO_8859_3
#define LIBPHDI_CODEPAGE_ISO_LATIN_4			LIBPHDI_CODEPAGE_ISO_8859_4
#define LIBPHDI_CODEPAGE_ISO_LATIN_5			LIBPHDI_CODEPAGE_ISO_8859_9
#define LIBPHDI_CODEPAGE_ISO_LATIN_6			LIBPHDI_CODEPAGE_ISO_8859_10
#define LIBPHDI_CODEPAGE_ISO_LATIN_7			LIBPHDI_CODEPAGE_ISO_8859_13
#define LIBPHDI_CODEPAGE_ISO_LATIN_8			LIBPHDI_CODEPAGE_ISO_8859_14
#define LIBPHDI_CODEPAGE_ISO_LATIN_9			LIBPHDI_CODEPAGE_ISO_8859_15
#define LIBPHDI_CODEPAGE_ISO_LATIN_10			LIBPHDI_CODEPAGE_ISO_8859_16

#define LIBPHDI_CODEPAGE_KOI8_RUSSIAN			LIBPHDI_CODEPAGE_KOI8_R
#define LIBPHDI_CODEPAGE_KOI8_UKRAINIAN			LIBPHDI_CODEPAGE_KOI8_U

#define LIBPHDI_CODEPAGE_WINDOWS_THAI			LIBPHDI_CODEPAGE_WINDOWS_874
#define LIBPHDI_CODEPAGE_WINDOWS_JAPANESE		LIBPHDI_CODEPAGE_WINDOWS_932
#define LIBPHDI_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBPHDI_CODEPAGE_WINDOWS_936
#define LIBPHDI_CODEPAGE_WINDOWS_KOREAN			LIBPHDI_CODEPAGE_WINDOWS_949
#define LIBPHDI_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBPHDI_CODEPAGE_WINDOWS_950
#define LIBPHDI_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBPHDI_CODEPAGE_WINDOWS_1250
#define LIBPHDI_CODEPAGE_WINDOWS_CYRILLIC		LIBPHDI_CODEPAGE_WINDOWS_1251
#define LIBPHDI_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBPHDI_CODEPAGE_WINDOWS_1252
#define LIBPHDI_CODEPAGE_WINDOWS_GREEK			LIBPHDI_CODEPAGE_WINDOWS_1253
#define LIBPHDI_CODEPAGE_WINDOWS_TURKISH		LIBPHDI_CODEPAGE_WINDOWS_1254
#define LIBPHDI_CODEPAGE_WINDOWS_HEBREW			LIBPHDI_CODEPAGE_WINDOWS_1255
#define LIBPHDI_CODEPAGE_WINDOWS_ARABIC			LIBPHDI_CODEPAGE_WINDOWS_1256
#define LIBPHDI_CODEPAGE_WINDOWS_BALTIC			LIBPHDI_CODEPAGE_WINDOWS_1257
#define LIBPHDI_CODEPAGE_WINDOWS_VIETNAMESE		LIBPHDI_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_CODEPAGE_H ) */

