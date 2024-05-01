#pragma once
#include "Grass.hpp"

//int Grass::num_of_grass = 0;

void Grass::Behavior(Field& field) {
	set_age_remain(get_age_remain() - 1);
	if (get_age_remain() == 0) {
		Death(field, get_x(), get_y(), get_spec());
	}
	else if (get_age_remain() == 20) {
		freshness = Freshness::fresh;
	}
	else if (get_age_remain() == 10) {
		freshness = Freshness::withered;
	}
}