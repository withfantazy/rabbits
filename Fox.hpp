#pragma once
#include "Living.hpp"
#include "Trace.hpp"
#include "funcs.hpp"

class Fox : public Living {
private:
	static int num_of_foxes;
	int lv_of_hunger = 0;
	int lv_of_senses = 0;
	int lv_of_love = 0;
public:
	Fox() = default;
	int get_lv_of_hunger() const {
		return lv_of_hunger;
	}
	int get_lv_of_senses() const {
		return lv_of_senses;
	}
	int get_lv_of_love() const {
		return lv_of_love;
	}
	void set_lv_of_hunger(int n) {
		lv_of_hunger = n;
	}
	void set_lv_of_senses(int n) {
		lv_of_senses = n;
	}
	void set_lv_of_love(int n) {
		lv_of_love = n;
	}
	void Move(Field& field, int d_x, int d_y);
	void Move_to_the_cell(Field& field, int x, int y, int other_x, int other_y);
	void Move_from_the_cell(Field& field, int x, int y, int other_x, int other_y);
	bool Scan_trace(Field& field, int x, int y) const;
	void Kill(Field& field, int x, int y);
	static int get_num_of_foxes() { return num_of_foxes; }
	static void set_num_of_foxes(int n) { num_of_foxes = n; }
	Fox(int x, int y) : Living(x, y, Spec::fox, 2199, 3) {
		//set_num_of_foxes(get_num_of_foxes() + 1);
		//std::cout << "Fox constructed\n";
	}
	virtual void Behavior(Field& field) override;
	~Fox() {
		//set_num_of_foxes(get_num_of_foxes() - 1);
		//std::cout << "Fox destructed\n";
	}
};

std::pair<int, int> Nearest_Fox(Field& field, int x, int y);
void Fox_repr(Field& field, int x1, int y1, int x2, int y2);