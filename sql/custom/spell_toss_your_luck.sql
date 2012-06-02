/* Fix Titanium Seal of Dalaran */
DELETE FROM `spell_script_names` WHERE `spell_id`=60476;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('60476', 'spell_toss_your_luck');