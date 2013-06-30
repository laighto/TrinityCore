SET NAMES 'utf8';

DELETE FROM `command` WHERE `name`='promote friend';
INSERT INTO `command` (`name`, `security`, `help`) VALUES 
('promote friend', 0, 'Syntax: .promote friend $CharacterName\r\nAllow set ingame friend to get party bonuses');

DELETE FROM `trinity_string` WHERE entry IN (788, 789, 790, 791);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
('788', 'ERROR! You already set your friend', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Ошибка! Вы уже указали друга.'),
('789', 'All characters from account of player %s now your friends', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Все персонажи с аккаунта игрока %s стали вашими друзьями!'),
('790', '|cFF14ABFFYour friend (recruit)|cFFFF0021 %s |cFF14ABFFis loged in|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cFF14ABFFВаш друг (рекрут)|cFFFF0021 %s |cFF14ABFFзашел в игру|r'),
('791', '|cFF14ABFFYour friend (recruiter)|cFFFF0021 %s |cFF14ABFFis loged in|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cFF14ABFFВаш друг (рекрутер)|cFFFF0021 %s |cFF14ABFFзашел в игру|r');
