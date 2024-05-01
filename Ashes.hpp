#pragma once
#include "Living.hpp"
#include "Grass.hpp"


class Ashes : public Living {
public:
	Ashes() = default;
	Ashes(int x, int y) : Living(x, y, Spec::ashes, 2, 0) {}
	virtual void Behavior(Field& field) override;
	~Ashes() {}
};