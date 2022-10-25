// Closest Points.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
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
	std::cout << "D[" << index1 << "," << index2 << "]: " << min << std::endl;
}

// Recusive function to find the closest pair of points
double closest_pair(std::vector<Point> points, int n) {

	auto index1 = points[0].index;
	auto index2 = points[(n-1)].index;
	// Base case
	if (n <= 3) {
		double min = DBL_MAX;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (distance(points[i], points[j]) < min) {
					min = distance(points[i], points[j]);
					//index1 = points[i].index;
					//index2 = points[j].index;
				}
			}
		}
		print_min(min, index1, index2);
		//index1 = 0;
		//index2 = 0;
		return min;
	}

	// Find the middle point
	int mid = n / 2;
	Point mid_point = points[mid];

	// Divide the points into two halves
	std::vector<Point> left;
	std::vector<Point> right;
	for (int i = 0; i < n; i++) {
		if (i < mid) {
			left.push_back(points[i]);
		}
		else {
			right.push_back(points[i]);
		}
	}

	// Find the closest pair of points in the left and right halves
	double left_min = closest_pair(left, mid);
	double right_min = closest_pair(right, n - mid);

	// Find the minimum of the two
	double min = left_min < right_min ? left_min : right_min;

	// Create a strip of points around the middle point
	std::vector<Point> strip;
	for (int i = 0; i < n; i++) {
		if (abs(points[i].x - mid_point.x) < min) {
			strip.push_back(points[i]);
		}
	}

	// Sort the strip by y coordinate
	std::sort(strip.begin(), strip.end(), y_compare);

	// Find the closest pair of points in the strip
	for (int i = 0; i < strip.size(); i++) {
		for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; j++) {
			if (distance(strip[i], strip[j]) < min) {
				min = distance(strip[i], strip[j]);
				//index1 = strip[i].index;
				//index2 = strip[j].index;
			}
		}
	}

	print_min(min, index1, index2);
	//index1 = 0;
	//index2 = 0;
	return min;
}
// recusivly find the closet pair of points in points
double closest_pair2(std::vector<Point> points, int left, int right) {
	double min{ 0.00 };

	// if right - left < 3 find closest point by brute force
	auto index1 = 0;
	auto index2 = 0;
	// Base case
	if (right - left <= 3) {
		double min = DBL_MAX;
		for (int i = left; i < right; i++) {
			for (int j = i + 1; j < right; j++) {
				if (distance(points[i], points[j]) < min) {
					min = distance(points[i], points[j]);
					index1 = points[i].index;
					index2 = points[j].index;
				}
			}
		}
		print_min(min, index1, index2);
		return min;
	}
	
	// Find the middle point
	int mid = (left + right) / 2;
	Point mid_point = points[mid];
	
	// Call closest pair on right half
	double right_min = closest_pair2(points, mid, right);

	// Call closest_pair on left half
	double left_min = closest_pair2(points, left, mid - 1);

	// Find the minimum of the two
	min = left_min < right_min ? left_min : right_min;
	
	// Create a strip of points around the middle point
	std::vector<Point> strip;
	
	for (int i = left; i < right; i++) {
		if (abs(points[i].x - mid_point.x) < min) {
			strip.push_back(points[i]);
		}
	}
	
	// Sort the strip by y coordinate
	std::sort(strip.begin(), strip.end(), y_compare);
	
	// Find the closest pair of points in the strip
	for (int i = 0; i < strip.size(); i++) {
		for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; j++) {
			if (distance(strip[i], strip[j]) < min) {
				min = distance(strip[i], strip[j]);
				index1 = strip[i].index;
				index2 = strip[j].index;
			}
		}
	}
	
	print_min(min, index1, index2);
	



	return min;
}

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
	// Find closest pair using closest_pair
	double min{ 0 };
	//min = closest_pair2(points, 0, (n-1));
	min = closest_pair(points, n);

	// Print the min
	//std::cout << min << std::endl;


	// Close file
	//inputFile.close();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
