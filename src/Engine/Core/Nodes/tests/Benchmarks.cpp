#include "Benchmarks.h"
#include "../Grid.h"
#include "../../Utils.h"

void Benchmarks::benchGrid()
{
	{
		Timer timer_5x5{ "Benchmark Grid 5x5" };
		Mesh grid_5x5 = Grid::createGrid(5, 5, 10, 10);
	}

	{
		Timer timer_10x10{ "Benchmark Grid 10x10" };
		Mesh grid_10x10 = Grid::createGrid(10, 10, 10, 10);
	}

	{
		Timer timer_20x20{ "Benchmark Grid 20x20" };
		Mesh grid_20x20 = Grid::createGrid(20, 20, 10, 10);
	}

	{
		Timer timer_100x100{ "Benchmark Grid 100x100" };
		Mesh grid_100x100 = Grid::createGrid(100, 100, 10, 10);
	}
}
