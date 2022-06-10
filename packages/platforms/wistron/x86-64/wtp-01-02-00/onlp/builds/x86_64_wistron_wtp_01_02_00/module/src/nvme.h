/*
 * Definitions for the NVM Express interface
 * Copyright (c) 2011-2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _NVME_H
#define _NVME_H

#include <dirent.h>
#include <stdbool.h>
#include <stdint.h>
#include <endian.h>
#include <sys/time.h>

#include "linux/nvme.h"

struct nvme_subsystem;
struct nvme_ctrl;

struct nvme_namespace {
	char *name;
	struct nvme_ctrl *ctrl;

	unsigned nsid;
	struct nvme_id_ns ns;
};

struct nvme_ctrl {
	char *name;
	char *path;
	struct nvme_subsystem *subsys;

	char *address;
	char *transport;
	char *state;
	char *ana_state;
	char *traddr;
	char *trsvcid;
	char *host_traddr;
	char *hostnqn;
	char *hostid;

	struct nvme_id_ctrl id;

	int    nr_namespaces;
	struct nvme_namespace *namespaces;
};

struct nvme_subsystem {
	char *name;
	char *subsysnqn;

	int    nr_ctrls;
	struct nvme_ctrl *ctrls;

	int    nr_namespaces;
	struct nvme_namespace *namespaces;
};

struct nvme_topology {
	int    nr_subsystems;
	struct nvme_subsystem *subsystems;
};

#define SYS_NVME "/sys/class/nvme"

extern const char *devicename;
extern const char *output_format;

char *nvme_char_from_block(char *block);
void *mmap_registers(const char *dev);

extern int current_index;
int scan_ctrl_namespace_filter(const struct dirent *d);
int scan_namespace_filter(const struct dirent *d);
int scan_ctrl_paths_filter(const struct dirent *d);
int scan_ctrls_filter(const struct dirent *d);
int scan_subsys_filter(const struct dirent *d);
int scan_dev_filter(const struct dirent *d);

int scan_subsystems(struct nvme_topology *t, const char *subsysnqn,
		    __u32 ns_instance, int nsid, char *dev_dir);
void free_topology(struct nvme_topology *t);
char *get_nvme_subsnqn(char *path);
char *nvme_get_ctrl_attr(char *path, const char *attr);

void *nvme_alloc(size_t len, bool *huge);
void nvme_free(void *p, bool huge);

unsigned long long elapsed_utime(struct timeval start_time,
					struct timeval end_time);
#endif /* _NVME_H */
