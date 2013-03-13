UPDATE `gameobject_template` SET `AIName` = '', `ScriptName` = 'dummy_book' WHERE `entry` = 177226;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 7058;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
(7058, 0, 0, 'I am absolutely certain that i want to learn Gnomish engineer.', 1, 1, 0, 0, 0, 0, NULL),
(7058, 1, 0, 'I am absolutely certain that i want to learn Goblin engineer.', 1, 1, 0, 0, 0, 0, NULL),
(7058, 2, 0, 'I wish to unlearn Gnomish engineer.', 1, 1, 0, 0, 0, 0, 'Do you really want to unlearn your engineer specialty and lose all associated recipes?'),
(7058, 3, 0, 'I wish to unlearn Goblin engineer.', 1, 1, 0, 0, 0, 0, 'Do you really want to unlearn your engineer specialty and lose all associated recipes?'),
(7058, 4, 0, 'Revert to One Talent Specialization', 0, 0, 0, 0, 0, 0, NULL),
(7058, 5, 0, 'Learn Dual Talent Specialization.', 0, 0, 0, 0, 0, 0, '1000gold');

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id` = 7058;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES
(7058, 0, 'Я абсолютно уверен, что я хочу изучить Гномскую инженерию.', NULL),
(7058, 1, 'Я абсолютно уверен, что я хочу изучить Гоблинскую инженерию.', NULL),
(7058, 2, 'Я хочу забыть Гномкую инженерию.', 'Вы действительно хотите забыть вашу специальность инженера и потерять все связанные рецепты?'),
(7058, 3, 'Я хочу забыть Гоблинскую инженерию.', 'Вы действительно хотите забыть вашу специальность инженера и потерять все связанные рецепты?'),
(7058, 4, 'Забыть двойную специализацыю.', 'Вы действительно хотите забыть двойную специализацыю?'),
(7058, 5, 'Выучить двойную специализацыю.', '1000 золота');
