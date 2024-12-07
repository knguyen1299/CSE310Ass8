//************************************************************************
// ASU CSE310 Assignment #8 Fall 2024
// ASU ID: 1212799807
// Name: Kevin Nguyen 
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph. Each site is a vertex and each route between sites is an edge
// and processes the information to construct a graph.
//**************************************************************************

//include necessary header file
//----
#include <iostream>  // For input/output operations (cin, cout, getline)
#include <string>    // For using string objects and string manipulation
#include "Route.h"   // Your custom header for the Route class
#include "Map.h"
using namespace std;

void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance);
const int MAX_DESTINATIONS = 10;  // Adjust as needed

int main() {
    const int MAX_SITE_NUM = 50, MAX_ROUTE_NUM = 100;
    int numOfSites = 0, numOfRoutes = 0;

    Site* siteArray = new Site[MAX_SITE_NUM];
    Route* routeArray = new Route[MAX_ROUTE_NUM];

    string oneLine;
    getline(cin, oneLine);

    while (oneLine.compare("End") != 0) {
        string siteName;
        size_t commaPos = oneLine.find(',');

        siteName = oneLine.substr(0, commaPos);  // Extract the site name

        Site* site1 = nullptr;
        bool siteFound = false;
        
        for (int i = 0; i < numOfSites; ++i) {
            if (siteArray[i].siteName == siteName) {
                site1 = &siteArray[i];
                siteFound = true;
                break;
            }
        }
        
        if (!siteFound) {
            siteArray[numOfSites] = Site(siteName);
            site1 = &siteArray[numOfSites];
            numOfSites++;
        }

        string remainingLine = oneLine.substr(commaPos + 1);
        size_t nextCommaPos;
        
        while ((nextCommaPos = remainingLine.find(',')) != string::npos) {
            string destinationSite = remainingLine.substr(0, nextCommaPos);
            size_t leftParen = destinationSite.find('(');
            size_t rightParen = destinationSite.find(')');

            // Ensure that both parentheses exist and the string between them is a valid number
            if (leftParen != string::npos && rightParen != string::npos) {
                // Extract the substring between the parentheses (the distance)
                string distanceStr = destinationSite.substr(leftParen + 1, rightParen - leftParen - 1);

                try {
                    // Convert the distance to double
                    double distance = stod(distanceStr);

                    string destinationName = destinationSite.substr(0, leftParen);

                    Site* site2 = nullptr;
                    bool destinationFound = false;
                    for (int i = 0; i < numOfSites; ++i) {
                        if (siteArray[i].siteName == destinationName) {
                            site2 = &siteArray[i];
                            destinationFound = true;
                            break;
                        }
                    }
                    
                    if (!destinationFound) {
                        siteArray[numOfSites] = Site(destinationName);
                        site2 = &siteArray[numOfSites];
                        numOfSites++;
                    }

                    // Create a route and add it to the route array
                    routeArray[numOfRoutes] = Route(site1, site2, distance);
                    numOfRoutes++;
                } catch (const std::invalid_argument& e) {
                    // Handle invalid distance format
                    cerr << "Invalid distance format: " << distanceStr << endl;
                } catch (const std::out_of_range& e) {
                    // Handle out of range distance
                    cerr << "Distance out of range: " << distanceStr << endl;
                }
            }

            // Remove the processed part of the string
            remainingLine = remainingLine.substr(nextCommaPos + 1);
        }

        getline(cin, oneLine);
    }

    Map myMap(numOfSites, numOfRoutes, siteArray, routeArray);

    cout << "Total historical sites you will visit: " << numOfSites << endl;

    myMap.MST_Kruskal();

    delete[] siteArray;
    delete[] routeArray;

    return 0;
}



//****************************************************************
//By giving a string, for example 'Pantheon(300.5)', this function
//extract the arrival site name 'Pantheon' and distance '300.5' meters
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrSiteInfo(const std::string& oneLine, std::string& sourceSite, 
                    std::string destinationSites[MAX_DESTINATIONS], 
                    double distances[MAX_DESTINATIONS], int& destinationCount) {
    size_t commaPos = oneLine.find(',');

    // Extract the source site name (everything before the first comma)
    sourceSite = oneLine.substr(0, commaPos);

    std::string remainingLine = oneLine.substr(commaPos + 1);  // Get the remaining part (routes)
    size_t nextCommaPos;
    destinationCount = 0;  // Reset the destination count

    // Process the remaining part to extract destination sites and distances
    while ((nextCommaPos = remainingLine.find(',')) != std::string::npos && destinationCount < MAX_DESTINATIONS) {
        std::string destinationSite = remainingLine.substr(0, nextCommaPos);
        size_t leftParen = destinationSite.find('(');
        size_t rightParen = destinationSite.find(')');

        // Ensure that both parentheses exist and the string between them is a valid number
        if (leftParen != std::string::npos && rightParen != std::string::npos) {
            // Extract the substring between the parentheses (the distance)
            std::string distanceStr = destinationSite.substr(leftParen + 1, rightParen - leftParen - 1);

            try {
                // Convert the distance to double
                double distance = std::stod(distanceStr);

                // Extract the destination site name
                std::string destinationName = destinationSite.substr(0, leftParen);

                // Add the destination site and distance to the arrays
                destinationSites[destinationCount] = destinationName;
                distances[destinationCount] = distance;
                destinationCount++;  // Increment the destination count
            } catch (const std::invalid_argument& e) {
                // Handle invalid distance format
                std::cerr << "Invalid distance format: " << distanceStr << std::endl;
            } catch (const std::out_of_range& e) {
                // Handle out of range distance
                std::cerr << "Distance out of range: " << distanceStr << std::endl;
            }
        }

        // Remove the processed part of the string
        remainingLine = remainingLine.substr(nextCommaPos + 1);
    }
}
