#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

// Struct of point with x y coordinate
struct Point {
	double x;
	double y;
	int index;
};

//Sort points by x value
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

void print_min(double min, int index1, int index2) {
	std::cout << "D[" << index1 << "," << index2 << "]: " << std::fixed << std::setprecision(4) << min << std::endl;
}



class Nearest_points
{
public:
	// Class constructor takes vector points ans an integer size
	Nearest_points(std::vector<Point> points, int size);
	// method calculate using closest pair retuns void
	double calculate(std::vector<Point> points, int size);
	
	// vector points
	std::vector<Point> points;
	// integer size
	int size;

};

