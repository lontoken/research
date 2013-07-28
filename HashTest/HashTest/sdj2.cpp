// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "djb2.h"

unsigned int DJB2Hash(const void* buf, size_t len, unsigned int hash) {
  const unsigned char* s = reinterpret_cast<const unsigned char*>(buf);
  if (len > 0) {
    do {
      hash = hash * 33 + *s++;
    } while (--len);
  }
  return hash;
}
