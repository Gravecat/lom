// actions/world-interaction.hpp -- Commands that interact with the world, in ways that aren't specific enough to get their own source files.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once
#include "core/pch.hpp" // Precompiled header

#include "parser/parser-macros.hpp"

namespace westgate::actions::world_interaction {

void    look(PARSER_FUNCTION);      // Look around you. Just look around you.
void    travel(PARSER_FUNCTION);    // Travels in a specific direction.
void    open_close(PARSER_FUNCTION);    // Attempts to open or close a door or similar.
void    wait(PARSER_FUNCTION);      // Waits or rests for a specified period of time.

}   // westgate::actions::world_interaction namespace
