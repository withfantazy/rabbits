#pragma once
#include "Living.hpp"

class None : public Living {
public:
	None() = default;
	None(int x, int y) : Living(x, y, Spec::none, 0, 0) {}
	virtual void Behavior(Field& field) override {}
	~None() {}
};