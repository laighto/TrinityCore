-- implemented apothecary trio script Love In the Air based on old script by @w1sht0l1v3 mod by @chaosua
SET @NPC_FRYE := 36272;
SET @NPC_HUMMEL := 36296;
SET @NPC_BAXTER := 36565;
SET @NPC_CRAZED := 36568;

UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_frye' WHERE `entry`=@NPC_FRYE;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_hummel' WHERE `entry`=@NPC_HUMMEL;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_apothecary_baxter' WHERE `entry`=@NPC_BAXTER;
UPDATE `creature_template` SET `AIName`='',`ScriptName`='npc_crazed_apothecary' WHERE `entry`=@NPC_CRAZED;

DELETE FROM `creature_text` WHERE `entry` IN (@NPC_FRYE,@NPC_HUMMEL,@NPC_BAXTER);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@NPC_HUMMEL,0,0,"Did they bother to tell you who I am and why I am doing this?",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,1,0,"...or are they just using you like they do everybody else?",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,2,0,"But what does it matter. It is time for this to end.",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,3,0,"Baxter! Get in here and help! NOW!",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,4,0,"It is time, Frye! Attack!",12,0,100,0,0,0,"say text"),
(@NPC_HUMMEL,5,0,"Apothecaries! Give your life for The Crown!",12,0,100,0,0,0,"say text"),
(@NPC_FRYE,0,0,"Great. We're not gutless, we're incompetent.",12,0,100,0,0,0,"say text"),
(@NPC_BAXTER,0,0,"It has been the greatest honor of my life to server with you, Hummel.",12,0,100,0,0,0,"say text");

DELETE FROM locales_creature_text WHERE entry IN (@NPC_FRYE,@NPC_HUMMEL,@NPC_BAXTER);
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
(@NPC_HUMMEL, '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Они пытались сказать тебе кто я есть, и почему я это делаю?'),
(@NPC_HUMMEL, '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, '... или же они просто используют тебя как и всех остальных?'),
(@NPC_HUMMEL, '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Но кокое это имеет значение. Пришло время все это прекратить.'),
(@NPC_HUMMEL, '3', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Бакстер! Иди сюда  и помоги! СЕЙЧАС!'),
(@NPC_HUMMEL, '4', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Пришло время, Фрай! В атаку!'),
(@NPC_HUMMEL, '5', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Аптекари! Отдайте свою жизнь за Королевство!'),
(@NPC_FRYE, '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Отлично. Смелости нам хватило, а мозгов — нет.'),
(@NPC_BAXTER, '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Для меня было большой честью служить тебе, Хаммел.');

#DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry` IN (68530,68529);
#INSERT INTO `conditions`(`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`)VALUES
#(17,0,68530,0,11,1,27288,0,0,'',"Ice Prison - Death Knight Champion"),
#(17,0,68529,0,11,1,27288,0,0,'',"Ice Prison - Death Knight Champion");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (68530,68529);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(68530,-68529,0,'Remove Perfume Immune when Cologne Immune is applied'),
(68529,-68530,0,'Remove Cologne Immune when Perfume Immune is applied');

-- implemented apothecary trio script Love In the Air based on old script by @w1sht0l1v3 mod by @chaosua

--Lord Walden script
UPDATE creature_template SET ScriptName = 'boss_lord_walden' WHERE entry = 46963;
UPDATE creature_template SET ScriptName = 'npc_mystery_toxin' WHERE `entry` IN (50439,50522);

DELETE FROM `creature_template_addon` WHERE `entry` IN (50439,50522);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (50522, 0, 0, 0, 0, 0, '34873');
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (50439, 0, 0, 0, 0, 0, '34873');
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `InhabitType` = 4, `flags_extra` = 2 WHERE `entry` IN (50439, 50522);
DELETE FROM `creature` WHERE `id` IN (50439,50522);

DELETE FROM spell_linked_spell WHERE spell_trigger = 93607 AND spell_effect = 93689;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES 
(93607, 93689, 'SFK Lord Walden Toxic Catalyst');

DELETE FROM `creature_text` WHERE `entry` = 46963;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46963, 0, 0,"Even here I find myself beset by fools!",14, 0, 100, 0, 0, 0, "Lord Walden - SAY_AGGRO"),
(46963, 1, 0,"This childish effort ends now!",14, 0, 100, 0, 0, 0,"Lord Walden - SAY_KILL_1"),
(46963, 2, 0,"You shall annoy me no longer!",14, 0, 100, 0, 0, 0,"Lord Walden - SAY_KILL_2"),
(46963, 3, 0,"My new life was just beginning...",14, 0, 100, 0, 0, 0,"Lord Walden - SAY_DEATH");
DELETE FROM locales_creature_text WHERE entry IN (@NPC_FRYE,@NPC_HUMMEL,@NPC_BAXTER);
INSERT INTO `locales_creature_text`  (`entry`, `groupid`, `id`,`text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES 
(46963, '0', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Даже здесь мне нет покоя от глупцов!'),
(46963, '1', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Детские игры закончились!'),
(46963, '2', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Ты больше не будешь мне надоедать!'),
(46963, '3', '0', NULL,  NULL, NULL, NULL, NULL, NULL, NULL, 'Моя новая жизнь только начиналась...!');

UPDATE creature_template SET ScriptName = 'boss_lord_godfrey' WHERE entry = 46964;
UPDATE creature_template SET ScriptName = 'boss_commander_springvale' WHERE entry = 4278;
UPDATE creature_template SET ScriptName = 'boss_baron_silverlaine' WHERE entry = 3887;
UPDATE creature_template SET ScriptName = 'boss_baron_ashbury' WHERE entry = 46962;