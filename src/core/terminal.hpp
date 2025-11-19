// core/terminal.hpp -- Includes the rang library and iostream for printing coloured text to the terminal.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once
#include "core/global.hpp"

#include <iostream> // std::cout and associated functionality

// rang library, used to add colour to the terminal.
// The #pragma lines are to suppress compiler warnings.
#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
#include "3rdparty/rang/rang.hpp"
#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif

using std::cout;
using std::endl;
using namespace rang;
