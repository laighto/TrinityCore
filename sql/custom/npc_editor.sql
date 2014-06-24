DELETE FROM  `gossip_menu_option` WHERE `menu_id`=65530;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(65530, 0, 0, 'Change Name', 965530, 1, 1, 0, 0, 0, 1000000, 'Expensive!', 0),
(65530, 1, 0, 'Change Faction', 965531, 1, 1, 0, 0, 0, 60000000, 'Expensive!', 0),
(65530, 2, 0, 'Change Race', 965532, 1, 1, 0, 0, 0, 50000000, 'Expensive!', 0);

DELETE FROM  `locales_gossip_menu_option` WHERE `menu_id`=65530;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES 
(65530, 0, 'Сменить имя',  'Дорого!'),
(65530, 1, 'Сменить фракцию',  'Дорого!'),
(65530, 2, 'Сменить расу',  'Дорого!');

DELETE FROM `broadcast_text` WHERE `ID` IN (965530, 965531, 965532);
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('965530', 'Change Name.'),
('965531', 'Change Faction.'),
('965532', 'Change Race.');

DELETE FROM `locales_broadcast_text` WHERE `ID` IN (965530, 965531, 965532);
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('965530', 'Сменить имя.'),
('965531', 'Сменить фракцию.'),
('965532', 'Сменить расу.');

-- Reksar
DELETE FROM `smart_scripts` WHERE (`entryorguid`=99999 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(99999, 0, 0, 0, 62, 0, 100, 0, 65535, 0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -13229.8, 225.33, 32.596, 1.03, "Teleport to Gurubashi Arena?"),
(99999, 0, 2, 0, 62, 0, 100, 0, 65535, 1, 0, 0, 62, 571, 0, 0, 0, 0, 0, 7, 0, 0, 0, 5804.15, 624.771, 647.767, 1.64, "Teleport to Dalaran?");

DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=65535;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 65535, 1, 0, 0, 27, 0, 60, 3, 0, 0, 0, 0, '', 'Teleport to Dalaran'),
(15, 65535, 0, 0, 0, 27, 0, 20, 3, 0, 0, 0, 0, '', 'Teleport to Gurubashi arena'),
(15, 65535, 4, 0, 0, 27, 0, 40, 3, 0, 0, 0, 0, '', 'Learn Dual Spec switching');

DELETE FROM `gossip_menu_option` WHERE `menu_id`='65535';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(65535, 0, 2, 'Gurubashi Arena Teleport', 655350, 1, 1, 0, 0, 0, 0, 'Teleport to Gurubashi Arena?', 0),
(65535, 1, 2, 'Teleport to Dalaran', 655351, 1, 1, 0, 0, 0, 0, 'Teleport to Dalaran?', 0),
(65535, 2, 6, 'AUCTION', 655352, 13, 2097152, 0, 0, 0, 0, NULL, 0),
(65535, 3, 1, 'I want to browse your goods.', 655353, 3, 128, 0, 0, 0, 0, NULL, 0),
(65535, 4, 3, 'Training Dual Talent switch.', 655354, 5, 16, 0, 0, 0, 0, NULL, 0),
(65535, 5, 0, 'Stable Master', 655355, 14, 4194304, 0, 0, 0, 0, NULL, 0),
(65535, 6, 0, 'Redeem a Code', 655356, 1, 1, 0, 0, 1, 0, NULL, 0);

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id`='65535';
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc1`, `option_text_loc2`, `option_text_loc3`, `option_text_loc4`, `option_text_loc5`, `option_text_loc6`, `option_text_loc7`, `option_text_loc8`, `box_text_loc1`, `box_text_loc2`, `box_text_loc3`, `box_text_loc4`, `box_text_loc5`, `box_text_loc6`, `box_text_loc7`, `box_text_loc8`) VALUES
(65535, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ТП на Гурубаши Арену', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Бесплатно. Уверен?'),
(65535, 1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'ТП в Даларан', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Бесплатно. Уверен?'),
(65535, 2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'АУКЦИОН', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(65535, 3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Покажи мне свои товары.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(65535, 4, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Обучение переключению дуалспека', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(65535, 5, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Смотритель стойл', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Вы должны слезть с маунта! Уверены?'),
(65535, 6, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Погасить код', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

DELETE FROM `broadcast_text` WHERE `ID` IN (655350, 655351, 655352, 655353, 655354, 655355);
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('655350', 'Gurubashi Arena Teleport.'),
('655351', 'Teleport to Dalaran.'),
('655352', 'AUCTION.'),
('655353', 'I want to browse your goods.'),
('655354', 'Training Dual Talent switch.'),
('655355', 'Stable Master.'),
('655356', 'Redeem a Code');

DELETE FROM `locales_broadcast_text` WHERE `ID` IN (655350, 655351, 655352, 655353, 655354, 655355);
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('655350', 'ТП на Гурубаши Арену.'),
('655351', 'ТП в Даларан'),
('655352', 'Аукцион.'),
('655353', 'Покажи мне свои товары.'),
('655354', 'Обучение переключению дуалспека'),
('655355', 'Смотритель стойл.'),
('655356', 'Погасить код.');

UPDATE creature_template SET ScriptNAme='code_manager' WHERE entry=99999;
