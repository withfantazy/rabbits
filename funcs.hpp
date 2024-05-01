#pragma once
#include "Ashes.hpp"
#include "Grass.hpp"
#include "Fox.hpp"
#include "None.hpp"
#include "Rabbit.hpp"
#include "Trace.hpp"

bool check_move(Field& field, int x, int y);
void Spawn(Field& field, int x, int y, Spec spec);
void Death(Field& field, int x, int y, Spec spec);
void OvergrownWithGrass(Field& field, int x, int y);
std::pair<int, int> Nearest_Free_Cell(Field& field, int x, int y);