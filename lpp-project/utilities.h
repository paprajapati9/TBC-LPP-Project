#ifndef utilities_H_
#define utilities_H_
#include <iostream>
#include <vector>
#include <iomanip>
#include "fraction.h"
#include "lpp.h"
#include "constraint.h"
#include "objective.h"
using namespace std;
const char separator = ' ';
const int numWidth = 12;


/**
 * Header file for utilities
 */


/**
 * @param dv: Vector containing int type data values.
 * displayVector function prints all the elements
 * of the given vector
*/
void displayVector(vector<int> dv)
{
    for (int i = 0; i < dv.size(); i++)
    {
        cout << left <<setw(10)<<setfill(separator)<<dv[i];
    }
    cout << endl;
}

// Overloaded displayVector to display a vector containing fraction type data
void displayVector(vector<fraction> dv, fraction resourse)
{
    for (int i = 0; i < dv.size(); i++)
    {   
        cout<<setw(numWidth)<<setfill(separator)<<dv[i];
    }
    cout<<setw(numWidth)<<setfill(separator)<<resourse;
    cout << endl;
}


void displayinitialtable(vector<fraction> object, fraction sol, vector<vector<fraction>> constr, vector<fraction> resi, vector<int> basics)
{
    cout << left << setw(numWidth) << "Basic";
    for (int i = 1; i <= 5; i++)
        cout <<"x"<<setw(numWidth-1)<< i;
    cout << "Solution\n";
    cout<< setw(numWidth+1)<< "Z";
    displayVector(object, sol); // display new objective row element

    for (int j = 0; j < constr.size(); j++)
    {
        cout <<"x"<< left << setw(numWidth) <<setfill(separator)<< basics[j] + 1;
        displayVector(constr[j], resi[j]);
    }
}

void displayTable(vector<fraction> object ,fraction sol,vector<vector<fraction>> constr,vector<fraction> resi, vector <int> basics, int enteringVariable, int leavingVariable)
{
    cout<<left<<setw(numWidth-1)<<"Basic";
    for(int i = 1; i <= 5; i++) cout<<left<<setw(numWidth)<<"x"+to_string(i);
    cout<<"Solution\n";
    cout<<left<<setw(numWidth)<<setfill(separator)<<"Z";
    displayVector(object, sol); // display new objective row element
    for (int j = 0; j < constr.size(); j++) // Calcute new Constraint element
    {
        if (j == leavingVariable) // skip leaving row elements i.e already change in new pivot row function
        {   
            cout<<"x"<<left<<setw(numWidth-1)<<basics[leavingVariable]+1;
            // Displaying Basic Variable Value
            displayVector(constr[leavingVariable], resi[leavingVariable]);
            continue;
        }
        cout<<"x"<<left<<setw(numWidth-1)<<basics[j]+1;
        // Displaying Basic Variable Value
        displayVector(constr[j], resi[j]); // display new constraint vector
    }
}       

void bigM_zrow(vector<fraction> &objective, vector<vector<fraction>> constraints, vector<int> constype, vector<fraction> &reso, fraction &optimalSolution)
{
    // New z row = old z row + (1000*R1 row + 1000*R2 row)

    for (int i = 0; i < constype.size(); i++)
    {
        for (int j = 0; j < objective.size(); j++)
        {
            if (constype[i] == 1)
            {
                objective[j] = objective[j] + (-1000 * constraints[i][j]);
            }
        }
        
        if (constype[i] == 1)
        {
            optimalSolution = optimalSolution + ((-1000) * reso[i]);
        }
    }
}

#endif