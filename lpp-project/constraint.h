#ifndef constraint_H_
#define constraint_H_

#include "utilities.h"
using namespace std;


/**
 * Header file for constraint data type
 */

class Constraint : public LPP
{
public:
    vector<vector<fraction>> constraints{{20 ,50}, {80, 50}};

    /**
     * @condition: -1 : <=
     *              0 : =
     *              1 : >=
     */
    vector<int> constype{-1,1}; //type of constraints ,have to determine constraint type from the user input
    /**
     * What does function do: Displays the constraints in equation form.
     * Example: 2x1 + 3x2 = 4
     * @param res : resource vector
     */
    void display(vector<fraction> res)
    {
        for (int i = 0; i < constraints.size(); ++i)
        {
            for (int j = 0; j < constraints[i].size(); ++j)
            {
                if (j < (constraints[i].size() - 1))
                    cout << constraints[i][j] << "x" << j + 1 << " + ";
                else
                    cout << constraints[i][j] << "x" << j + 1 << " = " << res[i];
            }
            cout << "\n";
        }
    }

    /**
     * Adds slack or surplus variable in constraint according to
     * type of constraint. This basically converts the constraint
     * into standard form.
     */
    void SlackSurp(vector<fraction> &objective, int problemType = 1)
    {
        for (int i = 0; i < constraints.size(); ++i)
        {
            if (constype[i] == -1) // -1 : <= enequality
            {
                addZeros(i, 1);         //adds zero for slack var in all except current constraints
                objective.push_back(0); //0 for current slack var
            }
            else if (constype[i] == 1) // 1 : >= enequality
            {
                addZeros(i, -1);        //adds zero for surplus var in all except current constraints
                objective.push_back(0); //0 for current surplus var
                addZeros(i, 1);         //adds zero for artificial var in all except current constraints
                if (problemType == 0)
                    objective.push_back(-1000); //M=1000 for current Artificial var
                else
                    objective.push_back(1000); //M=1000 for current Artificial var
            }
            else
            {
                addZeros(i, 1); //adds zero for artificial var in all except current constraints
                if (problemType == 0)
                    objective.push_back(-1000); //M=1000 for current Artificial var
                else
                    objective.push_back(1000); //M=1000 for current Artificial var
            }
        }
    }

    /**
     * Adds zero in place of slack surplus variables
     * not present in the current constraint.
     * @param index: which constraint out of all is being edited
     * @param coefficient: coefficient to be added in current constraint
     */
    void addZeros(int index, int coefficient)
    {
        for (int i = 0; i < constraints.size(); ++i)
        {
            if (i == index)
                constraints[index].push_back(coefficient);
            else
                constraints[i].push_back(0);
        }
    }
};

class Resource : public LPP
{
public:
    vector<fraction> reso{48, 72}; //stores resource coefficient
};

#endif