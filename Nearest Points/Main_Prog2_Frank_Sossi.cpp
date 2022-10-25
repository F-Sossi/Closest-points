// Closest Points.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "Closest_points_Frank_Sossi.h"



int main()
{
	auto n = 0;

	// Open file program1data.txt for reading
	std::ifstream inputFile("program2data.txt");


	// Check if file opened successfully
	if (!inputFile.is_open()) {
		std::cout << "Error opening file" << std::endl;
	}

	// Read number of points
	inputFile >> n;

	// Create vector of points
	std::vector<Point> points(n);

	// Read points from file
	for (auto i = 0; i < n; i++) {
		inputFile >> points[i].x >> points[i].y;
	}

	// Sort points by x value
	std::sort(points.begin(), points.end(), x_compare);

	// set index of the points
	for (auto i = 0; i < n; i++) {
		points[i].index = i;
	}
/*
	std::cout << "Sorted \n" << std::endl;
	//print points
	for (auto i = 0; i < n; i++) {
		std::cout << points[i].x << " " << points[i].y << " " << points[i].index << std::endl;
	}

	std::cout << "\n distance \n" << std::endl;
	// print distance between all points
	for (auto i = 0; i < n; i++) {
		for (auto j = i + 1; j < n; j++) {
			std::cout << "D[" << points[i].index << "," << points[j].index << "]: " << distance(points[i], points[j]) << std::endl;
		}
	}

	std::cout << "\n alg output \n" << std::endl;

*/
	// Find closest pair using closest_pair
	double min{0};
	min = closest_pair(points, n);
	
	return 0;
}
