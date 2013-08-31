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
uint32 crossbowman;
uint32 abom;
bool pos1;
bool pos2;
bool pos3;
bool pos4;
bool mpos1;
bool mpos2;
bool mpos3;
bool s3pos;
bool s3posb;
bool endpoint;
bool stage4;
bool boss2;
bool bfgcdone;
Creature* militia[20];

Position const eventPositionsMilitia[20] =
{
    {-1414.01f, 1252.87f, 36.4277f, 1.82248f},
    {-1401.23f, 1256.08f, 36.4277f, 1.78689f},
    {-1404.68f, 1255.06f, 36.4277f, 1.83401f},
    {-1409.34f, 1254.0f, 36.4277f, 1.76726f},
    {-1412.72f, 1248.8f, 36.4277f, 1.82805f},
    {-1408.44f, 1249.96f, 36.4277f, 1.8359f},
    {-1403.72f, 1251.25f, 36.4277f, 1.8359f},
    {-1400.0f, 1252.25f, 36.4277f, 1.8359f},
    {-1398.9f, 1248.2f, 36.4277f, 1.8359f},
    {-1402.56f, 1247.44f, 36.4277f, 1.77134f},
    {-1407.73f, 1246.53f, 36.4277f, 1.74385f},
    {-1411.73f, 1245.83f, 36.4277f, 1.74385f},
    {-1410.76f, 1241.59f, 36.3279f, 1.84595f},
    {-1406.95f, 1242.67f, 36.3628f, 1.84595f},
    {-1402.01f, 1244.07f, 36.4077f, 1.84595f},
    {-1398.3f, 1245.11f, 36.4267f, 1.84595f},
    {-1397.47f, 1242.15f, 35.5597f, 1.84595f},
    {-1401.27f, 1241.55f, 35.6481f, 1.72726f},
    {-1406.42f, 1240.54f, 35.7236f, 1.78224f},
    {-1410.29f, 1239.71f, 35.7615f, 1.78224f},
};

Position const eventPositionsTeamA[12] =
{
    {-1408.63f, 1260.13f, 36.43f, 1.82f}, // Liam Home Position  #0 
    {-1436.97f, 1360.36f, 35.556f, 4.03f}, // Battle Run straight         #1 STAGE1 
    {-1493.54f, 1405.87f, 35.556f, 2.84f}, // back middle               #2 STAGE 1
    {-1572.08f, 1317.48f, 35.556f, 3.13f}, // crosbowman complete, canon arrive #3 STAGE2_PREPARE
    {-1632.15f, 1308.01f, 19.66f, 3.30f}, // Stage 2               #4
    {-1762.86f, 1347.87f, 19.43f, 0.65f},  // Center military district #5
    {-1721.62f, 1398.47f, 21.67f, 0.85f},  // BOSS Gurerrot #6

    {-1788.89f, 1375.696f, 19.83f, 2.20f},  // Move to bridge #7
    {-1804.03f, 1460.228f, 18.86f, 1.53f},  // Move to bridge #8
    {-1803.73f, 1518.038f, 19.78f, 1.49f},  // Move to bridge #9
    {-1794.12f, 1577.45f, 20.50f, 1.15f},  // Move after bridge #10
    {-1756.99f, 1643.99f, 20.38f, 0.53f},  // End Point #11
};

Position const eventPositionsTeamB[9] =
{
    {-1430.48f, 1362.39f, 35.556f, 1.29f}, // Event START Run right STAGE1
    {-1444.30f, 1418.51f, 35.556f, 1.62f}, // Turn left STAGE1
    {-1503.71f, 1389.28f, 35.556f, 4.11f}, // Go straight-right
    {-1519.27f, 1341.73f, 35.556f, 3.09f},  // Stage1 #3
    {-1572.08f, 1317.48f, 35.556f, 3.13f}, // crosbowman complete, canon arrive #2 STAGE2_PREPARE #4
    {-1632.15f, 1308.01f, 19.66f, 3.30f}, // Stage 2  #5
    {-1688.45f, 1347.13f, 15.13f, 0.65f},  // Center military district #6
    {-1721.62f, 1398.47f, 21.67f, 0.85f},  // BOSS Gurerrot #7
    {-1705.44f, 1633.82f, 20.49f, 5.51f},  // BOSS Sylvanas #8
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
    STAGE_1_FIGHT            = 8,
    STAGE2                   = 9,
    STAGE_1_CENTER           = 10,
    STAGE_1_B_FIGHT          = 11,
    STAGE1_B_1               = 12,
    STAGE1_B_2               = 13,
    STAGE1_B_3               = 14,
    STAGE2_B                 = 15,
    RESET_ALL                = 16,
    STAGE2_PREPARE           = 17,
    STAGE2_A_FIGHT           = 18,
    STAGE2B                  = 19,
    STAGE2_A_CENTER          = 20,
    STAGE_BOSS_G             = 21,
    STAGE_BOSS_FIGHT_G       = 22,
    STAGE_2_B_FIGHT          = 23,
    STAGE2_B_1               = 24,
    STAGE_BOSS_Gm            = 25,
    STAGE_BOSS_FIGHT_Gm      = 26,
   //gurerrot defeated
    STAGE_3_FIGHT_A          = 27,
    STAGE_3_FIGHT_B          = 28,
    STAGE_3_POINT_1          = 29,
    STAGE_3_POINT_2          = 30,
    STAGE_3_POINT_3          = 31,
    STAGE_3_POINT_4          = 32,
    STAGE_3_POINT_5          = 33,
    STAGE_3_POINT_DESPAWN    = 34,
    STAGE_4                  = 35,
    STAGE_4_FIGHT            = 36,

};

enum QuestDatas 
{
    QUEST_BFGC = 24904,
};

enum SpellDatas
{
    SPELL_BFGC_CONPLETE = 72349,  // completes quest requirements
    SPELL_SOLDIER_OF_BFGC = 72069, // Liam's aura
    SPELL_SHOOT         = 6660,
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