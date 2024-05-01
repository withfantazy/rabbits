#pragma once
#include "Living.hpp"
#include "funcs.hpp"
#include "Errors.hpp"

enum Freshness {
	immature,
	fresh,
	withered
};

class Grass : public Living {
private:
	static int num_of_grass;
	Freshness freshness = immature;
public:
	Grass() = default;
	Freshness get_freshness() const { return freshness; }
	static int get_num_of_grass() { return num_of_grass; }
	static void set_num_of_grass(int n) { num_of_grass = n; }
	Grass(int x, int y, Freshness freshness) : Living(x, y, Spec::grass, 30, 0), freshness(freshness) {
		//std::cout << "Grass constructed\n";
		//set_num_of_grass(get_num_of_grass() + 1);
	}
	virtual void Behavior(Field& field) override;
	~Grass() {
		//std::cout << "Grass destructed\n";
		//set_num_of_grass(get_num_of_grass() - 1);
	}
};

std::pair<int, int> Nearest_Grass(Field& field, int x, int y);