/*
 * Copyright (C) [2004, 2005, 2006], Hyperic, Inc.
 * This file is part of SIGAR.
 * 
 * SIGAR is free software; you can redistribute it and/or modify
 * it under the terms version 2 of the GNU General Public License as
 * published by the Free Software Foundation. This program is distributed
 * in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 */

#ifndef SIGAR_UTIL_H
#define SIGAR_UTIL_H

/* most of this is crap for dealing with linux /proc */
#define UITOA_BUFFER_SIZE \
    (sizeof(int) * 3 + 1)

#define SSTRLEN(s) \
    (sizeof(s)-1)

#define sigar_strtoul(ptr) \
    strtoul(ptr, &ptr, 10)

#define sigar_strtoull(ptr) \
    strtoull(ptr, &ptr, 10)

#define sigar_isspace(c) \
    (isspace(((unsigned char)(c))))

#define sigar_isdigit(c) \
    (isdigit(((unsigned char)(c))))

#define sigar_isalpha(c) \
    (isalpha(((unsigned char)(c))))

#define sigar_isupper(c) \
    (isupper(((unsigned char)(c))))

#ifndef PROC_FS_ROOT
#define PROC_FS_ROOT "/proc/"
#endif

#ifndef PROCP_FS_ROOT
#define PROCP_FS_ROOT "/proc/"
#endif

char *sigar_uitoa(char *buf, unsigned int n, int *len);

int sigar_inet_ntoa(sigar_t *sigar,
                    sigar_uint32_t address,
                    char *addr_str);

struct hostent *sigar_gethostbyname(const char *name,
                                    sigar_hostent_t *data);

SIGAR_INLINE char *sigar_skip_line(char *buffer, int buflen);

SIGAR_INLINE char *sigar_skip_token(char *p);

SIGAR_INLINE char *sigar_skip_multiple_token(char *p, int count);

char *sigar_getword(char **line, char stop);

int sigar_file2str(const char *fname, char *buffer, int buflen);

int sigar_proc_file2str(char *buffer, int buflen,
                        sigar_pid_t pid,
                        const char *fname,
                        int fname_len);

#define SIGAR_PROC_FILE2STR(buffer, pid, fname) \
    sigar_proc_file2str(buffer, sizeof(buffer), \
                        pid, fname, SSTRLEN(fname))

#define SIGAR_PROC_FILENAME(buffer, pid, fname) \
    sigar_proc_filename(buffer, sizeof(buffer), \
                        pid, fname, SSTRLEN(fname))

#define SIGAR_SKIP_SPACE(ptr) \
    while (sigar_isspace(*ptr)) ++ptr

char *sigar_proc_filename(char *buffer, int buflen,
                          sigar_pid_t pid,
                          const char *fname, int fname_len);

int sigar_proc_list_procfs_get(sigar_t *sigar,
                               sigar_proc_list_t *proclist);

int sigar_proc_fd_count(sigar_t *sigar, sigar_pid_t pid,
                        sigar_uint64_t *total);

/* linux + freebsd */
int sigar_procfs_args_get(sigar_t *sigar, sigar_pid_t pid,
                          sigar_proc_args_t *procargs);

int sigar_mem_calc_ram(sigar_t *sigar, sigar_mem_t *mem);

double sigar_file_system_usage_calc_used(sigar_t *sigar,
                                         sigar_file_system_usage_t *fs);

void sigar_cpu_model_adjust(sigar_t *sigar, sigar_cpu_info_t *info);

int sigar_cpu_mhz_from_model(char *model);

char *sigar_get_self_path(sigar_t *sigar);

typedef struct sigar_cache_entry_t sigar_cache_entry_t;

struct sigar_cache_entry_t {
    sigar_cache_entry_t *next;
    sigar_uint64_t id;
    void *value;
};

typedef struct {
    sigar_cache_entry_t **entries;
    unsigned int count, size;
    void (*free_value)(void *ptr);
} sigar_cache_t;

sigar_cache_t *sigar_cache_new(int size);

sigar_cache_entry_t *sigar_cache_get(sigar_cache_t *table,
                                     sigar_uint64_t key);

sigar_cache_entry_t *sigar_cache_find(sigar_cache_t *table,
                                      sigar_uint64_t key);

void sigar_cache_destroy(sigar_cache_t *table);

#endif /* SIGAR_UTIL_H */
