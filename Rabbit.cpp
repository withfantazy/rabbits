#pragma once
#include<algorithm>
#include "Rabbit.hpp"

//int Rabbit::num_of_rabbits = 0;


void Rabbit::Move(Field& field, int d_x, int d_y)
{
	//std::cout << "Rabbit moved \n";
	int x = this->get_x();
	int y = this->get_y();
	if (check_move(field, x + d_x, y + d_y) && (field[x + d_x][y + d_y]->get_spec() == Spec::none || field[x + d_x][y + d_y]->get_spec() == Spec::trace)) {
		field[x + d_x][y + d_y] = this;
		set_x(x + d_x);
		set_y(y + d_y);
		field[x][y] = new Trace(x, y, Trace_spec::Rabbit_spec);
	}
}

void Rabbit::Jump(Field& field, int d_x, int d_y)
{
	//std::cout << "Rabbit jumped\n";
	int x = this->get_x();
	int y = this->get_y();
	if (check_move(field, x + d_x, y + d_y) && (field[x + d_x][y + d_y]->get_spec() == Spec::none || field[x + d_x][y + d_y]->get_spec() == Spec::trace)) {
		delete field[x + d_x][y + d_y];
		field[x + d_x][y + d_y] = this;
		set_x(x + d_x);
		set_y(y + d_y);
		field[x][y] = new Trace(x, y, Trace_spec::Rabbit_spec);
	}
}

void Rabbit::Move_to_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Move(field, other_x - x != 0 ? (other_x - x) / std::abs(other_x - x) : 0, other_y - y != 0 ? (other_y - y) / std::abs(other_y - y) : 0);
}

void Rabbit::Move_from_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Move(field, other_x - x != 0 ? -(other_x - x) / std::abs(other_x - x) : 0, other_y - y != 0 ? -(other_y - y) / std::abs(other_y - y) : 0);
}

void Rabbit::Jump_to_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Jump(field, other_x - x != 0 ? (other_x - x) * 2 / std::abs(other_x - x) : 0, other_y - y != 0 ? (other_y - y) * 2 / std::abs(other_y - y) : 0);
}

void Rabbit::Jump_from_the_cell(Field& field, int x, int y, int other_x, int other_y)
{
	Jump(field, other_x - x != 0 ? -(other_x - x) * 2 / std::abs(other_x - x) : 0, other_y - y != 0 ? -(other_y - y) * 2 / std::abs(other_y - y) : 0);
}

void Rabbit::Eat_grass(Field& field, int other_x, int other_y)
{
	if (check_move(field, other_x, other_y)) {
		//std::cout << "Rabbit eats\n";
		Death(field, other_x, other_y, Spec::grass);
		Rabbit::Move(field, other_x - get_x(), other_y - get_y());
	}
}

void Rabbit::Mutation(Field& field, int x, int y) {
	set_age_remain(get_age_remain() + rand() % 30);
	set_lv_of_hunger(get_lv_of_hunger() + rand() % 30);
}

void Rabbit::Behavior(Field& field) {
	int love = get_lv_of_love();
	int hunger = get_lv_of_hunger();
	int fear = get_lv_of_fear();
	std::vector<int> needs = { love, hunger, fear };
	std::sort(needs.begin(), needs.end());
	std::pair<int, int> waymark = {};
	for (int i = needs.size() - 1;i >= 0;--i) {
		if (needs[i] == love) {
			Rabbits_repr(field, get_x(), get_y(), waymark.first, waymark.second);
			set_lv_of_love(5);
		}
		else if (needs[i] == hunger) {
			std::pair<int, int> waymark = Nearest_Grass(field, get_x(), get_y());
			Eat_grass(field, get_x(), get_y());
			set_lv_of_hunger(10);
		}
		else if (needs[i] == fear) {
			std::pair<int, int> waymark = Nearest_Fox(field, get_x(), get_y());
			Jump_from_the_cell(field, get_x(), get_y(), waymark.first, waymark.second);
			set_lv_of_fear(0);
		}
	}
	Jump(field, rand() % 3, rand() % 3);
	set_age_remain(get_age_remain() - 1);
	set_lv_of_hunger(hunger + 1);
	set_lv_of_love(love + 1);
	waymark = Nearest_Fox(field, get_x(), get_y());
	if (waymark.first != get_x() || waymark.second != get_y()) {
		set_lv_of_fear(fear + 1);
		Jump_from_the_cell(field, get_x(), get_y(), waymark.first, waymark.second);
	}
	set_lv_of_fear(get_lv_of_fear() + 1);
	if (get_age_remain() == 0 || get_lv_of_hunger() > 210) {
		Death(field, get_x(), get_y(), get_spec());
	}
	if (get_lv_of_fear() > 50) {
		set_age_remain(get_age_remain() - 1);
	}if (get_lv_of_love() > 50) {
		set_age_remain(get_age_remain() - 1);
	}
	for (int i = 0;i < 3;++i) {
		//std::cout << get_x() << ' ' << get_y() << "help\n";
		//Mutation(field, get_x(), get_y());
	}
}

std::pair<int, int> Nearest_Rabbit(Field& field, int x, int y) {
	std::vector<std::pair<int, int>> pos = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto pr : pos) {
		if (check_move(field, x + pr.first, y + pr.second) && field[x + pr.first][y + pr.second]->get_spec() == Spec::rabbit) {
			return { x + pr.first, y + pr.second };
		}
	}
	return { x, y };
}

void Rabbits_repr(Field& field, int x1, int y1, int x2, int y2) {
	std::pair<int, int> nfc = Nearest_Free_Cell(field, x1, y1);
	if (nfc.first != x1 || nfc.second != y1) {
		Spawn(field, nfc.first, nfc.second, Spec::rabbit);
	}
	else if (nfc.first != x1 || nfc.second != y1) {
		nfc = Nearest_Free_Cell(field, x2, y2);
		if (nfc.first != x2 || nfc.second != y2) {
			Spawn(field, nfc.first, nfc.second, Spec::rabbit);
		}
	}
	else {
		int num_of_kids = 3;
		for (int ind_i = 0;ind_i < field.size();++ind_i) {
			for (int ind_j = 0;ind_j < field[0].size();++ind_j) {
				if (field[ind_i][ind_j]->get_spec() == Spec::none || field[ind_i][ind_j]->get_spec() == Spec::trace) {
					Spawn(field, ind_i, ind_j, Spec::rabbit);
					num_of_kids--;
					if (num_of_kids == 0) {
						break;
					}
				}
			}
			if (!num_of_kids) {
				break;
			}
		}
	}
}