#include <iostream>
#include <vector>
#include <iomanip>
#include "fraction.h"
#include <string>

using namespace std;

#define separator   ' '
#define numWidth  10
int enteringVariable = 0;
int leavingVariable = 0;
/**
 * TESTING PROBLEM
 * MAX z= 2x1+3x2
 *  S.to x1+2X2 <= 2
 *       2x2 +x1<=3
 * x1,x2>=0
*/

void displayVector(vector<int>);
void displayVector(vector<fraction>, fraction);
// void displayVector(vector<fraction>, fraction , int);


class LPP
{
    public:
    fraction optimalSolution{}; //stores optimal solution at each simplex table
    int enteringVariable{};   //stores index of the entering variable in indexOfBasic vector
    int leavingVariable{};    //stores index of the leaving variable in objective vector
    int problemType;          //stores the int indicating type of problem
    fraction pivotElement;      //stores value of the pivot element at each simplex table
    vector<int> indexOfBasic; //stores index of current basic variables in objective vector

    void setProblemType(int probType)
    {
        problemType = probType;
    }

    /**
     * Checks initial basic variables by reading the constraints
     * and adds their variables in indexOfBaisc vector.
     * @param constraint: 2D constraints vector.
     */
    void checkBasic(vector<vector<fraction>> constraint, vector<fraction> objective, vector<fraction> resource)
    {
        fraction BasicInt{};
        int flag{1};
        cout<<left<<setw(10)<<"Basic";
        for(int i = 1; i <= 4; i++) cout<<"x"<<setw(10)<<i;
        cout<<"Solution\n";
        cout<<left<<setw(10)<<setfill(separator)<<"Z";
        displayVector(objective, optimalSolution); // display new objective row element

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
                /* If sum of column is 1 and no negative element is
                   present , it means the column makes identity vector */
            }
            if (flag && (BasicInt == 1))
                indexOfBasic.push_back(i);

        }
        for (int j = 0; j < constraint.size(); j++)
        {
            cout<<"x"<<left<<setw(9)<<indexOfBasic[j]+1;
            displayVector(constraint[j], resource[j]);
        }
    }

    //This function will tell the values of the Variables present in basis (basic variables)
    void displayBasicVariables(vector<fraction> resource)
    {
        for (int i = 0; i < indexOfBasic.size(); i++)
        {
            cout<<"x"<<indexOfBasic[i]+1<<" : "<<resource[i]<<endl;
        }
    }


    /**
     * Checks for the most negative/positive element in the Z-row
     * based on type of lpp problem max/min.
     * @param objRow: Objective row vector.
     * @param problemType: Determining max or min type problems
     * By default problem type is 1 that is maximization problem. 
     */
    int checkEnteringVar(vector<fraction> objRow, int problemType=1)
    {
        int enteringVarIndex = 0;
        for (int i = 0; i < objRow.size(); i++)
        {
            if (problemType)
            {
                if (objRow[i] < objRow[enteringVarIndex])
                    enteringVarIndex = i;
            }
            else
            {
                if (objRow[i] > objRow[enteringVarIndex])
                    enteringVarIndex = i;
            }
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
        cout << "Pivot element is: " << pivotElement << endl
             << endl;
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
    * what does Function? : change elements of old pivot row for next tabel
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
        //displayVector(reso); // display new resource vector
        multFactor = objective[enteringVariable] * (-1);
        cout<<left<<setw(10)<<"Basic";
        for(int i = 1; i <= 4; i++) cout<<left<<setw(10)<<"x"+to_string(i)<<" ";
        cout<<"Solution\n";
        cout<<left<<setw(10)<<setfill(separator)<<"Z";
        for (int j = 0; j < objective.size(); j++) // Calculate new objective row elements
        {
            objective[j] = objective[j] + multFactor * constraints[leavingVariable][j]; // formula applied and calculate new objective row
        }

        displayVector(objective, optimalSolution); // display new objective row element

        multFactor = 1;

        for (int j = 0; j < constraints.size(); j++) // Calcute new Constraint element
        {
            if (j == leavingVariable) // skip leaving row elements i.e already change in new pivot row function
            {   
                cout<<"x"<<left<<setw(9)<<indexOfBasic[0]+1;
                displayVector(constraints[leavingVariable], reso[leavingVariable]);
                continue;
            }

            multFactor = constraints[j][enteringVariable] * (-1);

            for (int i = 0; i < constraints[j].size(); i++)
            {
                constraints[j][i] = constraints[j][i] + multFactor * constraints[leavingVariable][i]; // formula applied and calculate new constraint row
            }
            cout<<"x"<<left<<setw(9)<<indexOfBasic[1]+1;
            displayVector(constraints[j], reso[j]); // display new constraint vector
        }
    }
};


class Constraint : public LPP
{
    public:
    vector<vector<fraction>> constraints{{1, 2}, {2, 1}};

    /**
     * @condition: -1 : <=
     *              0 : =
     *              1 : >=
     */ 
    vector<int> constype{-1, -1}; //type of constraints ,have to determine constraint type from the user input
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
    void SlackSurp(vector<fraction> &objective, int problemType=1)
    {
        for (int i = 0; i < constraints.size(); ++i)
        {
            if (constype[i] == -1) // -1 : <= enequality
            {
                addZeros(i, 1);  //adds zero for slack var in all except current constraints
                objective.push_back(0); //0 for current slack var
            }
            else if (constype[i] == 1) // 1 : >= enequality
            {
                addZeros(i, -1); //adds zero for surplus var in all except current constraints
                objective.push_back(0); //0 for current surplus var
                addZeros(i, 1); //adds zero for artificial var in all except current constraints
                if(problemType == 0) objective.push_back(-1000); //M=1000 for current Artificial var
                else objective.push_back(1000); //M=1000 for current Artificial var
            }
            else
            {
                addZeros(i, 1); //adds zero for artificial var in all except current constraints
                if(problemType == 0) objective.push_back(-1000); //M=1000 for current Artificial var
                else objective.push_back(1000); //M=1000 for current Artificial var
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
            if(i == index) constraints[index].push_back(coefficient);
            else constraints[i].push_back(0);
        }
    }
};


class Resource : public LPP
{
    public:
    vector<fraction> reso{2, 3}; //stores resource coefficient
};

class ObjFunc : public LPP
{
    public:
    vector<fraction> objective; //stores objective coefficient.

    //Insert coefficient of objective function to objective vector.
    void Insert()
    { 
        objective.push_back(-2);
        objective.push_back(-3);
    }

    /**
     * Displays Objective function.
     * By default objective parameters are negative .
     * @param coeff : stores the negative value of objective coefficient 
     *                if it not equal to 0(to make them positive) otherwise 
     *                it stores 0 as it is.
     * Adds '+' between each objective variable except the last one.
     */
    void display()
    {
        cout << "**** LPP Problem ****\n\n";
        cout << "Max Z = ";
        for (int j = 0; j < objective.size(); j++)
        {
            fraction coeff = (objective[j] != 0) ? (objective[j] * (-1)) : 0;
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
        cout << "\n\n";
    }
};

/**
 * @param dv: Vector containing int type data values.
 * displayVector function prints all the elements
 * of the given vector
*/
void displayVector(vector<int> dv)
{
    for (int i = 0; i < dv.size(); i++)
    {
        cout << left << setw(numWidth) << setfill(separator) << dv[i]<<" ";
    }
    cout << endl;
}

// Overloaded displayVector to display a vector containing fraction type data
void displayVector(vector<fraction> dv, fraction resourse)
{
    for (int i = 0; i < dv.size(); i++)
    {   
        cout << dv[i]<<"          ";
    }
    cout << resourse<<"          ";
    cout << endl;
}

int main()
{
    cout << "\t\t\t  ***** LPP Solver *****\n\n\n";
    Constraint c;
    ObjFunc o;
    Resource r;
    o.setProblemType(1); //set min/max problem type
    o.Insert();
    c.SlackSurp(o.objective);
    o.display();
    cout << "Subject To: \n";
    c.display(r.reso);
    cout<<endl;

    //Check initial basic variables
    c.checkBasic(c.constraints, o.objective, r.reso);

    int optimalCondition = c.checkOptimality(o.objective);
    while (not optimalCondition)
    {
        enteringVariable = c.checkEnteringVar(o.objective);
        leavingVariable = c.checkleavingVariable(r.reso, c.constraints);
        c.setPivot(c.constraints);
        c.newPivotRow(c.constraints, r.reso);
        c.newRow(c.constraints, o.objective, r.reso);
        optimalCondition = c.checkOptimality(o.objective);
        cout << endl;
    }
    cout<<"Final basic variables are: \n";
    c.displayBasicVariables(r.reso);
    cout << "Optimal Solution is : " << c.optimalSolution<<endl<<endl;
    getchar();
}

/*
 * Check If the Basisvalues are correctly displaying or not ( inside newRow function)
*/