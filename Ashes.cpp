#pragma once
#include "Ashes.hpp"

void Ashes::Behavior(Field& field) {
	set_age_remain(get_age_remain() - 1);
	if (get_age_remain() == 0) {
		int x = get_x();
		int y = get_y();
		delete field[x][y];
		field[x][y] = new Grass(x, y, Freshness::immature);
	}
}