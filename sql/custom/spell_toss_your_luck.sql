/* Fix Titanium Seal of Dalaran */
DELETE FROM `spell_script_names` WHERE `spell_id`=60476;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('60476', 'spell_toss_your_luck');

REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(604763, '%s finds the coin face down for tails!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '%s обнаруживает, что монетка упала решкой!'),
(604762, '%s catches the coin heads up!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '%s ловит монетку, падающую орлом вверх!'),
(604761, '%s casually flips his |cff0070dd|Hitem:44430:0:0:0:0:0:0:0:80|h[Titanium Seal of Dalaran]|h|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '%s небрежно подбрасывает в воздух свою |cff0070dd|Hitem:44430:0:0:0:0:0:0:0:80|h[Титановая печать Даларана]|h|r');
