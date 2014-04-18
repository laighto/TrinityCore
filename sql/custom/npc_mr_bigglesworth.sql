UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_mr_bigglesworth' WHERE `entry` = 16998;

# TEMP HACK 
# placing hiden trigger with name "Kel'Thuzad" near  Mr.bigglesworth spawn point
# to be able hear voice ant text after cat death
DELETE FROM `creature_template` WHERE (`entry`=99980);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(99980, 0, 0, 0, 0, 0, 169, 0, 0, 0, 'Kel\'Thuzad', '', '', 0, 1, 1, 2, 35, 35, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1000, 1000, 2, 32770, 2048, 0, 0, 0, 0, 0, 1, 1, 130, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 15595);
DELETE FROM `locales_creature` WHERE `entry`=99980;
INSERT INTO `locales_creature` (`entry`, `name_loc8`) VALUES 
('99980', 'Кел\'Тузад');
DELETE FROM `creature_text` WHERE `entry`='99980';
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`, `probability`, `sound`, `comment`) VALUES 
('99980', '5', 'No!!! A curse upon you, interlopers! The armies of the Lich King will hunt you down. You will not escape your fate...', '14', '100', '14484', 'kelthuzad SAY_CAT_DIED');
DELETE FROM `locales_creature_text` WHERE `entry`='99980';
INSERT INTO `locales_creature_text` (`entry`, `groupid`, `text_loc8`) VALUES 
('99980', '5', 'Нет!! Будьте вы прокляты, незваные гости! Армии Короля-лича поймают вас. Вы не сбежите от своей погибели...');
DELETE FROM `creature` WHERE `id`=99980;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(99980, 533, 3, 1, 0, 0, 3004.91, -3434.45, 384.38, 6.19645, 300, 0, 0, 12600, 0, 0, 0, 0, 0);

