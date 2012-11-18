SET @ArcherEntry  := 14489;
SET @ErisEntry    := 14494;
SET @PeasantEntry := 14484;

-- stealth Eris
DELETE FROM `creature_template_addon` WHERE (`entry`=14494);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(14494, 0, 0, 0, 0, 0, 23196);

-- update involved creatures
UPDATE creature_template SET ScriptName = 'npc_fleeing_peasant', RegenHealth = 0 WHERE entry = @PeasantEntry;
UPDATE creature_template SET ScriptName = 'npc_eris_havenfire', AIName = '' WHERE entry = @ErisEntry;
UPDATE creature_template SET AIName = 'ArcherAI', equipment_id = 14489 WHERE entry = @ArcherEntry;

-- hand out weapons
DELETE FROM creature_equip_template WHERE entry = @ArcherEntry;
INSERT INTO creature_equip_template VALUES (@ArcherEntry, 0, 0, 11304);