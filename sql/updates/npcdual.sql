-- 1. Eliminar si ya existe para evitar errores de duplicado
DELETE FROM `creature_template` WHERE `entry` = 90000;

-- 2. Insertar la plantilla del NPC
INSERT INTO `creature_template` 
(`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellListId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) 
VALUES 
(90000, 0, 0, 0, 0, 0, 15413, 0, 0, 0, 'Kaelen', 'Maestro de Especialización Dual', NULL, 0, 70, 70, 2, 35, 1, 1, 1.14286, 1, 0, 100, 150, 0, 100, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 100, 150, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_dual_spec', 1);

-- 3. (Opcional) Equipar al NPC con un bastón para que se vea mejor
DELETE FROM `creature_equip_template` WHERE `entry` = 90000;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemid_1`, `itemid_2`, `itemid_3`) 
VALUES (90000, 1, 25611, 0, 0); 
