UPDATE `creature_template` SET `ScriptName` = 'npc_eye_of_acherus' WHERE `entry` = '28511';

DELETE FROM creature_text WHERE entry='28511';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('28511', '1', '0',  'The Eye of Acherus launches towards its destination.', '12', 'q12641 - text1' ),
('28511', '2', '0',  'The Eye of Acherus is in your control.', '12', 'q12641 - text2');

DELETE FROM locales_creature_text WHERE entry='28511';
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
('28511', '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Око Акеруса отправляется к месту назначения.'),
('28511', '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Око Акеруса под вашим управлением.');
