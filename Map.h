//********************************************************************
// ASU CSE310 Assignment #8 Fall 2024
// Name of Author: Kevin Nguyen
// ASU ID: 1212799807
// Description: This is the header file that defines an undirected graph
//              with an array of sites and routes that manages a the
// historical sites and routes between them and implements the Kruskals 
// algorithm to compute MST.
//********************************************************************

#ifndef MAP_H
#define MAP_H

#include "Route.h"  // Include Route.h for the Route and Site classes
#include <iostream>
#include <algorithm>
#include <iomanip>  // For output formatting

using namespace std;

class Map {
private:
    int numOfSites, numOfRoutes;
    Site* setOfSites;
    Route* setOfRoutes;

public:
    Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray) 
        : numOfSites(numOfSites), numOfRoutes(numOfRoutes), setOfSites(siteArray), setOfRoutes(routeArray) {}

    void make_set(Site* oneSite) {
        oneSite->parent = oneSite;
        oneSite->rank = 0;
    }

    Site* find_set(Site* oneSite) {
        if (oneSite != oneSite->parent) {
            oneSite->parent = find_set(oneSite->parent);
        }
        return oneSite->parent;
    }

    void link(Site* aSite, Site* bSite) {
        if (aSite->rank > bSite->rank) {
            bSite->parent = aSite;
        } else if (aSite->rank < bSite->rank) {
            aSite->parent = bSite;
        } else {
            bSite->parent = aSite;
            aSite->rank++;
        }
    }

    void Union(Site* aSite, Site* bSite) {
        link(find_set(aSite), find_set(bSite));
    }

    void sortRoutes() {
        for (int i = 0; i < numOfRoutes - 1; ++i) {
            for (int j = i + 1; j < numOfRoutes; ++j) {
                if (setOfRoutes[i].getDistance() > setOfRoutes[j].getDistance()) {
                    swap(setOfRoutes[i], setOfRoutes[j]);
                }
            }
        }
    }

    void MST_Kruskal() {
        cout << "\nMST Kruskal Algorithm Result\n" << endl;
        double totalDistance = 0.0;

        sortRoutes();

        for (int i = 0; i < numOfSites; ++i) {
            make_set(&setOfSites[i]);
        }

        for (int i = 0; i < numOfRoutes; ++i) {
            Site* fromSite = setOfRoutes[i].getSite1();
            Site* toSite = setOfRoutes[i].getSite2();
            double distance = setOfRoutes[i].getDistance();

            if (find_set(fromSite) != find_set(toSite)) {
                Union(fromSite, toSite);
                totalDistance += distance;
                setOfRoutes[i].printRoute();
            }
        }

        cout << "=====================================================================================" << endl;
        cout << "Total Distance: " << totalDistance << " meters" << endl;
    }
};


#endif // MAP_H
