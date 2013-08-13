DELETE FROM `gossip_menu_option` WHERE `menu_id`=11189;
INSERT INTO `gossip_menu_option` VALUES 
(11189, 0, 0, 'A ride to Razor Hill?', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id`=11189;
INSERT INTO `locales_gossip_menu_option`(`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES 
('11189', '0', 'Подвезешь до Колючего Холма?', NULL);

UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_raider_jhash' WHERE `entry` = 10676;
UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 1.14286, `AIName` = 'SmartAI' WHERE `entry` = 39239;
UPDATE `creature_template` SET `speed_walk` = 1, `speed_run` = 1.14286, `AIName` = 'SmartAI' WHERE `entry` = 10682;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39239 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39239, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 39239, 0, 25171, 120000, 0, 1, 0, 0, 0, 0, 0, 0, 0, "q25171 - go to razor hill"),
(39239, 0, 1, 0, 58, 0, 100, 0, 50, 39239, 0, 0, 41, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "q25171 - despawn on end");

DELETE FROM `smart_scripts` WHERE (`entryorguid`=10682 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(10682, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 1, 39239, 0, 25171, 300000, 0, 1, 0, 0, 0, 0, 0, 0, 0, "q25171 - go to razor hill"),
(10682, 0, 1, 0, 58, 0, 100, 0, 49, 39239, 0, 0, 41, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "q25171 - despawn on end");

DELETE FROM waypoints WHERE entry=39239,
INSERT INTO `waypoints` VALUES 
(39239, 1, -815.424, -4884.22, 19.1523, ''),
(39239, 2, -802.668, -4864.17, 19.4394, ''),
(39239, 3, -775.752, -4842.89, 18.2601, ''),
(39239, 4, -749.337, -4820.6, 20.4928, ''),
(39239, 5, -728.173, -4799.34, 27.2705, ''),
(39239, 6, -719.707, -4790.84, 30.0686, ''),
(39239, 7, -705.715, -4778.32, 33.392, ''),
(39239, 8, -685.85, -4768.43, 33.6957, ''),
(39239, 9, -665.358, -4746.46, 33.6768, ''),
(39239, 10, -641.842, -4728.85, 33.6768, ''),
(39239, 11, -627.456, -4724.15, 33.7574, ''),
(39239, 12, -613.571, -4725.08, 35.0456, ''),
(39239, 13, -595.745, -4727.58, 34.5489, ''),
(39239, 14, -571.976, -4730.91, 33.7125, ''),
(39239, 15, -546.49, -4740.93, 33.1522, ''),
(39239, 16, -524.568, -4750.7, 33.0258, ''),
(39239, 17, -502.645, -4760.46, 32.4313, ''),
(39239, 18, -481.369, -4769.94, 32.0578, ''),
(39239, 19, -469.546, -4771.99, 32.4101, ''),
(39239, 20, -446.714, -4777.79, 32.4421, ''),
(39239, 21, -429.724, -4783.74, 32.3735, ''),
(39239, 22, -399.731, -4798.68, 32.5283, ''),
(39239, 23, -377.271, -4807.52, 32.4649, ''),
(39239, 24, -362.733, -4810.24, 32.4343, ''),
(39239, 25, -338.733, -4810.14, 31.376, ''),
(39239, 26, -311.806, -4805.96, 30.2044, ''),
(39239, 27, -288.421, -4800.56, 29.3866, ''),
(39239, 28, -241.652, -4789.76, 25.8458, ''),
(39239, 29, -212.421, -4783.01, 24.3593, ''),
(39239, 30, -185.775, -4773.06, 23.5647, ''),
(39239, 31, -157.476, -4763.1, 23.0989, ''),
(39239, 32, -126.255, -4755.13, 22.3136, ''),
(39239, 33, -90.8134, -4748.81, 21.2681, ''),
(39239, 34, -62.8192, -4747.71, 20.8005, ''),
(39239, 35, -26.895, -4745.38, 21.3369, ''),
(39239, 36, -8.93291, -4744.21, 21.7506, ''),
(39239, 37, 9.02917, -4743.04, 21.9355, ''),
(39239, 38, 32.9786, -4741.48, 21.5791, ''),
(39239, 39, 57.8952, -4743.06, 19.7756, ''),
(39239, 40, 83.5882, -4743.55, 17.6865, ''),
(39239, 41, 95.5624, -4744.33, 16.9484, ''),
(39239, 42, 120.512, -4756.07, 14.117, ''),
(39239, 43, 130.697, -4762.42, 13.0023, ''),
(39239, 44, 147.008, -4767.21, 12.0988, ''),
(39239, 45, 158.301, -4763.15, 11.8968, ''),
(39239, 46, 180.884, -4755.04, 11.5156, ''),
(39239, 47, 197.823, -4748.95, 10.8997, ''),
(39239, 48, 230.641, -4740.67, 10.1041, ''),
(39239, 49, 238.972, -4739.61, 10.1041, ''),
(39239, 50, 270.845, -4743.21, 9.83511, '');

-- DELETE FROM `smart_scripts` WHERE(`entryorguid`=10676 AND `source_type`=0);
-- INSERT INTO `smart_scripts`(`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
-- (10676, 0, 0, 1, 62, 0, 100, 0, 11189, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "q25171 - close gossip"),
-- (10676, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 73678, 3, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "q25171 - mount on wolf"),
-- (10676, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 10682, 1, 120000, 0, 0, 0, 8, 0, 0, 0, -825.47, -4900.59, 19.63, 1.086, "q25171 - summon Raider Kerr");
-- DELETE FROM conditions WHERE SourceTypeOrReferenceId='15' AND SourceGroup='11189';
-- INSERT INTO `conditions`(`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `NegativeCondition`, `Comment`) VALUES 
-- ('15', '11189', '0', '8', '25171', '1', 'Quest not rewarded 25171');