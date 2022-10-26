#pragma once

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

// Recusive function to find the closest pair of points
double closest_pair(std::vector<Point> points, int size) {
	auto length = size - 1;
	auto index1 = points[0].index;
	auto index2 = points[length].index;
	// Base case
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

	// Divide the points into two halves
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

	// Find the closest pair of points in the left and right halves
	double min_left = closest_pair(left, mid);
	double right_min = closest_pair(right, size - mid);

	// Find the minimum of the two
	double min = min_left < right_min ? min_left : right_min;

	// Create a strip of points around the middle point
	std::vector<Point> strip;
	for (int i = 0; i < size; i++) {
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
			}
		}
	}

	print_min(min, index1, index2);
	return min;
}
