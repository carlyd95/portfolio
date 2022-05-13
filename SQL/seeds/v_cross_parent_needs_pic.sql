create VIEW `v_cross_parent_needs_pic` AS 
	select `v_cross_parent`.`parent` AS `parent` 
	from (`seed`.`v_cross_parent` 
		join `pc`.`v_pc` on(`v_pc`.`ck` = `v_cross_parent`.`parent`)) 
	where `v_pc`.`plant_has_pic` = 0;