create VIEW `v_field_number_dupes` as
	select `v_pc`.`ck` AS `ck`,
	`sub`.`plant_field_number` AS `plant_field_number`,
	`sub`.`count` AS `count`
	from (((select `v_pc`.`plant_field_number` AS `plant_field_number`, count(`v_pc`.`ck`) AS `count`
	from `pc`.`v_pc`
	where `v_pc`.`plant_field_number` regexp '[0-9]'
	group by `v_pc`.`plant_field_number`
	having count(`v_pc`.`plant_field_number`) > 2)) `sub`
	join `pc`.`v_pc` on(`sub`.`plant_field_number` = `v_pc`.`plant_field_number`))
	order by count desc, plant_field_number asc;




		