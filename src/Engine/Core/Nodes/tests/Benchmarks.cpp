#include "Benchmarks.h"
#include "../Grid.h"
#include "../Cylinder.h"
#include "../../Utils.h"

#include <iostream>

void Benchmarks::benchGrid()
{
	std::cout << "\n---- GRID 5x5 ----\n";

	{
		Timer timer_5x5{ "Benchmark Grid 5x5" };
		Mesh grid_5x5 = Grid::createGrid(5, 5, 10, 10);
	}

	std::cout << "\n---- GRID 10x10 ----\n";

	{
		Timer timer_10x10{ "Benchmark Grid 10x10" };
		Mesh grid_10x10 = Grid::createGrid(10, 10, 10, 10);
	}

	std::cout << "\n---- GRID 20x20 ----\n";

	{
		Timer timer_20x20{ "Benchmark Grid 20x20" };
		Mesh grid_20x20 = Grid::createGrid(20, 20, 10, 10);
	}

	std::cout << "\n---- GRID 100x100 ----\n";

	{
		Timer timer_100x100{ "Benchmark Grid 100x100" };
		Mesh grid_100x100 = Grid::createGrid(100, 100, 10, 10);
	}

	std::cout << "\n---- GRID 200x200 ----\n";

	{
		Timer timer_200x200{ "Benchmark Grid 200x200" };
		Mesh grid_200x200 = Grid::createGrid(200, 200, 10, 10);
	}
}

void Benchmarks::benchCylinder()
{

	std::cout << "\n---- CYLINDER Divisions 8 ----\n";

	{
		Timer timer_8{ "Benchmark CYLINDER Div 8" };
		Mesh cylinder_8 = Cylinder::createCylinder({ 0, 0, 0 }, { 10.0f, 10.0f }, 10.0f, 8, false);
	}

	std::cout << "\n---- CYLINDER Divisions 5000 ----\n";

	{
		Timer timer_500{ "Benchmark CYLINDER Div 5000" };
		Mesh cylinder_500 = Cylinder::createCylinder({ 0, 0, 0 }, { 10.0f, 10.0f }, 10.0f, 5000, false);
	}

	std::cout << "\n---- CYLINDER Divisions 50000 ----\n";

	{
		Timer timer_5000{ "Benchmark CYLINDER Div 50000" };
		Mesh cylinder_5000 = Cylinder::createCylinder({ 0, 0, 0 }, { 10.0f, 10.0f }, 10.0f, 50000, false);
	}

}
