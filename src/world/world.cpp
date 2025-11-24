// world/world.cpp -- The World class handles storing and managing the data for the game world (rooms, items, mobiles, etc.) as well as handling copies of
// templatable things like items and monsters.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "core/core.hpp"
#include "core/game.hpp"
#include "util/text/namegen.hpp"
#include "world/world.hpp"

using std::make_unique;
using std::runtime_error;

namespace westgate {

// Sets up the World object and loads static data into memory.
World::World() : namegen_ptr_(make_unique<ProcNameGen>())
{
    core().log("Loading static data into memory.");
    namegen_ptr_->load_namelists();
}

// Destructor, explicitly frees memory used.
World::~World() { namegen_ptr_.reset(nullptr); }

// Returns a reference to the procedural name generator object.
ProcNameGen& World::namegen() const
{
    if (!namegen_ptr_) throw runtime_error("Attempt to access null ProcNameGen object!");
    return *namegen_ptr_;
}

// Shortcut instead of using game()->world()
World& world() { return game().world(); }

}   // namespace westgate
