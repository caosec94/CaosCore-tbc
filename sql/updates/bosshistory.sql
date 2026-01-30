CREATE TABLE IF NOT EXISTS `boss_history` (
  `Guid` bigint(20) NOT NULL AUTO_INCREMENT,
  `GuildId` int(10) NOT NULL,
  `CreatureEntry` int(10) NOT NULL,
  `CreatureName` varchar(255) NOT NULL,
  `PlayerCount` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `KillTime` int(10) NOT NULL,
  `KillDate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `KillData` longtext NOT NULL,
  `MapRaid` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `MapId` smallint(6) unsigned NOT NULL DEFAULT '0',
  `MapName` varchar(255) NOT NULL,
  `MapSpawnMode` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `MapMaxPlayers` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



REPLACE INTO `db_script_string` (`entry`, `content_default`) VALUES
(11006, '|Cffff0000[RAID INFO] |cff00ffff%s %uN: |Cff00ff00%s |cff00ffffderrotado por la hermandad |Cff00ff00%s|cff00ffff. Jugadores: %u/%u Tiempo: %um %us'),
(11007, '|Cffff0000[RAID INFO] |cff00ffff%s %uH: |Cff00ff00%s |cff00ffffderrotado por la hermandad |Cff00ff00%s|cff00ffff. Jugadores: %u/%u Tiempo: %um %us');

