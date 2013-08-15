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

bool event_active;
bool intro;
bool event_intro;
bool stage2;
bool stage2b;
bool resetall;
uint32 militiacounter;
uint32 crossbowman;
uint64 liamGUID;

Position const eventPositionsTeamA[6] =
{
    {-1408.63f, 1260.13f, 36.43f, 1.82f}, // Liam Home Position  #0 
    {-1436.97f, 1360.36f, 35.556f, 4.03f}, // Battle Run straight         #1 STAGE1 
    {-1493.54f, 1405.87f, 35.556f, 2.84f}, // back middle               #2 STAGE 1
    {-1575.13f, 1317.56f, 35.556f, 3.190f}, // crosbowman complete, canon arrive #3 STAGE2
    {-506.1137f, 2213.306f, 539.2870f, 0.0f}, // back left                 #4
    {-509.0040f, 2211.743f, 539.2870f, 0.0f},  // back right                #3
};

Position const eventPositionsTeamB[7] =
{
    {-1430.48f, 1362.39f, 35.556f, 1.29f}, // Event START Run right STAGE1
    {-1444.30f, 1418.51f, 35.556f, 1.62f}, // Turn left STAGE1
    {-1503.71f, 1389.28f, 35.556f, 4.11f}, // Go straight-right
    {-1519.27f, 1341.73f, 35.556f, 3.09f},  // Stage1 #3
    {-1575.13f, 1317.56f, 35.556f, 3.190f}, // crosbowman complete, canon arrive #2 STAGE2 #4
    {-506.6607f, 2211.367f, 539.2870f, 0.0f}, // back middle               #3
    {-506.1137f, 2213.306f, 539.2870f, 0.0f}, // back left                 #4
};

enum ScriptTexts
{
    SAY_INTRO_1            = 1,
    SAY_INTRO_2            = 2,
    SAY_INTRO_3            = 3,
    SAY_INTRO_4            = 4,
    SAY_INTRO_5            = 5,
    SAY_INTRO_6            = 6,
    SAY_INTRO_7            = 7,
    SYA_RANDOM_TXT         = 11,
};
enum EventTypes
{
    EVENT_INTRO_2            = 1,
    EVENT_INTRO_3            = 2,
    EVENT_INTRO_4            = 3,
    EVENT_INTRO_5            = 4,
    EVENT_INTRO_6            = 5,
    EVENT_INTRO_7            = 6,
    EVENT_BEGIN_BATTLE       = 7,
    STAGE1                   = 8,
    STAGE2                   = 9,
    STAGE1_A                 = 10,
    STAGE1_B                 = 11,
    STAGE1_B_FIGHT           = 12,
    STAGE1_B_1               = 13,
    STAGE1_B_2               = 14,
    STAGE1_B_3               = 15,
    STAGE2_B                 = 16,
    RESET_ALL                = 17,
};

enum QuestDatas 
{
    QUEST_BFGC = 24904,
};

enum SpellDatas
{
    SPELL_BFGC_CONPLETE = 72349,  // completes quest requirements
    SPELL_SOLDIER_OF_BFGC = 72069, // Liam's aura
};

enum NPCDatas
{
    KRENNAN_ARANAS = 38553,
    PRINCE_LIAM_GREYMANE = 38218,
    GILNEAN_MILLITIA = 38221,

    // Enemies
    GORERROT = 38331, //First big boss
    LADY_SYLVANAS_WINDRUNNER = 38469, //ENDS EVENT, second big boss
    FORSAKEN_CROSSBOWMAN = 38210,
    VILE_ABOMINATION = 38420,

    // Triggers
    GENERIC_TRIGGER_LAB_LARGE_AOI = 28332,
};