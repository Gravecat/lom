// src/parser/parser.hpp -- The parser processes input from the player and converts it into commands in the game world.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once
#include "core/pch.hpp" // Precompiled header

namespace westgate {
namespace parser {

void    process_input(const std::string& input);    // Processes input from the player.
bool    yes_no();   // Displays a yes/no prompt for the player, returns their choice.

} } // parser, westgate namespaces
