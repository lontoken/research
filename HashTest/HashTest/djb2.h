// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _DJB2_H_
#define _DJB2_H_

static const unsigned int kDJB2HashSeed = 5381u;

unsigned int DJB2Hash(const void* buf, size_t len, unsigned int seed = kDJB2HashSeed);

#endif 


