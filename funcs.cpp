#pragma once
#include "funcs.hpp"

bool check_move(Field& field, int x, int y) {
	return (0 <= x && x < field.size() && 0 <= y && y < field.size());
}


void Spawn(Field& field, int x, int y, Spec spec)
{
	//std::cout << "something spawned\n";
	if (field[x][y]->get_spec() == Spec::none && field[x][y]->get_spec() == Spec::trace) {
		delete field[x][y];
		if (spec == Spec::rabbit) {
			field[x][y] = new Rabbit(x, y);
		}
		else if (spec == Spec::fox) {
			field[x][y] = new Fox(x, y);
		}
		else if (spec == Spec::grass) {
			field[x][y] = new Grass(x, y, Freshness::immature);
		}
		else if (spec == Spec::ashes) {
			field[x][y] = new Ashes(x, y);
		}
	}
}

void Death(Field& field, int x, int y, Spec spec) {
	Trace_spec trace_spec = Trace_spec::undefined_spec;
	if (field[x][y]->get_spec() == Spec::rabbit) {
		trace_spec = Trace_spec::Rabbit_spec;
	}
	else if (field[x][y]->get_spec() == Spec::fox) {
		trace_spec = Trace_spec::Fox_spec;
	}
	delete field[x][y];
	if (trace_spec != Trace_spec::undefined_spec) {
		field[x][y] = new Ashes(x, y);
	}
	else {
		field[x][y] = new None(x, y);
	}

}



std::pair<int, int> Nearest_Free_Cell(Field& field, int x, int y) {
	std::vector<std::pair<int, int>> pos = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (auto& pr : pos) {
		if (check_move(field, x + pr.first, y + pr.second) && (field[x + pr.first][y + pr.second]->get_spec() == Spec::none || field[x + pr.first][y + pr.second]->get_spec() == Spec::trace)) {
			return { x + pr.first, y + pr.second };
		}
	}
	return { x, y };
}



void OvergrownWithGrass(Field& field, int x, int y) {
	delete field[x][y];
	field[x][y] = new Grass(x, y, Freshness::immature);
}
