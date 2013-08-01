#include "fnv.h"

Fnv32_t fnv_32_buf(const void *buf, size_t len, Fnv32_t hval)
{
    const unsigned char *bp = (const unsigned char *)buf;	/* start of buffer */
    const unsigned char *be = bp + len;		/* beyond end of buffer */

    /*
    * FNV-1 hash each octet in the buffer
    */
    while (bp < be) {

        hval *= FNV_32_PRIME;

        /* xor the bottom with the current octet */
        hval ^= (Fnv32_t)*bp++;
    }

    /* return our new hash value */
    return hval;
}


Fnv32_t fnv_32_str(const char *str, Fnv32_t hval)
{
    const unsigned char *s = (const unsigned char *)str;	/* unsigned string */

    /*
    * FNV-1 hash each octet in the buffer
    */
    while (*s) {

        hval *= FNV_32_PRIME;

        /* xor the bottom with the current octet */
        hval ^= (Fnv32_t)*s++;
    }

    /* return our new hash value */
    return hval;
}

Fnv32_t fnv_32a_buf(const void *buf, size_t len, Fnv32_t hval)
{
    const unsigned char *bp = (unsigned char *)buf;	/* start of buffer */
    const unsigned char *be = bp + len;		/* beyond end of buffer */

    /*
    * FNV-1a hash each octet in the buffer
    */
    while (bp < be) {

        /* xor the bottom with the current octet */
        hval ^= (Fnv32_t)*bp++;

        hval *= FNV_32_PRIME;

    }

    /* return our new hash value */
    return hval;
}


Fnv32_t fnv_32a_str(const char *str, Fnv32_t hval)
{
    const unsigned char *s = (const unsigned char *)str;	/* unsigned string */

    /*
    * FNV-1a hash each octet in the buffer
    */
    while (*s) {

        /* xor the bottom with the current octet */
        hval ^= (Fnv32_t)*s++;

        hval *= FNV_32_PRIME;

    }

    /* return our new hash value */
    return hval;
}