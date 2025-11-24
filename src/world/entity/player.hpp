// world/entity/player.hpp -- The Player class defines the player character; it's mostly just a Mobile, but has a few extra player-specific bits.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

#pragma once
#include "core/pch.hpp" // Precompiled header

#include "world/entity/mobile.hpp"

namespace westgate {

class Player : public Mobile {
public:
                Player() = delete;  // No default constructor; use nullptr on the constructor below.
                Player(FileReader* file);   // Creates a blank Player, then loads its data from a FileReader.
    uint32_t    region() const;     // Checks what Region the Player is currently in.
    void        save(FileWriter* file) override;    // Saves this Player to a save game file.
    void        set_parent_entity(Entity* new_entity_parent = nullptr) override;    // This is a big no-no. We're overriding this method for safety reasons.
    void        set_parent_room(Room* new_room_parent = nullptr) override;  // Sets a new Room as the parent of this Player.
    EntityType  type() const override { return EntityType::PLAYER; }    // Self-identifies this Entity's derived class.

private:
    static constexpr uint32_t   PLAYER_SAVE_VERSION =   1;  // The expected version for saving/loading binary game data.

    unsigned int    region_;    // The current Region the Player is in.
};

Player& player();   // A shortcut instead of using game().player()

}   // namespace westgate
