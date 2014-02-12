/*
 * Copyright (c) 2013, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <efi.h>
#include <efilib.h>
#include "stdlib.h"

#include "efilinux.h"

#define UINTN_MAX ((UINTN)-1);
#define offsetof(TYPE, MEMBER) ((UINTN) &((TYPE *)0)->MEMBER)

EFI_STATUS str_to_stra(CHAR8 *dst, CHAR16 *src, UINTN len);
CHAR16 *stra_to_str(CHAR8 *src);
VOID StrNCpy(OUT CHAR16 *dest, IN const CHAR16 *src, UINT32 n);
UINT8 getdigit(IN CHAR16 *str);
EFI_STATUS string_to_guid(IN CHAR16 *in_guid_str, OUT EFI_GUID *guid);
UINT32 swap_bytes32(UINT32 n);
UINT16 swap_bytes16(UINT16 n);
void copy_and_swap_guid(EFI_GUID *dst, const EFI_GUID *src);
EFI_STATUS open_partition(
                IN const EFI_GUID *guid,
                OUT UINT32 *MediaIdPtr,
                OUT EFI_BLOCK_IO **BlockIoPtr,
                OUT EFI_DISK_IO **DiskIoPtr);
void path_to_dos(CHAR16 *path);
CHAR8 *append_strings(CHAR8 *s1, CHAR8 *s2);
UINTN strtoul(const CHAR16 *nptr, CHAR16 **endptr, UINTN base);

/* Basic port I/O */
static inline void outb(UINT16 port, UINT8 value)
{
	asm volatile("outb %0,%1" : : "a" (value), "dN" (port));
}

static inline UINT8 inb(UINT16 port)
{
	UINT8 value;
	asm volatile("inb %1,%0" : "=a" (value) : "dN" (port));
	return value;
}

#endif
