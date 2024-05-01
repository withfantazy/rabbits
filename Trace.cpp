#pragma once
#include "Trace.hpp"

void Trace::Behavior(Field& field) {
	set_age_remain(get_age_remain() - 1);
	if (get_age_remain() == 0) {
		Death(field, get_x(), get_y(), get_spec());
	}
}

std::pair<int, int> Nearest_Trace(Field& field, int x, int y) {
	std::vector<std::pair<int, int>> pos = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto pr : pos) {
		if (check_move(field, x + pr.first, y + pr.second) && field[x + pr.first][y + pr.second]->get_spec() == Spec::trace) {
			return { x + pr.first, y + pr.second };
		}
	}
	return { x, y };
}

std::pair<int, int> Nearest_Grass(Field& field, int x, int y) {
	std::vector<std::pair<int, int>> pos = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto pr : pos) {
		if (check_move(field, x + pr.first, y + pr.second) && field[x + pr.first][y + pr.second]->get_spec() == Spec::grass) {
			return { x + pr.first, y + pr.second };
		}
	}
	return { x, y };
}