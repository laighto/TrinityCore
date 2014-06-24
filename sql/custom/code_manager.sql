UPDATE `creature_template` SET `rank` = 2, `unit_class` = 2, `npcflag` = 1, `gossip_menu_id`='65507', `ScriptName`='code_manager' WHERE `entry`=100107;

DELETE FROM `gossip_menu_option` WHERE `menu_id`='65507';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(65507, 0, 0, 'Redeem a Code', 655070, 1, 1, 0, 0, 1, 0, NULL, 0);

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id`='65507';
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc1`, `option_text_loc2`, `option_text_loc3`, `option_text_loc4`, `option_text_loc5`, `option_text_loc6`, `option_text_loc7`, `option_text_loc8`, `box_text_loc1`, `box_text_loc2`, `box_text_loc3`, `box_text_loc4`, `box_text_loc5`, `box_text_loc6`, `box_text_loc7`, `box_text_loc8`) VALUES
(65507, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Погасить код', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

DELETE FROM `broadcast_text` WHERE `ID` = 655070;
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('655070', 'Redeem a Secret Code');

DELETE FROM `locales_broadcast_text` WHERE `ID` = 655070;
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('655070', 'Активировать секретный код.');

DELETE FROM `creature_text` WHERE `entry` = 100107;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `sound`, `comment`, `BroadcastTextID`) VALUES 
('100107', '0', '0', 'ERROR: Invalid code. Check your data.', '14', '0', 'code manager', '655071'),
('100107', '1', '0', 'ERROR: The code has already been activated.', '14', '0', 'code manager', '655072'),
('100107', '2', '0', 'Congratulations. Code has been activated successfully.', '14', '0', 'code manager', '655073');
DELETE FROM `broadcast_text` WHERE `ID` IN (655071,655072,655073);
INSERT INTO `broadcast_text` (`ID`, `MaleText`) VALUES 
('655071', 'ERROR: Invalid code. Check your data.'),
('655072', 'ERROR: The code has already been activated.'),
('655073', 'Congratulations. Code has been activated successfully.');
DELETE FROM `locales_broadcast_text` WHERE `ID` IN (655071,655072,655073);
INSERT INTO `locales_broadcast_text` (`ID`, `MaleText_loc8`) VALUES 
('655071', 'ОШИБКА: Неверный код. Проверьте правильность ввода.'),
('655072', 'ОШИБКА: Код уже был активирован.'),
('655073', 'Поздравляем. Код успешно активирован.');

DROP TABLE IF EXISTS `code_manager`;
CREATE TABLE `code_manager` (
  `code` tinytext NOT NULL COMMENT 'UNIQUE GENERATED CODE',
  `active` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `actionid` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'ID of action in script',
  `data0` mediumint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'data field for action',
  `data1` mediumint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'data field for action',
  `data2` mediumint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'data field for action',
  `data3` mediumint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'data field for action',
  `comment` tinytext COMMENT 'Description of Action, that code activates',
  `charguid` int(10) unsigned DEFAULT NULL COMMENT 'character id. from which was code activated',
  `characcount` int(10) unsigned DEFAULT NULL COMMENT 'Account id. from which was code activated',
  PRIMARY KEY (`code`(20))
) ENGINE=InnoDB DEFAULT CHARSET=utf8;