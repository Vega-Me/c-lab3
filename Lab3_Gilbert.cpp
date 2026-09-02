// Programmer  : Marcos Gilbert  |  Course: CSC 155  |  Lab 3 — Transit Ridership Analyzer
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
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
// (done) For each route compute: total riders, daily average, busiest day (value + day number), slowest day (value + day number)
// (done) Compute overall monthly total and overall daily average across all routes.
// (done) formatted report to cout, ofstream to transit_report.txt
// (done) use setw() / precision(1) / fixed

//declaring input and output files
ifstream inFile;
ofstream outFile;

inFile.open("ridership.txt");
if (!inFile.is_open()) {
    cout << "\nError: ridership.txt not found, exiting.\n";
    exit(1);
    } 
else {
    cout << "\nFile ridership.txt opened successfully.\n";
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
//Range of routes (peak - low)
int aRange = abestValue - aworstValue;
int bRange = bbestValue - bworstValue;
int cRange = cbestValue - cworstValue;
int totalRange = aRange;
if (totalRange < bRange) {
    totalRange = bRange;
}
if (totalRange < cRange) {
    totalRange = cRange;
}
//ridership percentage of each route
double aPercentage = static_cast<double>(aTotal) / allTotal * 100;
double bPercentage = static_cast<double>(bTotal) / allTotal * 100;
double cPercentage = static_cast<double>(cTotal) / allTotal * 100;
double totalPercentage = static_cast<double>(allTotal) / allTotal * 100; 

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


cout << "\n===============================================================================" << "\n";
cout << setw(63) << "REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT" << "\n";
cout << "===============================================================================" << "\n";
cout << "Route          Total            Daily Avg      Peak Day         Low Day    Range" << "\n";
cout << "-------------------------------------------------------------------------------" << "\n";
cout << "Route A" << setw(11) << aText << setprecision(1) << fixed << " (" << aPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< aAverage << setw(10) << "Day " << abestDay << " (" << abestValue << ")" << setw(10) << "Day " 
<< aworstDay << " (" << aworstValue << ")" << setw(5) << aRange << "\n";
cout << "Route B" << setw(11) << bText << " (" << bPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< bAverage << setw(10) << "Day " << bbestDay << " (" << bbestValue << ")" << setw(10) << "Day " 
<< bworstDay << " (" << bworstValue << ")" << setw(5) << bRange << "\n";
cout << "Route C" << setw(11) << cText << " (" << cPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< cAverage << setw(10) << "Day " << cbestDay << " (" << cbestValue << ")" << setw(10) << "Day " 
<< cworstDay << " (" << cworstValue << ")" << setw(5) << cRange << "\n";
cout << "-------------------------------------------------------------------------------" << "\n";
cout << "TOTAL" << setw(12) << totalText << " (" << totalPercentage << "%)" << setw(13) << totalAverage << " passengers/day" 
<< setw(25)<< totalRange << "\n";
cout << "===============================================================================" << "\n";
cout << "Report saved to: transit_report.txt" << "\n";

outFile << "\n===============================================================================" << "\n";
outFile << setw(63) << "REGIONAL TRANSIT AUTHORITY — MONTHLY REPORT" << "\n";
outFile << "===============================================================================" << "\n";
outFile << "Route          Total            Daily Avg      Peak Day         Low Day    Range" << "\n";
outFile << "-------------------------------------------------------------------------------" << "\n";
outFile << "Route A" << setw(11) << aText << setprecision(1) << fixed << " (" << aPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< aAverage << setw(10) << "Day " << abestDay << " (" << abestValue << ")" << setw(10) << "Day " 
<< aworstDay << " (" << aworstValue << ")" << setw(5) << aRange << "\n";
outFile << "Route B" << setw(11) << bText << " (" << bPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< bAverage << setw(10) << "Day " << bbestDay << " (" << bbestValue << ")" << setw(10) << "Day " 
<< bworstDay << " (" << bworstValue << ")" << setw(5) << bRange << "\n";
outFile << "Route C" << setw(11) << cText << " (" << cPercentage << "%)" << setw(13) << setprecision(1) << fixed 
<< cAverage << setw(10) << "Day " << cbestDay << " (" << cbestValue << ")" << setw(10) << "Day " 
<< cworstDay << " (" << cworstValue << ")" << setw(5) << cRange << "\n";
outFile<< "-------------------------------------------------------------------------------"<< "\n";
outFile << "TOTAL" << setw(12) << totalText << " (" << totalPercentage << "%)" << setw(13) << totalAverage << " passengers/day" 
<< setw(25)<< totalRange << "\n";
outFile<< "==============================================================================="<< "\n";
outFile << "Report saved to: transit_report.txt" << "\n";
outFile.close();
inFile.close();
}


//reference
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
// Error: ridership.txt not found, exiting. is the error message I get when changing the name of the file.

//excercise 3
//counter reaches 91 because the while loop will still try to work one extra iteration since the end of file is not set until a read attempt fails.
//while (inFile >> value) only reads until there's no more values


// — Creative Feature Documentation
//     What feature did you add and which lab did you extend?
//   I added a percentage of the totals to help visualize the routes. I also added a range of the riderships for each month and then I added a total range.
//     What did you learn about single-pass vs. multi-pass computation from the AI conversation? How did that shape your design?
//   I learned about how analyzing data is a lot more intuitve than I thought before, multi pass shaped my design helping me implement averages and ranges which are only
//   possible once the single step pass has happened.
//     Why did you choose this feature — what made it interesting or useful in the context of your lab's scenario?
//   It made it useful to help skip the trouble of having to see how inconsistent the month was for each route. In a real world scenario 
//   they would probably like to know which month was the least reliable for their ridership revenue.
//     What would you add next, and would it require storing the data or could it be computed in one pass?
//   Something I keep bringing up for all these labs is some way to visualize, chatgpt told me I would need to learn arrays and then how
//  to plot points which I do want to learn it's just much easier to time crunch when I'm doing the labs than it is outside of the labs

