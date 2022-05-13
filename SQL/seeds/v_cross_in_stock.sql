create or replace view v_cross_in_stock as 
	select * 
	from v_cross 
	where cross_stock > 0;