#pragma once
#include "Fox.hpp"
#include "Trace.hpp"
#include "Errors.hpp"
#include "funcs.hpp"

class Rabbit : public Living {
private:
	static int num_of_rabbits;
	int lv_of_hunger = 0;
	int lv_of_fear = 0;
	int lv_of_love = 0;
public:
	Rabbit() = default;
	void Move(Field& field, int d_x, int d_y);
	int get_lv_of_hunger() const {
		return lv_of_hunger;
	}
	int get_lv_of_fear() const {
		return lv_of_fear;
	}
	int get_lv_of_love() const {
		return lv_of_love;
	}
	void set_lv_of_hunger(int n) {
		lv_of_hunger = n;
	}
	void set_lv_of_fear(int n) {
		lv_of_fear = n;
	}
	void set_lv_of_love(int n) {
		lv_of_love = n;
	}
	void Move_to_the_cell(Field& field, int x, int y, int other_x, int other_y);
	void Move_from_the_cell(Field& field, int x, int y, int other_x, int other_y);
	void Jump_to_the_cell(Field& field, int x, int y, int other_x, int other_y);
	void Jump_from_the_cell(Field& field, int x, int y, int other_x, int other_y);
	void Jump(Field& field, int d_x, int d_y);
	void Eat_grass(Field& field, int x, int y);
	void Mutation(Field& field, int x, int y);
	static int get_num_of_rabbits() { return num_of_rabbits; }
	static void set_num_of_rabbits(int n) { num_of_rabbits = n; }
	Rabbit(int x, int y) : Living(x, y, Spec::rabbit, 2199, 2) {
		//set_num_of_rabbits(get_num_of_rabbits() + 1);
		//std::cout << "Rabbit constructed\n";
	}
	virtual void Behavior(Field& field) override;
	~Rabbit() {
		//set_num_of_rabbits(get_num_of_rabbits() - 1);
		//std::cout << "Rabbit destructed\n";
	}
};

std::pair<int, int> Nearest_Rabbit(Field& field, int x, int y);
void Rabbits_repr(Field& field, int x1, int y1, int x2, int y2);