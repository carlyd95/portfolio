create VIEW `v_cross_parent` AS 
	select distinct `seed_cross`.`cross_mom` AS `parent` 
	from `seed_cross` 
	where `seed_cross`.`cross_mom` like '____-___' 
		union 
	select distinct `seed_cross`.`cross_dad` AS `parent` 
	from `seed_cross`
	where `seed_cross`.`cross_dad` like '____-___';