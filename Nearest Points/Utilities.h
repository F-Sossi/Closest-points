#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>



bool x_compare(Point a, Point b) {
	return a.x < b.x;
}

// Sort points by y value
bool y_compare(Point a, Point b) {
	return a.y < b.y;
}

// Calculate distance between two points 
double distance(Point a, Point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

inline void print_min(double min, int index1, int index2) {
	std::cout << "D[" << index1 << "," << index2 << "]: " << std::fixed << std::setprecision(4) << min << std::endl;
}
