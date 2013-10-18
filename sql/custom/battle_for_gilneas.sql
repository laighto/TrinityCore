UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_krennan_aranas' WHERE `entry` = 38553;
UPDATE `creature_template` SET `AIName` = '', `Health_mod` = 12, `ScriptName` = 'npc_prince_liam' WHERE `entry` = 38218;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gorrerot' WHERE `entry` = 38331;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lady_sylvanas' WHERE `entry` = 38469;
UPDATE `creature_template` SET `ScriptName` = 'npc_forsaken_crossbow' WHERE `entry` = 38210;
UPDATE `creature_template` SET `ScriptName` = 'npc_vile_abomination' WHERE `entry` = 38420;
UPDATE `creature_template` SET `ScriptName` = 'npc_emberstone_canon_villager' WHERE `entry` = 38424;
UPDATE `creature_template` SET `ScriptName` = 'npc_emberstone_canon_villager' WHERE `entry` = 38425;
DELETE FROM `creature` WHERE `id`=38221;
UPDATE `creature_template` SET `dmg_multiplier` = 3, `Health_mod` = 2, `ScriptName` = 'npc_gilnean_millitia' WHERE `entry` = 38221;
UPDATE `creature_template` SET `ScriptName` = 'npc_king_genn_greymane' WHERE `entry` = 38470;

DELETE FROM `gossip_menu_option` WHERE `menu_id`=11061;
INSERT INTO `gossip_menu_option` VALUES 
(11061, 0, 0, 'Let us take back our city!', 1, 1, 0, 0, 0, 0, NULL),
(11061, 1, 0, 'I want to join battle!', 1, 1, 0, 0, 0, 0, NULL);
DELETE FROM `locales_gossip_menu_option` WHERE `menu_id`=11061;
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc8`, `box_text_loc8`) VALUES 
('11061', '0', 'Надо отвоевать наш город!', NULL),
('11061', '1', 'Я хочу присоединится к битве!', NULL);

DELETE FROM creature_text WHERE entry='38553';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('38553', '0', '0',  'BATTLE BEGIN TEST!', '12', 'q24904');


DELETE FROM creature_text WHERE entry='38218';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `sound`, `comment`) VALUES 
('38218', '1', '0',  'The Forsaken think we\'re weak. A broken people. They think we\'ll roll over like a scared dog.', '14', '19623', 'q24904'),
('38218', '2', '0',  'How wrong they are. We will fight them in the fields until the last trench collapses and the last cannon is silenced.', '14', '19624', 'q24904'),
('38218', '3', '0',  'We will fight them on the streets until the last shot is fired. And when there\'s no more ammunition, we\'ll crush their skulls with the stones that pave our city.', '14', '19625', 'q24904'),
('38218', '4', '0',  'We will fight them in the alleys, until our knuckles are skinned and bloody and our rapiers lay on the ground shattered.', '14', '19626', 'q24904'),
('38218', '5', '0',  'And if we find ourselves surrounded and disarmed... wounded and without hope... we will lift our heads in defiance and spit in their faces.', '14', '19627', 'q24904'),
('38218', '6', '0',  'But we will... NEVER SURRENDER!!!!!', '14', '19628', 'q24904'),
('38218', '7', '0',  'FOR GILNEAS!!!', '14', '', 'q24904'),
--
('38218', '8', '0',  'You\'re a sight for sore eyes, Lorna. Let\'s get those cannons manned! The rest of you, lure the abominations into the open!', '14', '', 'q24904'),
('38218', '9', '0',  'Crowley\'s troops are up ahead! Press on!', '14', '', 'q24904'),
('38218', '10', '0',  'FATHER!!!', '14', '', 'q24904'),
--
('38218', '11', '0',  'Your time is up, Forsaken scum!', '12', '', 'q24904'),
('38218', '11', '1',  'Push them back!', '12', '', 'q24904'),
('38218', '11', '2',  'Attack!', '12', '', 'q24904'),
('38218', '12', '0',  'Abominations are blocking the way towards the military district! This won\'t be easy.', '12', '', 'q24904'),
('38218', '13', '0',  'We took back our city... we took back...', '12', '', 'q24904'),
('38218', '14', '0',  'We did it, father...', '12', '', 'q24904'),
('38218', '15', '0',  'Gilneas will prevail!', '12', '', 'q24904');

DELETE FROM locales_creature_text WHERE entry='38218';
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
('38218', '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Отрекшиеся думают, что мы ослабли, опустили руки. Они думают, что мы убежим, поджав хвост.'),
('38218', '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Как же они ошибаются! Мы будем стоять до конца, будем биться, пока у нас есть пушки и солдаты в окопах.'),
('38218', '3', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Мы будем сражаться на улицах до последнего патрона. А когда нам нечем будет стрелять, мы будем разбивать их черепа булыжниками с мостовой.'),
('38218', '4', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Мы будем сражаться в подворотнях, пока с наших костяшек не сойдет кожа, а рапиры не упадут на землю сломанными.'),
('38218', '5', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'А если мы будем зажаты в угол, лишимся сил, оружия и надежды... Мы поднимем голову с презрением и плюнем им в лицо.'),
('38218', '6', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Но мы... НИКОГДА НЕ СДАДИМСЯ!'),
('38218', '7', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'ЗА ГИЛНЕАС!!!'),
--
('38218', '8', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Лорна, как я рад тебя видеть! Солдаты – по пушкам! Остальные выманивают поганищ на открытое пространство!'),
('38218', '9', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Впереди войска Краули! Поднажмем!'),
('38218', '10', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'ОТЕЦ!!!'),
--
('38218', '11', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Прошло ваше время, Отрекшиеся мрази!'),
('38218', '11', '1', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Тесни их!'),
('38218', '11', '2', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Атакуйте!'),
('38218', '12', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Поганища перекрывают путь к Военному кварталу! Пробиться будет нелегко.'),
('38218', '13', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Мы вернули свой город... Мы вернули...'),
('38218', '14', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Отец, мы победили...'),
('38218', '15', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'За Гилнеас!');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 38377;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=38377 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(38377, 0, 0, 0, 27, 0, 100, 0, 1000, 1000, 0, 0, 11, 72839, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Damaged catapult");

DELETE FROM waypoint_data WHERE id=99999;
INSERT INTO `waypoint_data` VALUES 
(99999, 3, -1603.74, 1314.05, 18.2847, 0, 0, 1, 0, 100, 0),
(99999, 2, -1588.6, 1316.2, 27.6428, 0, 0, 1, 0, 100, 0),
(99999, 1, -1575.36, 1317.83, 35.6656, 0, 0, 1, 0, 100, 0);