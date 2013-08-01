#ifndef _FNV_H_
#define _FNV_H_

typedef unsigned int Fnv32_t;

#define FNV0_32_INIT ((Fnv32_t)0)

#define FNV_32_PRIME ((Fnv32_t)0x01000193)

Fnv32_t fnv_32_buf(const void *buf, size_t len, Fnv32_t hval = FNV0_32_INIT);

Fnv32_t fnv_32_str(const char *str, Fnv32_t hval = FNV0_32_INIT);

Fnv32_t fnv_32a_buf(const void *buf, size_t len, Fnv32_t hval = FNV0_32_INIT);

Fnv32_t fnv_32a_str(const char *str, Fnv32_t hval = FNV0_32_INIT);

#endif