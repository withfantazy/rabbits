#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Living.hpp"
#include "Grass.hpp"
#include "Rabbit.hpp"
#include "Fox.hpp"
#include "Trace.hpp"
#include "Ashes.hpp"
#include "None.hpp"

#define rows 30
#define cols 30

int main() {
	std::string dummy = "";
	try {
		srand(time(0));
		std::vector<std::vector<Living*>> field(rows, std::vector<Living*>(cols, 0));
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				int wtg = std::abs(rand()) % 15;
				if (wtg < 7) {
					field[i][j] = new Rabbit(i,j);
				}
				else if (wtg == 8) {
					field[i][j] = new Fox(i, j);
				}
				else {
					field[i][j] = new None(i,j);
				}
			}
		}

		std::cout << "gen 0\n";
		for (int i = 0;i < rows;++i) {
			for (int j = 0;j < cols;++j) {
				Spec spec = field[i][j]->get_spec();
				if (spec == Spec::grass) {
					std::cout << "/ ";
				}
				else if (spec == Spec::rabbit) {
					std::cout << "^ ";
				}
				else if (spec == Spec::fox) {
					std::cout << "& ";
				}
				else if (spec == Spec::ashes) {
					std::cout << "~ ";
				}
				else if (spec == Spec::none) {
					std::cout << " ";
				}
				else if (spec == Spec::trace) {
					std::cout << "_ ";
				}
			}
			std::cout << "\n";
		}
		/*std::cout << "\nGrass num " << Grass::get_num_of_grass() << "\n";
		std::cout << "Rabbit num " << Rabbit::get_num_of_rabbits() << "\n";
		std::cout << "Fox num " << Fox::get_num_of_foxes() << "\n";
		std::cout << "\n";*/
		std::getline(std::cin, dummy);
		system("cls");

		int gen = 1;
		while (true) {
			std::cout << "GEN " << gen << "\n";
			for (int i = 0;i < rows;++i) {
				for (int j = 0;j < cols;++j) {
					Spec spec = field[i][j]->get_spec();
					if (spec == Spec::grass) {
						std::cout << "/ ";
					}
					else if (spec == Spec::rabbit) {
						std::cout << "^ ";
					}
					else if (spec == Spec::fox) {
						std::cout << "& ";
					}
					else if (spec == Spec::ashes) {
						std::cout << "~ ";
						if (rand() % 500 == 0) {
							OvergrownWithGrass(field, i, j);
						}
					}
					else if (spec == Spec::none) {
						std::cout << " ";
						if (rand() % 500 == 0) {
							OvergrownWithGrass(field, i, j);
						}
					}
					else if (spec == Spec::trace) {
						std::cout << "_ ";
						if (rand() % 500 == 0) {
							OvergrownWithGrass(field, i, j);
						}
					}
					field[i][j]->Behavior(field);
				}
				std::cout << "\n";
			}
			/*std::cout << "\nGrass num " << Grass().get_num_of_grass() << "\n";
			std::cout << "Rabbit num " << Rabbit().get_num_of_rabbits() << "\n";
			std::cout << "Fox num " << Fox().get_num_of_foxes() << "\n";*/
			//std::cout << "\n";
			std::getline(std::cin, dummy);
			system("cls");
			gen++;
		}
	}
	catch (OutOfRange) {
		std::cout << "out of range";
	}
	catch (FieldOverflow) {
		std::cout << "field overflow";
	}
	catch (MathError) {
		std::cout << "math error";
	}
	catch (InvalidOperation) {
		std::cout << "invalid operation";
	}
	catch (UndefinedBehavior) {
		std::cout << "undefined behavior";
	}
}