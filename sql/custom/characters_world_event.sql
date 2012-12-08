/*
Navicat MySQL Data Transfer

Source Server         : local
Source Server Version : 50519
Source Host           : localhost:3306
Source Database       : characters

Target Server Type    : MYSQL
Target Server Version : 50519
File Encoding         : 65001

Date: 2012-12-08 23:36:30
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `world_event`
-- ----------------------------
DROP TABLE IF EXISTS `world_event`;
CREATE TABLE `world_event` (
  `creatures_killed` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of world_event
-- ----------------------------
INSERT INTO `world_event` VALUES ('0');

-- ----------------------------
-- Table structure for `world_event_player`
-- ----------------------------
DROP TABLE IF EXISTS `world_event_player`;
CREATE TABLE `world_event_player` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `creature_killed` int(10) unsigned NOT NULL DEFAULT '0',
  `boss_killed` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of world_event_player
-- ----------------------------
