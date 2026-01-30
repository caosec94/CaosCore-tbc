ALTER TABLE `characters` ADD COLUMN `active_spec` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1';

CREATE TABLE IF NOT EXISTS `character_dual_spec_actions` (
  `guid` int(11) UNSIGNED NOT NULL,
  `spec` tinyint(1) NOT NULL DEFAULT '1',
  `button` tinyint(3) UNSIGNED NOT NULL,
  `action` int(11) UNSIGNED NOT NULL,
  `type` tinyint(3) UNSIGNED NOT NULL,
  PRIMARY KEY (`guid`,`spec`,`button`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
