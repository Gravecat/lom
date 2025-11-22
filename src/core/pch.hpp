// core/pch.hpp -- Precompiled global header, that includes things which are used pretty much everywhere in this project.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once

#include <climits>      // Integer limit macros like UINT_MAX
#include <cstddef>      // Primarily included here for size_t
#include <cstdint>      // Frequently-used integer defintions like uint32_t
#include <cstdlib>      // EXIT_FAILURE, EXIT_SUCCESS macro constants
#include <memory>       // std::unique_ptr and std::move are used frequently
#include <stdexcept>    // std::runtime_error is used frequently to throw error exceptions
#include <string>       // std::string is used in almost every part of this project
#include <vector>       // std::vector is used frequently enough to belong here too
