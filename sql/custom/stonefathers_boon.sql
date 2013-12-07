UPDATE `creature_template` SET `ScriptName`='npc_stonefathers_banner' WHERE `entry`=43163;

DELETE FROM `creature_template_addon` WHERE (`entry`=43163);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(43163, '', 0, 0, 0, 0, 80664);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 80670;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (80670, 80658, 0, 'Quest: Stonefathers Boon Spell (Deepholm)');