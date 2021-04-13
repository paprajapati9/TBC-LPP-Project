#include "utilities.h"
using namespace std;

/**
 * TESTING PROBLEM
 * MAX z= 2x1+3x2
 *  S.to x1+2X2 <= 2
 *       2x2 +x1<=3
 * x1,x2>=0
*/

/**
 * TESTING PROBLEM BIG-M
 * MAX z= 1x1+5x2
 *  S.to 4x1 + 5x2 <= 6
 *       1x1 + 3x2 >= 2
 * x1,x2>=0
 */ 


int main()
{
    int choice;
    cout << "\t\t\t  * LPP Solver *\n\n\n";
    Constraint c;
    Objective o;
    Resource r;
    cout << "Which type of problem is it? Press '1' for Maximization and '0' for Minimization." << endl;
    cin >> choice;

    o.setProblemType(choice); //set min/max problem type
    o.Insert();
    c.SlackSurp(o.objective);
    o.display();
    cout << "Subject To: \n";
    c.display(r.reso);
    cout << endl;

    bigM_zrow(o.objective, c.constraints, c.constype, r.reso, c.optimalSolution);

    //Check initial basic variables
    c.checkBasic(c.constraints, o.objective, r.reso);

    // int a = c.checkOptimality(o.objective);
    int optimalCondition = c.checkOptimality(o.objective);
    while (not optimalCondition)
    {
        c.checkEnteringVar(o.objective);
        c.checkleavingVariable(r.reso, c.constraints);
        c.setPivot(c.constraints);
        c.newPivotRow(c.constraints, r.reso);
        c.newRow(c.constraints, o.objective, r.reso);
        optimalCondition = c.checkOptimality(o.objective);
        cout << endl;
    }

    if (choice == 0)
    {
        cout << "Optimal Solution for Max problem is  : " << c.optimalSolution << endl
             << endl;
        cout << "\nFinal basic variables are: \n";
        c.displayBasicVariables(r.reso);
        cout << "Final Optimal Solution is : " << c.temp << endl
             << endl;
    }
    else
    {
        cout << "Final basic variables are: \n";
        c.displayBasicVariables(r.reso);
        cout << "Optimal Solution is : " << c.optimalSolution << endl
             << endl;
    }

    cout<<"Press any key to exit";
    getchar();
}