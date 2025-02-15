// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "nanoarrow_ipc.h"

#ifndef NANOARROW_IPC_HPP_INCLUDED
#define NANOARROW_IPC_HPP_INCLUDED

namespace nanoarrow {

namespace internal {

static inline void init_pointer(struct ArrowIpcDecoder* data) {
  data->private_data = nullptr;
}

static inline void move_pointer(struct ArrowIpcDecoder* src,
                                struct ArrowIpcDecoder* dst) {
  memcpy(dst, src, sizeof(struct ArrowIpcDecoder));
  src->private_data = nullptr;
}

static inline void release_pointer(struct ArrowIpcDecoder* data) {
  ArrowIpcDecoderReset(data);
}

static inline void init_pointer(struct ArrowIpcInputStream* data) {
  data->release = nullptr;
}

static inline void move_pointer(struct ArrowIpcInputStream* src,
                                struct ArrowIpcInputStream* dst) {
  memcpy(dst, src, sizeof(struct ArrowIpcInputStream));
  src->release = nullptr;
}

static inline void release_pointer(struct ArrowIpcInputStream* data) {
  if (data->release != nullptr) {
    data->release(data);
  }
}

}  // namespace internal
}  // namespace nanoarrow

#include "nanoarrow.hpp"

namespace nanoarrow {

namespace ipc {

/// \defgroup nanoarrow_ipc_hpp-unique Unique object wrappers
///
/// Extends the unique object wrappers in nanoarrow.hpp to include C structs
/// defined in the nanoarrow_ipc.h header.
///
/// @{

/// \brief Class wrapping a unique struct ArrowIpcDecoder
using UniqueDecoder = internal::Unique<struct ArrowIpcDecoder>;

/// \brief Class wrapping a unique struct ArrowIpcInputStream
using UniqueInputStream = internal::Unique<struct ArrowIpcInputStream>;

/// @}

}  // namespace ipc

}  // namespace nanoarrow

#endif
