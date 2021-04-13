#ifndef LPP_H_
#define LPP_H_

#include "utilities.h"
using namespace std;

void displayVector(vector<int>);
void displayVector(vector<fraction>, fraction);
void displayinitialtable(vector<fraction>,fraction,vector<vector<fraction>>,vector<fraction>,vector <int>);
void displayTable(vector<fraction>,fraction,vector<vector<fraction>>,vector<fraction>,vector <int>, int, int);

class LPP
{
public:
    fraction optimalSolution{}; //stores optimal solution at each simplex table
    fraction temp;              //stores the optimal solution of Max problem for later conversion to Min .
    int enteringVariable{};   //stores index of the entering variable in indexOfBasic vector
    int leavingVariable{};    //stores index of the entering variable in objective vector
    int problemType;          //stores index of the entering variable in objective vector
    fraction pivotElement;      //stores value of the pivot element at each simplex table
    vector<int> indexOfBasic; //stores index of current basic variables in objective vector

    void setProblemType(int probType)
    {
        problemType = probType;
    }

    /**
     * Checks initial basic variables  by reading the constraints
     * and adds thier variable in indexOfBaisc vector.
     * @param constraint: 2D constraints vector.
     */
    void checkBasic(vector<vector<fraction>> constraint, vector<fraction> objective, vector<fraction> resource)
    {
        fraction BasicInt{};
        int flag{1};
        // i will denote the column of the table
        for (int i = 0; i < constraint[0].size(); i++)
        {
            // j will denote the row of the table
            BasicInt = 0;
            flag = 1;
            for (int j = 0; j < constraint.size(); j++)
            {
                if (constraint[j][i] < 0)
                    flag = 0;
                BasicInt = BasicInt + constraint[j][i];
            }
            if (flag && (BasicInt == 1))
                indexOfBasic.push_back(i);
        }
        displayinitialtable(objective, optimalSolution, constraint, resource, indexOfBasic);
    }

    void displayBasicVariables(vector<fraction> resource)
    {

        for (int i = 0; i < indexOfBasic.size(); i++)
        {
            cout << "x" << indexOfBasic[i] + 1 << " : " << resource[i] << endl;
        }
    }

    /**
     * Checks for the most negative/positive element in the Z-row
     * based on type of lpp problem max/min.
     * @param objRow: Objective row vector.
     * By default problem type is 1 that is maximizarion problem.
     */
    int checkEnteringVar(vector<fraction> objRow, int problemType = 1)
    {
        int enteringVarIndex = 0;
        for (int i = 0; i < objRow.size(); i++)
        {
            if (objRow[i] < objRow[enteringVarIndex])
                enteringVarIndex = i;
            // else
            // {
            //     if (objRow[i] > objRow[enteringVarIndex])
            //         enteringVarIndex = i;
            // }
        }
        enteringVariable = enteringVarIndex;
        cout << "Entering variable is: x" << enteringVariable + 1 << endl;
        return enteringVariable;
    }

    /**
     * @param res: Resource Vector
     * @param constraint: 2D constraint Vector
     * Takes resource and constraint vectors and prints leaving variable
     * declaring and initialisation var to store minimum ratio
     * a variable which will store all ratios
     * to calculate the ratios we have to select particular entries of the rows ,
     * so we need this variable to store index of  the same.
     * We make use of a for loop which starts from zero to size of res vector,
     * then we pass it through a if block which checks whether it is greater than zero or not.
     * if it is >0 ratio is calculated.
     * Another if block determine the least of ratios obtained and assign it as min
     * ratio and the corresponding value of "i" is given to leaving variable and then
     * we print the leaving variable
     */
    int checkleavingVariable(vector<fraction> reso, vector<vector<fraction>> constraint)
    {
        fraction min_ratio = 0;
        fraction ratio;
        fraction currentVar;
        for (int i = 0; i < reso.size(); i++)
        {
            currentVar = constraint[i][enteringVariable];
            if (currentVar > 0)
            {
                ratio = reso[i] / currentVar;
                if (min_ratio == 0 || ratio < min_ratio)
                {
                    min_ratio = ratio;
                    leavingVariable = i;
                }
            }
        }
        cout << "Leaving variable is: x" << indexOfBasic[leavingVariable] + 1 << endl; //printing leaving variable.
        int returnLeave = indexOfBasic[leavingVariable];
        indexOfBasic[leavingVariable] = enteringVariable;
        return returnLeave;
    }

    /**
     * Sets the pivot element from the constraints vector
     * based on entering and leaving variable indexes
     * @param constraints: 2D vector of all constraints
     */
    void setPivot(vector<vector<fraction>> constraints)
    {
        pivotElement = constraints[leavingVariable][enteringVariable];
        cout << "Pivot element is: " << pivotElement << endl<<endl;
    }

    /**
     * The optimality is acheived if every element in the objective row is greater than 0 for maximization problem here
     * The vector objective stores the Z row elements of the problem for every iteration.
     * We run a loop to check for every element in the vector objective.
     * If all the elements of the vector objective or the Z row are greater than 0, the optimality has reached.
     * If even any one element is not positive, the program continues.
     * @param objective: Objective function vector
     *
     * @return bool: 0 for not optimal and 1 for optimal
     */
    bool checkOptimality(vector<fraction> objective)
    {
        cout << "\nChecking Optimality...\n";

        for (int i = 0; i < objective.size(); i++)
        {
            if (objective[i] < 0)
            {
                cout << "Optimality not reached\n\n";
                return 0;
            }
        }

        cout << "Optimality reached" << endl;
        return 1;
    }

    /**
    * @param reso: resource vector
    * what does Function? : change elements of old pivot row for next table
    * According to formula : New pivot row = Current pivot row / Pivot element
    * initially it convert the resource element of old pivot row by dividing it by pivotElement
    * and then convert every element of constraint of old pivot row in a for loop by dividing by pivotElement
    */
    void newPivotRow(vector<vector<fraction>> &constraints, vector<fraction> &reso)
    {
        reso[leavingVariable] = reso[leavingVariable] / pivotElement;
        for (int i = 0; i < constraints[leavingVariable].size(); i++)
        {
            constraints[leavingVariable][i] = constraints[leavingVariable][i] / pivotElement;
        }
    }

    /**
    * Function newRow
    * What does function do?
    * This function create the new rows of next tabel after calculation of new pivot row
    * According to Formula :   New row element = (Current row element) - (Pivot column coefficient) * (New pivot row coefficient)
    * @param constraint : old constraint 2D vector
    * @param reso : old resource vector
    * @param objective : objective vector
    */
    void newRow(vector<vector<fraction>> &constraints, vector<fraction> &objective, vector<fraction> &reso)
    {
        fraction multFactor = 1; //used as a new pivot row coefficient

        for (int j = 0; j < reso.size(); j++)
        {
            if (j == leavingVariable) //skip element at index - leaving variable  i.e pivot row
                continue;             // Reason to skip: already change happend in new pivot row function ie. new pivot row cofficient

            multFactor = constraints[j][enteringVariable] * (-1); // constraints[j][enteringVariable]*(-1) -->  new pivot row coficient

            reso[j] = reso[j] + multFactor * reso[leavingVariable]; // Formula applied and calculate new resource elements
        }

        //Calculate Z row cofficient of resource vector
        multFactor = objective[enteringVariable] * (-1);
        optimalSolution = optimalSolution + multFactor * reso[leavingVariable];
        temp = (-1)*optimalSolution;
        multFactor = objective[enteringVariable] * (-1);

        for (int j = 0; j < objective.size(); j++) // Calculate new objective row elements
        {
            objective[j] = objective[j] + multFactor * constraints[leavingVariable][j]; // formula applied and calculate new objective row
        }

        // displayVector(objective, optimalSolution); // display new objective row element

        multFactor = 1;
        for (int j = 0; j < constraints.size(); j++) // Calcute new Constraint element
        {
            if (j == leavingVariable) continue;
            // skip leaving row elements i.e already change in new pivot row function   

            multFactor = constraints[j][enteringVariable] * (-1);

            for (int i = 0; i < constraints[j].size(); i++)
            {
                constraints[j][i] = constraints[j][i] + multFactor * constraints[leavingVariable][i]; // formula applied and calculate new constraint row
            }
        }
        displayTable(objective,optimalSolution,constraints,reso,indexOfBasic,enteringVariable,leavingVariable);
    }
};



#endif