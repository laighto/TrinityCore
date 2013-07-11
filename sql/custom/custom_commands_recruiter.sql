SET NAMES 'utf8';

DELETE FROM `command` WHERE `name`='promote friend';
DELETE FROM `command` WHERE `name`='recruit friend';
DELETE FROM `command` WHERE `name`='recruit delete';
INSERT INTO `command` (`name`, `security`, `help`) VALUES 
('recruit friend', 0, 'Syntax: .recruit friend $CharacterName\r\nAllow set ingame friend(recruiter) to get party bonuses'),
('recruit delete', 1, 'Syntax: .recruit delete $CharacterName\r\nAllow delete recruiter data');

DELETE FROM `trinity_string` WHERE entry IN (788, 789, 790, 791);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
('788', 'ERROR! You already set your recruiter', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Ошибка! Вы уже указали рекрутера.'),
('789', 'All characters from account of player %s now your friends. Please RE-Login to changes take effect.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Все персонажи с аккаунта игрока %s стали вашими друзьями. Пожалуйста перезалогиньтесь в игру чтобы изминения вступили в силу.'),
('790', '|cFF14ABFFYour friend (recruit)|cFFFF0021 %s |cFF14ABFFis loged in|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cFF14ABFFВаш друг (рекрут)|cFFFF0021 %s |cFF14ABFFзашел в игру|r'),
('791', '|cFF14ABFFYour friend (recruiter)|cFFFF0021 %s |cFF14ABFFis loged in|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '|cFF14ABFFВаш друг (рекрутер)|cFFFF0021 %s |cFF14ABFFзашел в игру|r'),
('792', 'You have deleted your recruiter data. Please RE-Login to changes take effect.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Вы успешно удалили данные о рекрутере. Пожалуйста перезалогиньтесь в игру чтобы изминения вступили в силу.');
