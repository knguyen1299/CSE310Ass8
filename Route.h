//********************************************************************
// ASU CSE310 Assignment #8 Fall 2024
// Name of Author: Kevin Nguyen
// ASU ID: 1212799807
// Description: The header file is used to model a graph that connects
// the sites and routes to handle both vertices and edges.
//********************************************************************
#ifndef ROUTE_H
#define ROUTE_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Site represents one vertex of the map
using namespace std;

struct Site
{
    string siteName;  // Name of the site
    int rank;         // Used for union by rank heuristic
    struct Site* parent;  // Pointer to the parent site (used in union-find structure)

    // Default constructor
    Site() : siteName(""), rank(0), parent(this) {
        // Initializing siteName to empty string, rank to 0, and parent to itself
    }

    // Overloaded constructor with site name
    Site(string name) : siteName(name), rank(0), parent(this) {
        // Initializing siteName to the provided name, rank to 0, and parent to itself
    }
};


//Route represents one edge of the map which connects two historical sites of Rome
class Route
{
    private:
       struct Site* site1;
       struct Site* site2;
       double distance;

	public:
	   Route();
       Route(Site* site1, Site* site2, double distance);
       Site* getSite1();
       Site* getSite2();
       double getDistance() const;
       void printRoute();
};

//finish each function according to above definition
//----
//----
// Default constructor
Route::Route() : site1(nullptr), site2(nullptr), distance(0.0) {
    // Initialize site1 and site2 to nullptr and distance to 0.0
}

// Parameterized constructor
Route::Route(Site* site1, Site* site2, double distance) : site1(site1), site2(site2), distance(distance) {
    // Initialize site1, site2, and distance with the provided values
}

// Getter for site1
Site* Route::getSite1() {
    return site1;  // Return the first site
}

// Getter for site2
Site* Route::getSite2() {
    return site2;  // Return the second site
}

// Getter for distance
double Route::getDistance() const {
    return distance;  // Return the distance of the route
}

void Route::printRoute()
{
    cout << left;
    cout << setw(33) << site1->siteName
         << setw(8) << "<--->"
         << setw(33) << site2->siteName
         << setw(3) << " = "
         << setw(8) << right << fixed << setprecision(1) << getDistance()
         << endl;
}
#endif
