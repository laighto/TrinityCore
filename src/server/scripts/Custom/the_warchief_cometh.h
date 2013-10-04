/*
 * Copyright (C) 2013  chaosua2008@gmail.com
 *
 * EVENT written by chaosua in 2013 
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

bool start_event;
bool arrivedw;
bool scedule_sequence;
bool allowcast;
bool allowmorph;

Position const eventPositions[5] =
{
    {1379.61f, 1043.43f, 54.19f, 3.73f}, //near sylvanas
    {1403.69f, 1061.89f, 60.48f, 3.90f},
    {1395.29f, 1023.23f, 53.14f, 0.0f}, //left 
    {1358.71f, 1056.25f, 53.04f, 0.0f}, //right
    {1376.02f, 1045.70f, 53.36f, 5.703f} //cromush pos to go
};

enum HellscreamTXT
{
    SAY_TXT_3            = 0,
    SAY_TXT_4            = 1,

    SAY_TXT_8            = 2,

    SAY_TXT_13           = 3,
    SAY_TXT_14           = 4,

    SAY_TXT_16           = 5,
    SAY_TXT_17           = 6,

    SAY_TXT_19           = 7,
    SAY_TXT_20           = 8,

    SAY_TXT_22           = 9
};

enum CromushTXT
{
    SAY_TXT_21           = 0
};

enum SylvanasTXT
{
    SAY_TXT_1            = 0,
    SAY_TXT_2            = 1,

    SAY_TXT_5            = 2,
    SAY_TXT_6            = 3,
    SAY_TXT_7            = 4,
    
    SAY_TXT_9            = 5,
    SAY_TXT_10           = 6,
    SAY_TXT_11           = 7,
    SAY_TXT_12           = 8,

    SAY_TXT_15           = 9,

    SAY_TXT_18           = 10
};

enum EventTypes
{
    EVENT_1            = 1,
    EVENT_2            = 2,
    EVENT_3            = 3,
    EVENT_4            = 4,
    EVENT_5            = 5,
    EVENT_6            = 6,
    EVENT_7            = 7,
    EVENT_8            = 8,
    EVENT_9            = 9,
    EVENT_10           = 10,
    EVENT_11           = 11,
    EVENT_12           = 12,
    EVENT_13           = 13,
    EVENT_14           = 14,
    EVENT_15           = 15,
    EVENT_16           = 16,
    EVENT_17           = 17,
    EVENT_18           = 18,
    EVENT_19           = 19,
    EVENT_20           = 20,
    EVENT_21           = 21,
    EVENT_22           = 22,
    ARRIVE             = 23,
    LEFT               = 24,
    RESET              = 25,
    AGATHA             = 26,
    MORPH              = 27
};

enum QuestDatas 
{
    QUEST_TWC = 26965,
};

enum SpellDatas
{
    SPELL_QUEST_COMPLETE = 83384,  // completes quest requirements
    SPELL_REVIVE_UNDEAD = 83173,
    SPELL_FEIGHT_DEATH  = 45801
};

enum NPCGODatas
{
    NPC_WARCHIEF = 44629,
    GO_PORTAL_FROM_ORGRIMMAR = 193427
};