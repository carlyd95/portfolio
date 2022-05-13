create view v_sown as select
	`seed`.`sowing`.`id_pot`,
	`genus`.`group_sowing_date`,
	`pot`.`pot_note`,
	`seed`.`sowing`.`id_cross`,
	hex(`seed`.`sowing`.`id_cross`) AS `hexid`,
	ifnull(`cross`.`cross_parentage`,concat(ifnull(ifnull(concat(`cross`.`cross_mom`,' ',left(`mom`.`genus`,1),'. ',`mom`.`species`,ifnull(concat(' [',`mom`.`plant_parentage`,']'),'')),`cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(`cross`.`cross_dad`,' ',left(`dad`.`genus`,1),'. ',`dad`.`species`,ifnull(concat(' [',`dad`.`plant_parentage`,']'),'')),`cross`.`cross_dad`),'Unknown'))) AS `cross_full_parentage`,
	ifnull(`cross`.`cross_parentage`,concat(ifnull(ifnull(concat(`cross`.`cross_mom`,' ',left(`mom`.`genus`,1),'. ',`mom`.`species`),`cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(`cross`.`cross_dad`,' ',left(`dad`.`genus`,1),'. ',`dad`.`species`),`cross`.`cross_dad`),'Unknown'))) AS `cross_id_parentage`,
	ifnull(`cross`.`cross_parentage`,concat(ifnull(ifnull(concat(left(`mom`.`genus`,1),'. ',`mom`.`species`),`cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(left(`dad`.`genus`,1),'. ',`dad`.`species`),`cross`.`cross_dad`),'Unknown'))) AS `cross_short_parentage`,
	date_format(`cross`.`cross_harvest_date`,'%b %e, %Y') AS `cross_harvest_date`,
	date_format(`cross`.`cross_harvest_date` + interval 240 day,'%b %e, %Y') AS `cross_sow_by_date`,
	`source`.`source` AS `cross_source`,
	`cross`.`cross_stock`,
	`cross`.`cross_mom`,
	`cross`.`cross_dad`
from
	((((((`seed`.`sowing` 
	left join `seed`.`sowing_pot` `pot` on(`seed`.`sowing`.`id_pot` = `pot`.`id_pot`))
	left join `seed`.`sowing_group` `genus` on(`pot`.`id_group` = `genus`.`id_group`))
	left join `seed`.`seed_cross` `cross` on(`seed`.`sowing`.`id_cross` = `cross`.`id_cross`))
	left join `pc`.`source` `source` on(`cross`.`cross_source` = `source`.`id_source`))
	left join `pc`.`v_pc` `mom` on(`cross`.`cross_mom` = `mom`.`ck`))
	left join `pc`.`v_pc` `dad` on(`cross`.`cross_dad` = `dad`.`ck`));