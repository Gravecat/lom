// world/world.hpp -- The World class handles storing and managing the data for the game world (rooms, items, mobiles, etc.) as well as handling copies of
// templatable things like items and monsters.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once
#include "core/pch.hpp" // Precompiled header

namespace westgate {

class ProcNameGen;  // defined in util/text/namegen.hpp

class World {
public:
                    World();    // Sets up the World object and loads static data into memory.
                    ~World();   // Destructor, explicitly frees memory used.
    ProcNameGen&    namegen() const;    // Returns a reference to the procedural name generator object.

private:
    std::unique_ptr<ProcNameGen>    namegen_ptr_;       // Pointer to the procedural name-generator object.
};

World&  world();    // Shortcut instead of using game()->world()

}   // namespace westgate
