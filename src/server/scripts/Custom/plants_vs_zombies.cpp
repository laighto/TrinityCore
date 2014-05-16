/*
 * Copyright (C) 2014  chaosua2008@gmail.com
 *
 * EVENT written by chaosua in 2014 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"

/*
Worcground Plants VS Zombies
Quest:
28617 - Flower Power
28733 - Basic Botany
28744 - Ghouls hate My grains
28747 - Someone Setup the Pumpkin Bomb
28748 - Lawn of the Dead 
28751 - Tending the Garden

NPC:
49687- Brazie the Botanist (questgiver)
49194 - Solar power
49176 - botanist Vehicle
49192 - Fertilize-o-tron 2000

GO:
207282 - oasis flower
207285 - Thorns

Spell:
91688 - Create Sun Power
91683 - Create Botanist's Vehicle
91680 - Create Lawnmower
91646 - Plant Sunflower
91710 - Plant Strangler Vine
91649 - Plant Spitter
92157 - Plant Pumpkin Bomb
91704 - Plant Rocknut
92440 - Plant Freezya
91740 - Create Goal Stalker
91834 - Create Ghoul
91988 - Create Spitter Target
Progress bars:
91651 - 0/5
92259 - 0/4
92321 - 0/7
92597 - 0/7
92598 - 0/35000 Warden Stillwater

*/