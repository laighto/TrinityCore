UPDATE `gameobject_template` SET `AIName` = '', `ScriptName` = 'dummy_book' WHERE `entry` = 177226;

DELETE FROM `trinity_string` WHERE `entry` IN (999950, 999951, 999952, 999953, 999954, 999955);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(999950, 'I am absolutely certain that i want to learn Gnomish engineer.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Я абсолютно уверен, что я хочу изучить Гномскую инженерию.'),
(999951, 'I am absolutely certain that i want to learn Goblin engineer.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Я абсолютно уверен, что я хочу изучить Гоблинскую инженерию.'),
(999952, 'I wish to unlearn Gnomish engineer', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Я хочу забыть Гномкую инженерию.'),
(999953, 'I wish to unlearn Goblin engineer.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Я хочу забыть Гоблинскую инженерию.'),
(999954, 'Revert to One Talent Specialization', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Забыть двойную специализацыю.'),
(999955, 'Learn Dual Talent Specialization.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Выучить двойную специализацыю.');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 7058;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
(7058, 0, 0, 'I am absolutely certain that i want to learn Gnomish engineer.', 1, 1, 0, 0, 0, 0, NULL),
(7058, 1, 0, 'I am absolutely certain that i want to learn Goblin engineer.', 1, 1, 0, 0, 0, 0, NULL),
(7058, 2, 0, 'I wish to unlearn Gnomish engineer.', 1, 1, 0, 0, 0, 0, 'Do you really want to unlearn your engineer specialty and lose all associated recipes?'),
(7058, 3, 0, 'I wish to unlearn Goblin engineer.', 1, 1, 0, 0, 0, 0, 'Do you really want to unlearn your engineer specialty and lose all associated recipes?'),
(7058, 4, 0, 'Revert to One Talent Specialization', 1, 1, 0, 0, 0, 0, NULL),
(7058, 5, 0, 'Learn Dual Talent Specialization.', 1, 1, 0, 0, 0, 0, '1000gold');

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id` = 7058;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES
(7058, 0, 'Я абсолютно уверен, что я хочу изучить Гномскую инженерию.', NULL),
(7058, 1, 'Я абсолютно уверен, что я хочу изучить Гоблинскую инженерию.', NULL),
(7058, 2, 'Я хочу забыть Гномкую инженерию.', 'Вы действительно хотите забыть вашу специальность инженера и потерять все связанные рецепты?'),
(7058, 3, 'Я хочу забыть Гоблинскую инженерию.', 'Вы действительно хотите забыть вашу специальность инженера и потерять все связанные рецепты?'),
(7058, 4, 'Забыть двойную специализацыю.', 'Вы действительно хотите забыть двойную специализацыю?'),
(7058, 5, 'Выучить двойную специализацыю.', '1000 золота');

DELETE FROM `broadcast_text` WHERE `ID` IN (970580, 970581, 970582, 970583, 970584, 970585);
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('970580', 'I am absolutely certain that i want to learn Gnomish engineer.'),
('970581', 'I am absolutely certain that i want to learn Goblin engineer.'),
('970582', 'I wish to unlearn Gnomish engineer.'),
('970583', 'I wish to unlearn Goblin engineer.'),
('970584', 'Revert to One Talent Specialization.'),
('970585', 'Learn Dual Talent Specialization.');

DELETE FROM `locales_broadcast_text` WHERE `ID` IN (970580, 970581, 970582, 970583, 970584, 970585);
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('970580', 'Я абсолютно уверен, что я хочу изучить Гномскую инженерию.'),
('970581', 'Я абсолютно уверен, что я хочу изучить Гоблинскую инженерию.'),
('970582', 'Я хочу забыть Гномкую инженерию.'),
('970583', 'Я хочу забыть Гоблинскую инженерию.'),
('970584', 'Забыть двойную специализацыю.'),
('970585', 'Выучить двойную специализацыю.');

UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970580' WHERE `menu_id`='7058' AND `id`='0';
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970581' WHERE `menu_id`='7058' AND `id`='1';
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970582' WHERE `menu_id`='7058' AND `id`='2';
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970583' WHERE `menu_id`='7058' AND `id`='3';
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970584' WHERE `menu_id`='7058' AND `id`='4';
UPDATE `gossip_menu_option` SET `OptionBroadcastTextID`='970585' WHERE `menu_id`='7058' AND `id`='5';