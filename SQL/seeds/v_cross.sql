create or replace view v_cross as select 
	`seed`.`seed_cross`.`id_cross`,
	hex(`seed`.`seed_cross`.`id_cross`) AS `hexid`,
	ifnull(`seed`.`seed_cross`.`cross_parentage`,concat(ifnull(ifnull(concat(`seed`.`seed_cross`.`cross_mom`,' ',left(`mom`.`genus`,1),'. ',`mom`.`species`, ifnull(concat(' ', `mom`.`plant_infraspecies`), ''),ifnull(concat(' [',`mom`.`plant_parentage`,']'),'')),`seed`.`seed_cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(`seed`.`seed_cross`.`cross_dad`,' ',left(`dad`.`genus`,1),'. ',`dad`.`species`, ifnull(concat(' ', `dad`.`plant_infraspecies`), ''),ifnull(concat(' [',`dad`.`plant_parentage`,']'),'')),`seed`.`seed_cross`.`cross_dad`),'Unknown'))) AS `cross_full_parentage`,
	ifnull(`seed`.`seed_cross`.`cross_parentage`,concat(ifnull(ifnull(concat(`seed`.`seed_cross`.`cross_mom`,' ',left(`mom`.`genus`,1),'. ',`mom`.`species`, ifnull(concat(' ', `mom`.`plant_infraspecies`), '')),`seed`.`seed_cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(`seed`.`seed_cross`.`cross_dad`,' ',left(`dad`.`genus`,1),'. ',`dad`.`species`, ifnull(concat(' ', `dad`.`plant_infraspecies`), '')),`seed`.`seed_cross`.`cross_dad`),'Unknown'))) AS `cross_id_parentage`,
	ifnull(`seed`.`seed_cross`.`cross_parentage`,concat(ifnull(ifnull(concat(left(`mom`.`genus`,1),'. ',`mom`.`species`, ifnull(concat(' ', `mom`.`plant_infraspecies`), '')),`seed`.`seed_cross`.`cross_mom`),'Unknown'),' x ',ifnull(ifnull(concat(left(`dad`.`genus`,1),'. ',`dad`.`species`, ifnull(concat(' ', `dad`.`plant_infraspecies`), '')),`seed`.`seed_cross`.`cross_dad`),'Unknown'))) AS `cross_short_parentage`,
	date_format(`seed`.`seed_cross`.`cross_harvest_date`,'%b %e, %Y') AS `cross_harvest_date`,
	date_format(`seed`.`seed_cross`.`cross_harvest_date` + interval 240 day,'%b %e, %Y') AS `cross_sow_by_date`,
	`seed`.`seed_cross`.`cross_sale_rate`,
	`source`.`source` `cross_source`,
	`seed`.`seed_cross`.`cross_note`,
	`seed`.`seed_cross`.`cross_stock`,
	`seed`.`seed_cross`.`cross_mom`,
	`seed`.`seed_cross`.`cross_dad`
from
	(((`seed`.`seed_cross`
	left join `pc`.`source` `source` on(`seed`.`seed_cross`.`cross_source` = `source`.`id_source`))
	left join `pc`.`v_pc` `mom` on(`seed`.`seed_cross`.`cross_mom` = `mom`.`ck`))
	left join `pc`.`v_pc` `dad` on(`seed`.`seed_cross`.`cross_dad` = `dad`.`ck`));