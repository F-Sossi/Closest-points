#include "Nearest_points.h"
#include"Utilities.h"
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

// class to find nearest points
Nearest_points::Nearest_points(std::vector<Point> points, int size)
{
	// Sort points by x value
	std::sort(points.begin(), points.end(), x_compare);

	// set index of the points
	for (auto i = 0; i < size; i++) {
		points[i].index = i;
	}
	
	// initalize points to points
	this->points = points;
	// initalize size to size
	this->size = size;
}

double Nearest_points::calculate(std::vector<Point> points, int size)
{
	// set up variables to track the range of indices being examined
	auto last = size - 1;
	auto index1 = points[0].index;
	auto index2 = points[last].index;

	// Base case less than 3 points to compare
	if (size <= 3) {
		double min = DBL_MAX;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (distance(points[i], points[j]) < min) {
					min = distance(points[i], points[j]);
				}
			}
		}
		print_min(min, index1, index2);
		return min;
	}

	// Find the middle point
	int mid = size / 2;
	Point mid_point = points[mid];

	// Divide the array into to halves 
	std::vector<Point> left;
	std::vector<Point> right;
	for (int i = 0; i < size; i++) {
		if (i < mid) {
			left.push_back(points[i]);
		}
		else {
			right.push_back(points[i]);
		}
	}

	// Recurse on the left and right array 
	double min_left = calculate(left, mid);
	double right_min = calculate(right, size - mid);

	// Find the minimum of the two
	double min = min_left < right_min ? min_left : right_min;

	// Create a strip of points around the middle dividing line
	std::vector<Point> strip;
	for (int i = 0; i < size; i++) {
		if (abs(points[i].x - mid_point.x) < min) {
			strip.push_back(points[i]);
		}
	}

	// Sort the strip by y coordinate
	std::sort(strip.begin(), strip.end(), y_compare);

	// Find the closest pair of points in the strip should only loop 6 times max
	for (int i = 0; i < strip.size(); i++) {
		for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; j++) {
			if (distance(strip[i], strip[j]) < min) {
				min = distance(strip[i], strip[j]);
			}
		}
	}

	print_min(min, index1, index2);
	return min;
}

// method to calculate the nearest points

