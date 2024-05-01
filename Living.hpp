#pragma once
#include<vector>
#include<iostream>

enum Spec {
	grass,
	rabbit,
	fox,
	ashes,
	trace,
	none,
	undefined
};

class Living {
private:
	//static int num_of_living;
	int x = 0;
	int y = 0;
	int age_remain = 20;
	int speed = 0;
	int num_of_mutations = 0;
	Spec spec = undefined;
public:
	Living() = default;
	int get_x() const { return x; }
	int get_y() const { return y; }
	int get_age_remain() const { return age_remain; }
	int get_speed() const { return speed; }
	int get_num_of_mutations() const { return num_of_mutations; }
	//static int get_num_of_living() { return num_of_living; }
	//static void set_num_of_living(int n) { num_of_living = n; }
	Spec get_spec() const { return spec; }
	void set_x(int n) { x = n; }
	void set_y(int n) { y = n; }
	void set_age_remain(int n) { age_remain = n; }
	void set_speed(int n) { speed = n; }
	int get_num_of_mutations(int n) { num_of_mutations = n; }
	Living(int x, int y, Spec spec, int age_remain, int speed) : x(x), y(y), spec(spec), age_remain(age_remain), speed(speed) {
		//set_num_of_living(get_num_of_living() + 1);
	}
	virtual void Behavior(std::vector<std::vector<Living*>>& field) = 0;
	virtual ~Living() {
		//set_num_of_living(get_num_of_living() - 1);
	}
};

using Field = std::vector<std::vector<Living*>>;