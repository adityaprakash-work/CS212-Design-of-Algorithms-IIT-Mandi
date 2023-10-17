// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

// ---INPUT---------------------------------------------------------------------
// User generated
// 1. An integer, 'n' (1 <= n <= 10^5), representing the number of 2D points.
// 2. 'n' lines, each containing two floating-point numbers, 'x' and 'y',
//    separated by a space. These represent the coordinates of the 2D points.
//    (-10^3 <= x, y <= 10^3)
vector<pair<double, double>> userInput()
{
    int n;
    cin >> n;
    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        points[i] = { x, y };
    }
    return points;
}
// Random generated
// 1. Same bounds as above for 'n', 'x', and 'y'
// vector<pair<double, double>> randomInput(int n)
// {
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_real_distribution<> dis(-1000, 1000);

//     vector<pair<double, double>> points(n);
//     for (int i = 0; i < n; i++)
//     {
//         double x = dis(gen);
//         double y = dis(gen);
//         points[i] = { x, y };
//     }

//     return points;
// }
// Random generated from a mixture of Gaussians
vector<pair<double, double>> randomInput(int n)
{
    random_device rd;
    mt19937 gen(rd());

    // Define the range for the uniform distributions for mean and std
    uniform_real_distribution<> mean_dis(-1000, 1000);
    uniform_real_distribution<> std_dis(50, 200);

    // Define the parameters for the mixture of Gaussians
    vector<pair<double, double>> centers(3);
    vector<double> weights = { 0.3, 0.4, 0.3 };
    vector<pair<double, double>> stds(3);

    // Generate random centers and stds from uniform distributions
    for (int i = 0; i < 4; i++)
    {
        double x_mean = mean_dis(gen);
        double y_mean = mean_dis(gen);
        double x_std = std_dis(gen);
        double y_std = std_dis(gen);
        centers[i] = { x_mean, y_mean };
        stds[i] = { x_std, y_std };
    }

    // Generate random points from the mixture of Gaussians
    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++)
    {
        // Choose a center randomly based on the weights
        discrete_distribution<int> center_dist(weights.begin(), weights.end());
        int center_idx = center_dist(gen);
        pair<double, double> center = centers[center_idx];
        pair<double, double> std = stds[center_idx];

        // Generate a random point from the chosen Gaussian
        normal_distribution<double> x_dist(center.first, std.first);
        normal_distribution<double> y_dist(center.second, std.second);
        double x = x_dist(gen);
        double y = y_dist(gen);
        points[i] = { x, y };
    }

    return points;
}

// ---OUTPUT--------------------------------------------------------------------
// 1. A vector of pairs of doubles, representing the coordinates of the points
//    that make up the convex hull in counter-clockwise order.
// 2. The total number of points in the convex hull.

// ---GRAHAM SCAN---------------------------------------------------------------
// 1. Find the point with the lowest y-coordinate, 'p0'.
// 2. Sort the points by polar angle with 'p0', in counter-clockwise order.
// 3. Push the first three points onto a stack.
// 4. For each remaining point, 'pi':
//    a. While the angle formed by points 'pi', 'pi-1', and 'pi-2' makes a
//       non-left turn, pop the top point off the stack.
//    b. Push 'pi' onto the stack.
// 5. The stack now contains the points that make up the convex hull.

// Edge cases:
// 1. If there are fewer than 3 points, the convex hull is the set of points.
// 2. If there are multiple points with the same y-coordinate, the one with the
//    lowest x-coordinate is chosen.
// 3. If multiple points have the same polar angle, the one farthest to 'p0' is
//    chosen.
// 4. If multiple points have the same polar angle and distance from 'p0', then
//    either can be chosen.
// 5. If triplet of points are collinear then all points are in the convex hull.

// Function to find the point with the lowest y-coordinate
pair<double, double> findLowestY(vector<pair<double, double>>& points)
{
    pair<double, double> lowest = points[0];
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].second < lowest.second || (points[i].second == lowest.second && points[i].first < lowest.first))
        {
            lowest = points[i];
        }
    }
    return lowest;
}

// Function to calculate the polar angle between two points
double polarAngle(pair<double, double> p1, pair<double, double> p2)
{
    double xDiff = p2.first - p1.first;
    double yDiff = p2.second - p1.second;
    return atan2(yDiff, xDiff);
}

// Function to calculate the distance between two points
double distance(pair<double, double> p1, pair<double, double> p2)
{
    double xDiff = p2.first - p1.first;
    double yDiff = p2.second - p1.second;
    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

// Function to check if three points make a non-left turn
bool isNonLeftTurn(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3)
{
    double crossProduct = (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);
    return crossProduct <= 0;
}

// Function to find the convex hull using the Graham scan algorithm
pair<vector<pair<double, double>>, int> grahamScan(vector<pair<double, double>>& points)
{
    int n = points.size();
    if (n < 3)
    {
        return { points, n };
    }
    pair<double, double> p0 = findLowestY(points);
    sort(points.begin(), points.end(), [&](pair<double, double> p1, pair<double, double> p2)
        {
            double angle1 = polarAngle(p0, p1);
            double angle2 = polarAngle(p0, p2);
            if (angle1 == angle2) {
                return distance(p0, p1) < distance(p0, p2);
            }
            return angle1 < angle2; });
    vector<pair<double, double>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    for (int i = 2; i < n; i++)
    {
        while (hull.size() >= 2 && isNonLeftTurn(hull[hull.size() - 2], hull[hull.size() - 1], points[i]))
        {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return { hull, hull.size() };
}

// ---MAIN----------------------------------------------------------------------
int main()
{
    vector<pair<double, double>> points = randomInput(300);
    pair<vector<pair<double, double>>, int> result = grahamScan(points);
    cout << "Convex hull points: ";
    for (auto p : result.first)
    {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl
        << "Total number of points in the convex hull: " << result.second << endl;

    // Clean up data.csv file and write all points from the last run to it.
    // Denote points in the convex hull with their index in the result vector in
    // 'hull' column. The non-hull points are denoted with -1.
    ofstream data;
    data.open("data.csv", ofstream::out | ofstream::trunc);
    data << "x,y,hull" << endl;
    for (auto p : points)
    {
        int defIndex = -1;
        for (int i = 0; i < result.first.size(); i++)
        {
            if (p == result.first[i])
            {
                defIndex = i;
                break;
            }
        }
        if (defIndex == -1)
        {
            data << p.first << "," << p.second << ",-1" << endl;
        }
        else
        {
            data << p.first << "," << p.second << "," << defIndex << endl;
        }
    }
    data.close();

    // Call python script to plot the points
    system("python plot.py");
    return 0;
}