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
outFile.open("transit_report.txt");
//Error: ridership.txt not found. Exiting. would happen if the file was incorrectly named
//like in the excercise

//reading and proccessing all 90 values
int value, counter = 0;
int currentRoute, currentDay;

//Total sums for each route
int aTotal = 0;
int bTotal = 0;
int cTotal = 0;

//Best and worst days
int abestDay = 0, bbestDay = 0, cbestDay = 0;
int aworstDay = 0, bworstDay = 0, cworstDay = 0;
//Best and worst values
int abestValue = 0, bbestValue = 0, cbestValue = 0;
int aworstValue = 1000, bworstValue = 1000, cworstValue = 1000;


while (inFile >> value){
    currentRoute = counter / DAYS_PER_ROUTE;     // counter increases until it is above the 30 day mark, then it outputs 1, then 2 (ex. 65/30 = 2 which is route C)
    currentDay   = counter % DAYS_PER_ROUTE;     // counter / DAYS_PER_ROUTE remainder (ex. 17/30 = 17 remainder)
    counter++;

        //Sums of all the route values
        if (currentRoute == 0) {
            aTotal += value; 
        } 
        else if (currentRoute == 1) {
            bTotal += value;
        }
        else if (currentRoute == 2) {
            cTotal += value;
        }

        //Finding the best and worst days/values for all the routes
            //bestdays
        if (currentRoute == 0 && abestValue < value) {
            abestValue = value;
            abestDay = currentDay + 1;
        }
        if (currentRoute == 1 && bbestValue < value) {
            bbestValue = value;
            bbestDay = currentDay + 1;
        }
        if (currentRoute == 2 && cbestValue < value) {
            cbestValue = value;
            cbestDay = currentDay + 1;
        }


            //worst days
        if (currentRoute == 0 && aworstValue > value) {
            aworstValue = value;
            aworstDay = currentDay + 1;
        }
        if (currentRoute == 1 && bworstValue > value) {
            bworstValue = value;
            bworstDay = currentDay + 1;
        }
        if (currentRoute == 2 && cworstValue > value) {
            cworstValue = value;
            cworstDay = currentDay + 1;
        }
    }


//Route daily averages:
double aAverage = static_cast<double>(aTotal) / DAYS_PER_ROUTE;
double bAverage = static_cast<double>(bTotal) / DAYS_PER_ROUTE;
double cAverage = static_cast<double>(cTotal) / DAYS_PER_ROUTE;
//Total and average of all routes:
int allTotal = aTotal + bTotal + cTotal;
double totalAverage = static_cast<double>(allTotal) / TOTAL_VALUES;

//commas
string totalText = to_string(allTotal);
totalText.insert(totalText.length() - 3, ",");
string aText = to_string(aTotal);
aText.insert(aText.length() - 3, ",");
string bText = to_string(bTotal);
bText.insert(bText.length() -3, ",");
string cText = to_string(cTotal);
cText.insert(cText.length() - 3, ",");



// THE REPORT
// 
//track total riders, daily average, busiest day, slowest day


cout << "================================================" << "\n";
cout << setw(48) << "REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT" << "\n";
cout << "================================================" << "\n";
cout << "Route          Total      Daily Avg   Peak Day   Low Day" << "\n";
cout << "------------------------------------------------" << "\n";
cout << "Route A" << setw(13) << aText << setw(13) << setprecision(1) << fixed << aAverage << setw(10) << "Day " << abestDay << setw(8) << "Day " << aworstDay << "\n";
cout << "Route B" << setw(13) << bText << setw(13) << setprecision(1) << fixed << bAverage << setw(10) << "Day " << bbestDay << setw(8) << "Day " << bworstDay << "\n";
cout << "Route C" << setw(13) << cText << setw(13) << setprecision(1) << fixed << cAverage << setw(10) << "Day " << cbestDay << setw(8) << "Day " << cworstDay << "\n";
cout << "------------------------------------------------" << "\n";
cout << "TOTAL" << setw(13) << totalText << setw(15) << totalAverage << " passengers/day" << "\n";
cout << "================================================" << "\n";
cout << "Report saved to: transit_report.txt" << "\n";

outFile << "================================================" << "\n";
outFile << setw(46) << "REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT" << "\n";
outFile << "================================================" << "\n";
outFile << "Route          Total      Daily Avg   Peak Day   Low Day" << "\n";
outFile << "------------------------------------------------" << "\n";
outFile << "Route A" << setw(13) << aText << setw(13) << setprecision(1) << fixed << aAverage << setw(10) << "Day " << abestDay << setw(8) << "Day " << aworstDay << "\n";
outFile << "Route B" << setw(13) << bText << setw(13) << setprecision(1) << fixed << bAverage << setw(10) << "Day " << bbestDay << setw(8) << "Day " << bworstDay << "\n";
outFile << "Route C" << setw(13) << cText << setw(13) << setprecision(1) << fixed << cAverage << setw(10) << "Day " << cbestDay << setw(8) << "Day " << cworstDay << "\n";
outFile << "------------------------------------------------" << "\n";
outFile << "TOTAL" << setw(13) << totalText << setw(15) << totalAverage << " passengers/day" << "\n";
outFile << "================================================" << "\n";
outFile << "Report saved to: transit_report.txt" << "\n";
outFile.close();
inFile.close();
}



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




//excercise 2
//gives a error and exits because file name is incorrect

//excercise 3
//counter reaches 91 because the while loop will still try to work one extra iteration since the end of file is not set until a read attempt fails.
//while (inFile >> value) only reads until there's no more values