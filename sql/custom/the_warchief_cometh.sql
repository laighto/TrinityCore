UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_sylvanas' WHERE `entry` = 44365;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_warchief' WHERE `entry` = 44629;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_cromush' WHERE `entry` = 44640;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_mortuus' WHERE `entry` = 44615;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_agatha' WHERE `entry` = 44608;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_fallen_human' WHERE `entry` = 44593;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_fallen_human' WHERE `entry` = 44592;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_w_elite' WHERE `entry` = 44636;

DELETE FROM creature_text WHERE entry='44365';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('44365', '0', '0',  'Where is that ogre-headed buffoon?', '12', 'q26965 - text1' ),
('44365', '1', '0',  'Ah, speak of the devil...', '12', 'q26965 - text2'),
('44365', '2', '0',  'Warchief, so glad you could make it.', '12', 'q26965 - textevent 5'),
('44365', '3', '0',  'With the death of the Lich King, many of the more intelligent Scourge became... unemployed. Those \'fiends,\' as you so delicately put it, are called val\'kyr. They are under my command now...', '12', 'q26965 - textevent 6'),
('44365', '4', '0',  '...and they are part of the reason that I asked to see you.', '12', 'q26965 - textevent 7'),
('44365', '5', '0',  'Very well, Warchief. I have solved the plight of the Forsaken!', '12', 'q26965 - textevent 9'),
('44365', '6', '0',  'As a race, we Forsaken are unable to procreate.', '12', 'q26965 - textevent 10'),
('44365', '7', '0',  'With the aid of the val\'kyr, we are now able to take the corpses of the fallen and create new Forsaken.', '12', 'q26965 - textevent 11'),
('44365', '8', '0',  'Agatha, show the Warchief!', '12', 'q26965 - textevent 12'),
('44365', '9', '0',  'Warchief, without these new Forsaken my people would die out... Our hold upon Gilneas and northern Lordaeron would crumble.', '12', 'q26965 - textevent 15'),
('44365', '10', '0',  'Isn\'t it obvious, Warchief? I serve the Horde.', '12', 'q26965 - textevent 18');

DELETE FROM locales_creature_text WHERE entry='44365';
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
('44365', '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Где этот шут с мозгами огра?'),
('44365', '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'А, легок на помине!'),
('44365', '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Вождь, я так рада, что ты смог прибыть.'),
('44365', '3', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Многие воины Плети, которым удалось сохранить рассудок, после смерти Короля-лича остались не у дел. Эти "твари", как ты их назвал, зовутся валь\'кирами. Теперь они подвластны мне...'),
('44365', '4', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, '..И позвала я тебя в том числе из-за них.'),
('44365', '5', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Да, Вождь. Так вот, я сняла с Отрекшихся их проклятие!'),
('44365', '6', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Мы, Отрекшиеся, не можем иметь потомства.'),
('44365', '7', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Но с помощью валь\'кир мы научились оживлять тела погибших и превращать их в Отрекшихся.'),
('44365', '8', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Агата, покажи Вождю!'),
('44365', '9', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Вождь, без новых Отрекшихся мой народ бы вымер... Мы потеряли бы влияние в Гилнеасе и северном Лордероне.'),
('44365', '10', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Как это чем, Вождь? Я служу Орде.');

DELETE FROM creature_text WHERE entry='44629';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('44629', '0', '0',  'This better be important, Sylvanas. You know how I detest this place and its foul stench. Why have you called for me?', '12', 'q26965 - text3' ),
('44629', '1', '0',  'And more importantly, what are those Scourge fiends doing here?', '12', 'q26965 - text4'),
('44629', '2', '0',  'Get on with it, Sylvanas.', '12', 'q26965 - textevent 8'),
('44629', '3', '0',  'ABBERATION!', '12', 'q26965 - textevent 13'),
('44629', '4', '0',  'What you have done here, Sylvanas... it goes against the laws of nature. Disgusting is the only word I have to describe it.', '12', 'q26965 - textevent 14'),
('44629', '5', '0',  'Have you given any thought to what this means, Sylvanas?', '12', 'q26965 - textevent 16'),
('44629', '6', '0',  'What difference is there between you and the Lich King now?', '12', 'q26965 - textevent 17'),
('44629', '7', '0',  'Watch your clever mouth, bitch.', '12', 'q26965 - textevent 19'),
('44629', '8', '0',  'Cromush, you stay behind and make sure the Banshee Queen is well "guarded." I will be expecting a full report when next we meet.', '12', 'q26965 - textevent 20'),
('44629', '9', '0',  'Remember, Sylvanas, eventually we all have to stand before our maker and face judgment. Your day may come sooner than others\'....', '12', 'q26965 - textevent 22');

DELETE FROM locales_creature_text WHERE entry='44629';
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
('44629', '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Надеюсь, у тебя что-то важное. Ты знаешь, что я не выношу это место и его проклятую вонь. Зачем ты позвала меня?'),
('44629', '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'А еще мне интересно, что тут делают эти твари из Плети!'),
('44629', '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Продолжай, Сильвана.'),
('44629', '3', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'НЕМЫСЛИМО'),
('44629', '4', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Что ты здесь устроила, Сильвана... Это противоречит всем законам природы! Этому... нет названия!'),
('44629', '5', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Ты хоть понимаешь, что это значит, Сильвана?'),
('44629', '6', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Чем ты теперь отличаешься от Короля-лича?'),
('44629', '7', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Попридержи свой язык, дохлятина!'),
('44629', '8', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Кромуш, останься тут и следи, чтобы королеву банши хорошо охраняли. В следующий раз я жду полного отчета.'),
('44629', '9', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Помни, Сильвана, что в конце концов мы все предстанем перед Творцом и будем держать ответ за свои дела. Может быть, твой день не так далек...');

DELETE FROM creature_text WHERE entry='44640';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `comment`) VALUES 
('44640', '0', '0',  'as you command Warchief', '12', 'q26965 - textevent 21');

DELETE FROM locales_creature_text WHERE entry='44640';
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
('44640', '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Как прикажешь, вождь!');

DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=83173;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 83173, 0, 0, 31, 0, 3, 44592, 0, 0, 0, 0, '', 'TARGET ONLY Fallen human'),
(13, 1, 83173, 0, 1, 31, 0, 3, 44593, 0, 0, 0, 0, '', 'TARGET ONLY Fallen human');
