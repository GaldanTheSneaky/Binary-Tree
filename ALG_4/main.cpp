#include<iostream>
#include<fstream>
#include<string>
#include"BST.h"
#include<ctime>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	BSTree<int> *tree = new BSTree<int>;
	std::cout << "Choose data input way:" << std::endl;
	std::cout << "1: From file" << std::endl;
	std::cout << "2: From console" << std::endl;
	std::cout << "3: Randomly generated" << std::endl;
	int chosen_way;
	std::cin >> chosen_way;
	while (chosen_way < 1 || chosen_way > 3)
	{
		std::cout << "Enter number between 1 and 3" << std::endl;
		std::cin >> chosen_way;
	}
	

	switch (chosen_way)
	{
		case 1:
		{
			std::string filename;
			std::cout << "Enter name of the file: " << std::endl;
			std::cin >> filename;
			std::fstream file(filename, std::ios_base::in);

			if (!(file.is_open()))
			{
				std::cout << "File cannot be open!" << std::endl;
			}
			else
			{
				int buffer;
				while (file >> buffer)
					tree->Insert(buffer);
			}
		} break;

		case 2:
		{
			int tree_size;
			std::cout << "Enter size of the tree: " << std::endl;
			std::cin >> tree_size;
			while (tree_size <= 0)
			{
				std::cout << "Size of the tree must be greater than zero" << std::endl;
				std::cin >> tree_size;
			}

			std::cout << "Enter elements of the tree: " << std::endl;
			int buffer;
			for (int i = 0; i < tree_size; i++)
			{
				std::cin >> buffer;
				tree->Insert(buffer);
			}

		} break;

		case 3:
		{
			int tree_size;
			std::cout << "Enter size of the tree: " << std::endl;
			std::cin >> tree_size;
			while (tree_size <= 0)
			{
				std::cout << "Size of the tree must be greater than zero" << std::endl;
				std::cin >> tree_size;
			}

			std::cout << "Enter interval of numbers: " << std::endl;
			int floor, ceiling, value;
			std::cin >> floor >> ceiling;
			while (floor >= ceiling)
			{
				std::cout << "Floor must be lesser than ceiling" << std::endl;
				std::cin >> floor >> ceiling;
			}

			while (ceiling - floor < tree_size)
			{
				std::cout << "Interval mist be greater than size of the tree" << std::endl;
				std::cin >> floor >> ceiling;
			}

			std::uniform_int_distribution<> distr(floor, ceiling);

			for (int i = 0; i < tree_size; i++)
			{
				value = distr(gen);
				while (tree->Contains(value))
				{
					value = distr(gen);
				}
				tree->Insert(value);
			}

		} break;
	}

		std::cout << "Binary Search Tree: " << std::endl << std::endl;
		tree->Print();

		std::cout<< std::endl << "Enter value of destination: " << std::endl;
		int destination;
		std::cin >> destination;

		std::cout << "Path: ";
		int shortestPath = tree->FindPath(destination);
		std::cout << std::endl << "Length of shortest path equals " << shortestPath << std::endl;

		delete(tree);

	return 0;
}