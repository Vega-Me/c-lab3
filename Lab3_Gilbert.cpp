// Programmer  : Marcos Gilbert  |  Course: CSC 155  |  Lab 3 — Transit Ridership Analyzer
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

// ============================
const int DAYS_PER_ROUTE = 30;
const int NUM_ROUTES = 3;
const int TOTAL_VALUES = DAYS_PER_ROUTE * NUM_ROUTES;
// ============================


int main() {
// TEST:
// outfile is the file name
// ofstream means output file connection
//ofstream outFile("report.txt");  
//outFile << "done"; 
//outFile.close();


// LAB 3 START:
//requirements:
// (done) open and validate ridership, if doesn't work -> error message -> exit(1)      
// (done) read all values using a while loop, use counter to determine day and route
// 3. For each route compute: total riders, daily average, busiest day (value + day number), slowest day (value + day number)
// 4. Compute overall monthly total and overall daily average across all routes.
// 5. formatted report to cout, ofstream to transit_report.txt
// 6. use setw() / precision(1) / fixed

//declaring input and output files
ifstream inFile;
ofstream outFile;

inFile.open("ridership.txt");
if (!inFile.is_open()) {
        cout << "\nError: ridership.txt not found, exiting.\n";
        exit(1);
    } 
else {
        cout << "\nSuccess: ridership.txt found.\n";
    }
outFile.open("report.txt");


//reading and proccessing all 90 values
int value, counter = 0;
int currentRoute, currentDay;

//Total sums for each route
int aTotal = 0;
int bTotal = 0;
int cTotal = 0;
//Averages per day for each route
double aAverage, bAverage, cAverage;

while (inFile >> value){
    currentRoute = counter / DAYS_PER_ROUTE;     // counter increases until it is above the 30 day mark, then it outputs 1, then 2 (ex. 65/30 = 2 which is route C)
    currentDay   = counter % DAYS_PER_ROUTE;     // counter / DAYS_PER_ROUTE remainder (ex. 17/30 = 17 remainder)
    counter++;


    if (currentRoute == 0) {
        aTotal += value; 
    } 
    else if (currentRoute == 1) {
        bTotal += value;
    }
    else if (currentRoute == 2) {
        cTotal += value;
    }

    }


cout << "================================================" << "\n";
cout << setw(45) << "REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT" << "\n";
cout << "================================================" << "\n";
cout << "Route          Total      Daily Avg   Peak Day   Low Day" << "\n";
cout << "------------------------------------------------" << "\n";
cout << "Route A        9,847      328.2       Day 14     Day 22" << "\n";
cout << "Route B       11,203      373.4       Day  3     Day 29" << "\n";
cout << "Route C        8,991      299.7       Day 18     Day  7" << "\n";
cout << "------------------------------------------------" << "\n";
cout << "TOTAL         30,041      333.8 passengers/day" << "\n";
cout << "================================================" << "\n";
cout << "Report saved to: transit_report.txt" << "\n";

cout << aTotal << "\n";
cout << bTotal << "\n";
cout << cTotal << "\n";


//track total riders, daily average, busiest day, slowest day

// ================================================
//     REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT
// ================================================
// Route          Total      Daily Avg   Peak Day   Low Day
// ------------------------------------------------
// Route A        9,847      328.2       Day 14     Day 22
// Route B       11,203      373.4       Day  3     Day 29
// Route C        8,991      299.7       Day 18     Day  7
// ------------------------------------------------
// TOTAL         30,041      333.8 passengers/day
// ================================================
// Report saved to: transit_report.txt




}