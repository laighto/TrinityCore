UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_krennan_aranas' WHERE `entry` = 38553;
UPDATE `creature_template` SET `AIName` = '', `Health_mod` = 12, `ScriptName` = 'npc_prince_liam' WHERE `entry` = 38218;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gilnean_millitia' WHERE `entry` = 38221;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gorrerot' WHERE `entry` = 38331;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lady_sylvanas' WHERE `entry` = 38469;
UPDATE `creature_template` SET `ScriptName` = 'npc_forsaken_crossbow' WHERE `entry` = 38210;

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
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('38218', '1', '0',  'The Forsaken think we\'re weak. A broken people. They think we\'ll roll over like a scared dog.', '14', 'q24904'),
('38218', '2', '0',  'How wrong they are. We will fight them in the fields until the last trench collapses and the last cannon is silenced.', '14', 'q24904'),
('38218', '3', '0',  'We will fight them on the streets until the last shot is fired. And when there\'s no more ammunition, we\'ll crush their skulls with the stones that pave our city.', '14', 'q24904'),
('38218', '4', '0',  'We will fight them in the alleys, until our knuckles are skinned and bloody and our rapiers lay on the ground shattered.', '14', 'q24904'),
('38218', '5', '0',  'And if we find ourselves surrounded and disarmed... wounded and without hope... we will lift our heads in defiance and spit in their faces.', '14', 'q24904'),
('38218', '6', '0',  'But we will... NEVER SURRENDER!!!!!', '14', 'q24904'),
('38218', '7', '0',  'FOR GILNEAS!!!', '14', 'q24904'),
--
('38218', '8', '0',  'You\'re a sight for sore eyes, Lorna. Let\'s get those cannons manned! The rest of you, lure the abominations into the open!', '14', 'q24904'),
('38218', '9', '0',  'Crowley\'s troops are up ahead! Press on!', '14', 'q24904'),
('38218', '10', '0',  'FATHER!!!', '14', 'q24904'),
--
('38218', '11', '0',  'Your time is up, Forsaken scum!', '14', 'q24904'),
('38218', '12', '1',  'Push them back!', '12', 'q24904'),
('38218', '11', '2',  'Attack!', '12', 'q24904'),
('38218', '12', '0',  'Abominations are blocking the way towards the military district! This won\'t be easy.', '12', 'q24904'),
('38218', '13', '0',  'We took back our city... we took back...', '12', 'q24904'),
('38218', '14', '0',  'We did it, father...', '12', 'q24904'),
('38218', '15', '0',  'Gilneas will prevail!', '12', 'q24904');

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