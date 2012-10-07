UPDATE `gameobject_template` SET `AIName` = '', `ScriptName` = 'dummy_book' WHERE `entry` = 177226;

DELETE FROM `trinity_string` WHERE `entry` IN (999950, 999951, 999952, 999953);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(999953, 'Learn Dual Talent Specialization. (1000gold)', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Купить двойную специализацию талантов. (1000золота)'),
(999952, 'Revert to One Talent Specialization', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Забыть двойную специализацыю'),
(999951, 'Unlearn Gnomish Engineer (150 gold)', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Забыть Гномскую инженерию (150 золота)'),
(999950, 'Unlearn Goblin Engineer (150 gold)', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Забыть Гоблинскую инженерию (150 золота)');
