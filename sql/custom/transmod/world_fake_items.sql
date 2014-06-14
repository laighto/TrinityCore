SET NAMES 'UTF8';

DELETE FROM creature_template WHERE entry = '99997'; 
INSERT INTO creature_template (entry, modelid1, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, Health_mod, Mana_mod, Armor_mod, faction_A, faction_H, npcflag, speed_walk, speed_run, scale, rank, dmg_multiplier, unit_class, unit_flags, type, type_flags, InhabitType, RegenHealth, flags_extra, ScriptName) VALUES 
('99997', '28186', "Alorien", "Transmogrify Master", 'Speak', '65500', 71, 71, 1.56, 1.56, 1.56, 35, 35, 3, 1, 1.14286, 2, 1, 1, 1, 2, 7, 138936390, 3, 1, 2, 'npc_transmogrify'); 
DELETE FROM `locales_creature` WHERE `entry`='99997';
INSERT INTO `locales_creature` (`entry`, `name_loc8`, `subname_loc8`) VALUES ('99997', 'Алориен', 'Мастер трансмогрификации');

REPLACE INTO `gossip_menu` VALUES (65500, 65500);

REPLACE INTO npc_text (ID, text0_0, em0_1) VALUES
(65500, 'Put in the first slot of bag item, that you want to transmogrify. In the second slot, put item with perfect display.', 0);
DELETE FROM  `locales_npc_text` WHERE  `entry`='65500';
INSERT INTO `locales_npc_text` VALUES ('65500', null, null, null, null, null, null, null, 'Положите в первый слот рюкзака предмет, который вы хотите исказить. Во второй слот  предмет, модель которого будет использована для трансмогрификации.', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null);

DELETE FROM `trinity_string` WHERE `entry` IN (999970, 999971, 999972, 999973, 999974, 999975, 999976, 999976, 999977, 999978, 999979, 999980);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc8`) VALUES
(999970, 'Put items in the first and second slot of main bag!', 'Поставьте предметы в первый и второй слот основной сумки!'),
(999971, 'It costs %u gold!', 'Это стоит %u золота!'),
(999972, 'Cant find item!', 'Невозможно найти предмет!'),
(999973, 'Item has wrong quality!', 'Предметы запрещенного качества!'),
(999974, 'Items are from different slot!', 'Предметы из разных слотов!'),
(999975, 'Items require different player class!', 'Предметы для разных ировых классов!'),
(999976, 'Items require different race!', 'Предметы для разных рас!'),
(999977, 'Put item in the first slot!', 'Поставьте предмет в первый слот!'),
(999978, 'Items has different subclass material!', 'Предметы сделаны из разных материалов!'),
(999979, 'Player can\'t equip that item!', 'Игрок не может использовать этот предмет'),
(999980, 'Items has different class!', 'Разный класс предметов!');

DELETE FROM  `gossip_menu_option` WHERE `menu_id`=65500;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(65500, 0, 0, 'Change Name', 965500, 1, 1, 0, 0, 0, 0, 'Expensive!', 0),
(65500, 1, 0, 'Change Faction', 965501, 1, 1, 0, 0, 0, 0, 'Expensive!', 0);

DELETE FROM  `locales_gossip_menu_option` WHERE `menu_id`=65500;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES 
(65500, 0, 'Трансформировать предмет',  ''),
(65500, 1, 'Сделать предмет обычным',  '');

DELETE FROM `broadcast_text` WHERE `ID` IN (965500, 965501);
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('965500', 'Transmorgrify'),
('965501', 'Make item clean.');

DELETE FROM `locales_broadcast_text` WHERE `ID` IN (965500, 965501);
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('965500', 'Трансформировать предмет'),
('965501', 'Сделать предмет обычным');



