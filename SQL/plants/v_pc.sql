create or replace view v_pc as
	select concat(lpad(hex(`pc`.`plant`.`id_genus`),2,'0'),lpad(hex(`pc`.`plant`.`id_species`),2,'0'),concat('-',lpad(hex(`pc`.`plant`.`id_plant`),3,'0'))) AS `ck`,
		`pc`.`genus`.`genus` AS `genus`,
		`pc`.`species`.`species` AS `species`,
		`pc`.`plant`.`plant_infraspecies` AS `plant_infraspecies`,
		`pc`.`plant`.`plant_locality` AS `plant_locality`,
		`pc`.`plant`.`plant_field_number` AS `plant_field_number`,
		`pc`.`source`.`source` AS `plant_source`,
		`pc`.`plant`.`plant_cultivar` AS `plant_cultivar`,
		`pc`.`plant`.`plant_parentage` AS `plant_parentage`,
		`pc`.`plant`.`plant_note` AS `plant_note`,
		`pc`.`plant`.`plant_empty` AS `plant_empty`,
		`pc`.`plant`.`plant_has_pic` AS `plant_has_pic`,
		`pc`.`plant`.`plant_source` AS `id_plant_source` 
	from (((`pc`.`plant` 
	join `pc`.`species` on(`pc`.`plant`.`id_genus` = `pc`.`species`.`id_genus` and `pc`.`plant`.`id_species` = `pc`.`species`.`id_species`))
	join `pc`.`genus` on(`pc`.`plant`.`id_genus` = `pc`.`genus`.`id_genus`))
	join `pc`.`source` on(`pc`.`plant`.`plant_source` = `pc`.`source`.`id_source`));