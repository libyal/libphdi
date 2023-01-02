%option prefix="libphdi_xml_scanner_" outfile="lex.yy.c"
%option never-interactive 8bit
%option noinput nounput noyylineno nounistd
%option noyyalloc noyyrealloc noyyfree

%{
/*
 * XML scanner functions
 *
 * Copyright (C) 2016-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libphdi_libcnotify.h"
#include "libphdi_unused.h"
#include "libphdi_xml_parser.h"

#define YYLEX_PARAM	NULL

int libphdi_xml_scanner_suppress_error   = 1;
size_t libphdi_xml_scanner_buffer_offset = 0;
size_t libphdi_xml_scanner_index         = 0;

#define YY_USER_ACTION	libphdi_xml_scanner_buffer_offset += (size_t) libphdi_xml_scanner_leng;

#if defined( HAVE_DEBUG_OUTPUT )
#define libphdi_xml_scanner_token_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "libphdi_xml_scanner: offset: %" PRIzd " token: %s\n", libphdi_xml_scanner_buffer_offset, string )
#else
#define libphdi_xml_scanner_token_print( string )
#endif

%}

end_of_line             [\r\n|\n|\r]

name			[A-Za-z\x80-\xff_][A-Za-z\x80-\xff_0-9.-]{0,256}
escaped_value		&#([0-9]+|x[0-9a-fA-F]+);

xml_tag_content		([^<&\x00-\x08\x0a-\x1f\x7f]|{end_of_line}[^<&\x00-\x08\x0b\x0c\x0e-\x1f\x7f]|{end_of_line}{escaped_value}|{escaped_value})+
xml_attribute_value	\"([^"&\x00-\x1f\x7f]|{escaped_value}){0,256}\"|\'([^'&\x00-\x1f\x7f]|{escaped_value}){0,256}\'

white_space             [\t ]+

%s XML_CONTENT
%s XML_TAG

%%

{white_space}*"<"{name} {
        libphdi_xml_scanner_token_print(
         "XML_TAG_OPEN_START" );

	BEGIN( XML_TAG );

	libphdi_xml_scanner_index = 0;

	while( libphdi_xml_scanner_index < (size_t) libphdi_xml_scanner_leng )
	{
		if( libphdi_xml_scanner_text[ libphdi_xml_scanner_index++ ] == '<' )
		{
			break;
		}
	}
        libphdi_xml_scanner_lval.string_value.data   = &( libphdi_xml_scanner_text[ libphdi_xml_scanner_index ] );
        libphdi_xml_scanner_lval.string_value.length = (size_t) libphdi_xml_scanner_leng - libphdi_xml_scanner_index;

	return( XML_TAG_OPEN_START );
}

<XML_TAG>{name} {
        libphdi_xml_scanner_token_print(
         "XML_ATTRIBUTE_NAME" );

        libphdi_xml_scanner_lval.string_value.data   = libphdi_xml_scanner_text;
        libphdi_xml_scanner_lval.string_value.length = (size_t) libphdi_xml_scanner_leng;

        return( XML_ATTRIBUTE_NAME );
}

<XML_TAG>"=" {
        libphdi_xml_scanner_token_print(
         "XML_ATTRIBUTE_ASSIGN" );

        return( XML_ATTRIBUTE_ASSIGN );
}

<XML_TAG>{xml_attribute_value} {
        libphdi_xml_scanner_token_print(
         "XML_ATTRIBUTE_VALUE" );

        libphdi_xml_scanner_lval.string_value.data   = &( libphdi_xml_scanner_text[ 1 ] );
        libphdi_xml_scanner_lval.string_value.length = (size_t) libphdi_xml_scanner_leng - 2;

        return( XML_ATTRIBUTE_VALUE );
}

<XML_TAG>"/>"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_TAG_END_SINGLE" );

	BEGIN( INITIAL );

        return( XML_TAG_END_SINGLE );
}

<XML_TAG>">"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_TAG_END" );

	BEGIN( XML_CONTENT );

        return( XML_TAG_END );
}

<XML_CONTENT>{xml_tag_content} {
        libphdi_xml_scanner_token_print(
         "XML_TAG_CONTENT" );

	BEGIN( INITIAL );

        libphdi_xml_scanner_lval.string_value.data   = libphdi_xml_scanner_text;
        libphdi_xml_scanner_lval.string_value.length = (size_t) libphdi_xml_scanner_leng;

        return( XML_TAG_CONTENT );
}

{white_space}*"</"{name}">"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_TAG_CLOSE" );

	BEGIN( INITIAL );

	libphdi_xml_scanner_index = 0;

	while( libphdi_xml_scanner_index < (size_t) libphdi_xml_scanner_leng )
	{
		if( libphdi_xml_scanner_text[ libphdi_xml_scanner_index++ ] == '/' )
		{
			break;
		}
	}
	while( (size_t) libphdi_xml_scanner_leng > libphdi_xml_scanner_index )
	{
		if( libphdi_xml_scanner_text[ --libphdi_xml_scanner_leng ] == '>' )
		{
			break;
		}
	}
        libphdi_xml_scanner_lval.string_value.data   = &( libphdi_xml_scanner_text[ libphdi_xml_scanner_index ] );
        libphdi_xml_scanner_lval.string_value.length = (size_t) libphdi_xml_scanner_leng - libphdi_xml_scanner_index;

	return( XML_TAG_CLOSE );
}

<INITIAL>"<?xml"[^>\x00-\x1f\x7f]{0,256}">"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_PROLOGUE" );

	return( XML_PROLOGUE );
}

<INITIAL>"<!--"([^-\x00-\x1f\x7f]|"-"[^-\x00-\x1f\x7f]){0,256}"-->"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_COMMENT" );

	return( XML_COMMENT );
}

<INITIAL>"<!DOCTYPE"[^>\x00-\x1f\x7f]{0,256}">"{end_of_line}? {
        libphdi_xml_scanner_token_print(
         "XML_DOCTYPE" );

	return( XML_DOCTYPE );
}

{end_of_line} ;

{white_space} ;

. {
        libphdi_xml_scanner_token_print(
         "XML_UNDEFINED" );

	return( XML_UNDEFINED );
}

%%

void *libphdi_xml_scanner_alloc(
       yy_size_t size )
{
	return( memory_allocate(
	         size ) );
}

void *libphdi_xml_scanner_realloc(
       void *buffer,
       yy_size_t size )
{
	return( memory_reallocate(
	         buffer,
	         size ) );
}

void libphdi_xml_scanner_free(
      void *buffer )
{
	memory_free(
	 buffer );
}

int libphdi_xml_scanner_wrap(
     void )
{
	return( 1 );
}

void libphdi_xml_scanner_error(
      void *parser_state LIBPHDI_ATTRIBUTE_UNUSED,
      const char *error_string )
{
	LIBPHDI_UNREFERENCED_PARAMETER( parser_state )

	if( libphdi_xml_scanner_suppress_error == 0 )
	{
	        fprintf(
        	 stderr,
	         "%s at token: %s (offset: %" PRIzd " size: %" PRIzd ")\n",
        	 error_string,
	         libphdi_xml_scanner_text,
	         libphdi_xml_scanner_buffer_offset - (size_t) libphdi_xml_scanner_leng,
	         (size_t) libphdi_xml_scanner_leng );
	}
}

