#ifndef _SDBM_H
#define _SDBM_H

#pragma once

unsigned int SdbmHash(const void* buf )
{
    const unsigned char *str = reinterpret_cast<const unsigned char*>(buf);

    unsigned int hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

#endif