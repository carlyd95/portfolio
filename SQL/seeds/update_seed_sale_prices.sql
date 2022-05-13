update v_cross_sale 
	set cross_sale_rate = 
		concat(
			'$',
			cast(substring_index(substring_index(cross_sale_rate,' / ',1),'$',-1) as double) / 2,
			' / ',
			substring_index(cross_sale_rate,' / ',-1)
		) 
		where cross_short_parentage not like '%bobii%'
			and cross_short_parentage not like '%groene%'
			and str_to_date(cross_harvest_date, '%b %e, %Y') < '2021-09-10 00:00:00';