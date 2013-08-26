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
bool military_quoter;
bool gurerrot;
bool s2center;
bool boss_gurerrot_dead;
uint32 militiacounter;
uint32 crossbowman;
uint32 abom;
uint64 liamGUID;

Position const eventPositionsTeamA[7] =
{
    {-1408.63f, 1260.13f, 36.43f, 1.82f}, // Liam Home Position  #0 
    {-1436.97f, 1360.36f, 35.556f, 4.03f}, // Battle Run straight         #1 STAGE1 
    {-1493.54f, 1405.87f, 35.556f, 2.84f}, // back middle               #2 STAGE 1
    {-1575.13f, 1317.56f, 35.556f, 3.190f}, // crosbowman complete, canon arrive #3 STAGE2_PREPARE
    {-1635.31f, 1305.91f, 19.66f, 3.09f}, // Stage 2               #4
    {-1762.86f, 1347.87f, 19.43f, 0.65f},  // Center military district #5
    {-1721.62f, 1398.47f, 21.67f, 0.85f},  // BOSS Gurerrot #6
};

Position const eventPositionsTeamB[8] =
{
    {-1430.48f, 1362.39f, 35.556f, 1.29f}, // Event START Run right STAGE1
    {-1444.30f, 1418.51f, 35.556f, 1.62f}, // Turn left STAGE1
    {-1503.71f, 1389.28f, 35.556f, 4.11f}, // Go straight-right
    {-1519.27f, 1341.73f, 35.556f, 3.09f},  // Stage1 #3
    {-1575.13f, 1317.56f, 35.556f, 3.190f}, // crosbowman complete, canon arrive #2 STAGE2_PREPARE #4
    {-1635.31f, 1305.91f, 19.66f, 3.09f}, // Stage 2  #5
    {-1688.45f, 1347.13f, 15.13f, 0.65f},  // Center military district #6
    {-1721.62f, 1398.47f, 21.67f, 0.85f},  // BOSS Gurerrot #7
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
    SAY_RANDOM_TXT         = 11,
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
    STAGE2_PREPARE           = 18,
    STAGE2_A_FIGHT           = 19,
    STAGE2_A_CENTER          = 20,
    STAGE_1_BOSS             = 21,
    STAGE_1_BOSS_FIGHT       = 22,
    STAGE2_B_FIGHT           = 23,
    STAGE2_B_1               = 24,

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