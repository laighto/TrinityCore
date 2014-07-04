UPDATE `item_template` SET `ScriptName` = 'orb_of_the_crawler' WHERE `entry` = 35237;
UPDATE `creature_template` SET `ScriptName` = 'npc_briatha' WHERE `entry` = 25949;
UPDATE `creature_template` SET `ScriptName` = 'npc_heretic_emisar' WHERE `entry` = 25951;

DELETE FROM `creature_text` WHERE `entry` = '25949';
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`, `probability`, `comment`, `BroadcastTextID`) VALUES 
('25949', '0', 'These stones should be the last of them. Our coordination with Neptulon\'s forces will be impeccable.', '12', '100', 'Ice Caller Briatha', '0'),
('25949', '1', 'And your own preparations? Will the Frost Lord have a path to the portal?', '12', '100', 'Ice Caller Briatha', '0'),
('25949', '2', 'The ritual in coilfang will bring Ahune through once he is fully prepared, and the resulting clash between Firelord and Frostlord will rend the foundations of this world. Our ultimate goals are in reach at last...', '12', '100', 'Ice Caller Briatha', '0');
DELETE FROM `creature_text` WHERE `entry` = '25951';
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`, `probability`, `comment`, `BroadcastTextID`) VALUES 
('25951', '0', 'Yess. The Tidehunter will be pleased at this development. The Firelord\'s hold will weaken.', '12', '100', 'Ice Caller Briatha', '0'),
('25951', '1', 'Skar\'this has informed us well. We have worked our way into the slave pens and await your cryomancerss.', '12', '100', 'Ice Caller Briatha', '0');
