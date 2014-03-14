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

#ifndef __ACPI_H__
#define __ACPI_H__

#include "bootlogic.h"

/** Generic ACPI table header **/
struct ACPI_DESC_HEADER {
	CHAR8   signature[4];		/* ASCII Table identifier */
	UINT32  length;			/* Length of the table, including the header */
	CHAR8   revision;		/* Revision of the structure */
	CHAR8   checksum;		/* Sum of all fields must be 0 */
	CHAR8   oem_id[6];		/* ASCII OEM identifier */
	CHAR8   oem_table_id[8];	/* ASCII OEM table identifier */
	UINT32  oem_revision;		/* OEM supplied revision number */
	CHAR8   creator_id[4];		/* Vendor ID of utility creator of the table */
	UINT32  creator_revision;	/* Revision of utility creator of the table */
};

struct RSDP_TABLE {
	CHAR8	signature[8];		/* "RSD PTR " */
	CHAR8	checksum;		/* RSDP Checksum (bytes 0-19) */
	CHAR8	oem_id[6];		/* OEM ID String */
	CHAR8	revision;		/* ACPI Revision (0=1.0,2=2.0) */
	UINT32	rsdt_address;		/* 32-bit RSDT Pointer */
	UINT32	length;			/* RSDP Length */
	UINT64	xsdt_address;		/* 64-bit XSDT Pointer */
	CHAR8	extended_checksum;	/* RSDP Checksum (full) */
	CHAR8	reserved[3];		/* Reserved */
};

struct RSDT_TABLE {
	struct ACPI_DESC_HEADER header;	/* System Description Table Header */
	UINT32 entry[1];		/* Table Entries */
};

struct RSCI_TABLE {
	struct ACPI_DESC_HEADER header;	/* System Description Table Header */
	CHAR8 wake_source;		/* How system woken up from S4 or S5 */
	CHAR8 reset_source;		/* How system was reset */
	CHAR8 reset_type;		/* Identify type of reset */
	CHAR8 shutdown_source;		/* How system was last shutdown */
	UINT32 indicators;		/* Bitmap with additional info */
};

/** PIDV Definitions **/
struct ext_id_1 {
	UINT16 customer;
	UINT16 vendor;
	UINT16 device_manufacturer;
	UINT16 platform_family;
	UINT16 product_line;
	UINT16 hardware;
	UINT32 spid_checksum;
	CHAR8 fru[10];
	UINT16 fru_checksum;
	UINT16 reserved;
} __attribute__ ((packed));

struct ext_id_2 {
	UINT32 data1;
	UINT32 data2;
	UINT32 data3;
	UINT32 data4;
} __attribute__ ((packed));

struct PIDV_TABLE {
	struct ACPI_DESC_HEADER header;	/* System Description Table Header */
	CHAR8 part_number[32];		/* Serial number */
	struct ext_id_1 x_id1;		/* Extended ID 1 */
	struct ext_id_2 x_id2;		/* Extended ID 2 */
	UINT32 system_uuid;		/* Identify hardware platform */
};

#define EM_1_USE_IA_APPS_CAP 0
#define EM_1_USE_IA_APPS_RUN 1
struct EM_1_TABLE {
	struct ACPI_DESC_HEADER header;/* System Description Table Header */
	UINT16 ia_apps_run;	       /* Threshold voltage to boot the platform */
	UINT8 ia_apps_cap;	       /* Threshold capacity to boot the platform */
	UINT8 cap_or_volt;	       /* 0: use ia_apps_cap, 1: use ia_apps_run */
	UINT8 boot_on_invalid_batt;    /* Indicates if we should boot with invalid battery */
};

EFI_STATUS list_acpi_tables(void);
EFI_STATUS get_acpi_table(CHAR8 *signature, VOID **table);
enum flow_types acpi_read_flow_type(void);

EFI_STATUS rsci_populate_indicators(void);
enum wake_sources rsci_get_wake_source(void);
enum reset_sources rsci_get_reset_source(void);
EFI_STATUS rsci_set_reset_source(enum reset_sources);
enum reset_types rsci_get_reset_type(void);
enum shutdown_sources rsci_get_shutdown_source(void);

UINT16 em1_get_ia_apps_run(void);
UINT8 em1_get_ia_apps_cap(void);
UINT8 em1_get_cap_or_volt(void);
UINT8 em1_get_boot_on_invalid_batt(void);

void print_pidv(void);
void print_rsci(void);
void dump_acpi_tables(void);
void load_dsdt(void);

#endif /* __ACPI_H__ */
