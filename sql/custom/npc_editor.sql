DELETE FROM  `gossip_menu_option` WHERE `menu_id`=65530;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(65530, 0, 0, 'Change Name', 0, 1, 1, 0, 0, 0, 1000000, 'Expensive!', 0),
(65530, 1, 0, 'Change Faction', 0, 1, 1, 0, 0, 0, 60000000, 'Expensive!', 0),
(65530, 2, 0, 'Change Race', 0, 1, 1, 0, 0, 0, 50000000, 'Expensive!', 0);

DELETE FROM  `locales_gossip_menu_option` WHERE `menu_id`=65530;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES 
(65530, 0, 'Сменить имя',  'Дорого!'),
(65530, 1, 'Сменить фракцию',  'Дорого!'),
(65530, 2, 'Сменить расу',  'Дорого!');