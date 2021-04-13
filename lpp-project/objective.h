#ifndef objective_H_
#define objective_H_

#include "utilities.h"
using namespace std;

/**
 * Header file for objective data type
 */

class Objective: public LPP
{
    public:
    vector<fraction> objective; //stores objective coefficient.

    //Insert coefficient of objective function to objective vector.
    void Insert()
    {
        objective.push_back(-8);
        objective.push_back(-7);
    }

    /**
     * Displays Objective function.
     * If Min problem first displays Min objective then displays it after converting it into Max form.
     * By default objective parameters are negative .
     * @param coeff : stores the negative value of objective coefficient
     *                if it not equal to 0(to make them positive) otherwise
     *                it stores 0 as it is.
     * Adds '+' between each objective variable except the last one.
     */
    void display()
    {
        fraction coeff;
        cout << "* LPP Problem *\n\n";
        if (problemType == 1)
        {
            cout << "Max Z = ";
            for (int j = 0; j < objective.size(); j++)
            {

                coeff = (objective[j] != 0) ? (objective[j] * (-1)) : 0;
                // the objective function to be displayed should be in positive form thus we are multiplying by -1
                if (j < (objective.size() - 1))
                {
                    cout << coeff << "x" << j + 1 << " + ";
                }
                else
                {
                    cout << coeff << "x" << j + 1;
                }
            }
        }
        else
        {
            cout << "Min Z = ";
            for (int j = 0; j < objective.size(); j++)
            {
                coeff = (objective[j] != 0) ? (objective[j] * (-1)) : 0;
                // the objective function to be displayed should be in positive form thus we are multiplying by -1
                if (j < (objective.size() - 1))
                {
                    cout << coeff << "x" << j + 1 << " + ";
                }
                else
                {
                    cout << coeff << "x" << j + 1;
                }
            }

            //Converting Minization problem to Maximization problem.
            cout << endl
                 << "Converting the Objective function into Maximization form" << endl;
            cout << "Max (-Z) = ";
            for (int j = 0; j < objective.size(); j++)
            {
                coeff = (objective[j] != 0) ? (objective[j]) : 0;
                if (j < (objective.size() - 1))
                {
                    cout << coeff << "x" << j + 1 << " + ";
                }
                else
                {
                    cout << coeff << "x" << j + 1;
                }
            }
        }
        cout << "\n\n";
    }
};

#endif