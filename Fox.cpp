#pragma once
#include "Fox.hpp"

//int Fox::num_of_foxes = 0;

void Fox::Move(Field& field, int d_x, int d_y)
{
	//std::cout << "Fox moved\n";
	int x = this->get_x();
	int y = this->get_y();
	if (check_move(field, x + d_x, y + d_y) && (field[x + d_x][y + d_y]->get_spec() == Spec::none || field[x + d_x][y + d_y]->get_spec() == Spec::trace)) {
		delete field[x + d_x][y + d_y];
		field[x + d_x][y + d_y] = this;
		set_x(x + d_x);
		set_y(y + d_y);
		field[x][y] = new Trace(x, y, Trace_spec::Fox_spec);
	}
}

bool Fox::Scan_trace(Field& field, int x, int y) const
{
	return field[x][y]->get_spec() == Spec::trace;
}

void Fox::Kill(Field& field, int other_x, int other_y) {
	if (check_move(field, other_x, other_y)) {
		//std::cout << "Fox kills\n";
		Death(field, other_x, other_y, Spec::rabbit);
		int x = get_x();
		int y = get_y();
		Fox::Move(field, other_x - get_x(), other_y - get_y());

	}
}

void Fox::Move_to_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Move(field, other_x - x != 0 ? (other_x - x) / std::abs(other_x - x) : 0, other_y - y != 0 ? (other_y - y) / std::abs(other_y - y) : 0);
}

void Fox::Move_from_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Move(field, other_x - x != 0 ? -(other_x - x) / std::abs(other_x - x) : 0, other_y - y != 0 ? -(other_y - y) / std::abs(other_y - y) : 0);
}

void Fox::Behavior(Field& field) {
	if (get_lv_of_hunger() > 20) {
		std::pair<int, int> waymark = Nearest_Rabbit(field, get_x(), get_y());
		if (get_x() != waymark.first || get_y() != waymark.second) {
			Kill(field, waymark.first, waymark.second);
			set_lv_of_hunger(0);
		}
	}
	Move(field, rand() % 2, rand() % 2);
	std::pair<int, int>waymark = Nearest_Fox(field, get_x(), get_y());
	if (get_x() != waymark.first || get_y() != waymark.second) {
		Fox_repr(field, get_x(), get_y(), waymark.first, waymark.second);
		set_lv_of_love(get_lv_of_love() - 5);
	}
	/*if (get_lv_of_love() > 15) {
		Move(field, rand() % 2, rand() % 2);
		waymark = Nearest_Fox(field, get_x(), get_y());
		if (get_x() != waymark.first || get_y() != waymark.second) {
			Fox_repr(field, get_x(), get_y(), waymark.first, waymark.second);
			set_lv_of_love(get_lv_of_love() - 10);
		}
	}*/
	if (get_lv_of_senses() > 25) {
		waymark = Nearest_Trace(field, get_x(), get_y());
		if (get_x() != waymark.first || get_y() != waymark.second) {
			Move_to_the_cell(field, get_x(), get_y(), waymark.first, waymark.second);
			set_lv_of_senses(get_lv_of_senses() - 5);
		}
	}
	set_age_remain(get_age_remain() - 1);
	set_lv_of_hunger(get_lv_of_hunger() + rand() % 5);
	set_lv_of_love(get_lv_of_love() + rand() % 5);
	if (get_lv_of_senses() < 25) {
		set_lv_of_senses(get_lv_of_senses() + 5);
	}
	if (get_age_remain() == 0 || get_lv_of_hunger() > 100) {
		Death(field, get_x(), get_y(), get_spec());
	}
	if (get_lv_of_love() > 30) {
		set_age_remain(get_age_remain() - 1);
	}
}

std::pair<int, int> Nearest_Fox(Field& field, int x, int y) {
	std::vector<std::pair<int, int>> pos = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto pr : pos) {
		if (check_move(field, x + pr.first, y + pr.second) && field[x + pr.first][y + pr.second]->get_spec() == Spec::fox) {
			return { x + pr.first, y + pr.second };
		}
	}
	return { x, y };
}

void Fox_repr(Field& field, int x1, int y1, int x2, int y2) {
	std::pair<int, int> nfc = Nearest_Free_Cell(field, x1, y1);
	if (nfc.first != x1 || nfc.second != y1) {
		Spawn(field, nfc.first, nfc.second, Spec::fox);
	}
	else {
		nfc = Nearest_Free_Cell(field, x2, y2);
		if (nfc.first != x2 || nfc.second != y2) {
			Spawn(field, nfc.first, nfc.second, Spec::fox);
		}
	}
}