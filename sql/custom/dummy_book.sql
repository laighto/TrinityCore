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
