create or replace view 
	v_cross_sale as 
	select * from v_cross 
	where cross_stock > 0 and cross_sale_rate is not null;