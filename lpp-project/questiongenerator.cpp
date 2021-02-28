#include <iostream>
#include <vector>
using namespace std;

class Question
{
public:
    string Type;
    vector<string> Constraint_Condition;
    vector<string> Variable_Feasibility;
    int No_Of_Variable;
    int No_Of_Constraint;
    vector<double> Objective_Cofficient;
    vector<vector<double>> Constraint_Cofficient;
    vector<double> Resource;

    void Selecion(void);
    void Set_Objective_Cofficient(void);
    void Set_Constraint_Cofficient(void);
    void Set_Feasibility();
    void Display_Objective_Cofficient(void);
    void Display_Constraint_Cofficient(void);
    void Display_Variable_Feasibility(void);
};

void Question ::Selecion()
{
    cout << "\nWhich type (Max/Min)       :  ";
    cin >> Type;
    cout << "Entre No of variable (n)   :  ";
    cin >> No_Of_Variable;
    cout << "Entre No of Constrains (m) :  ";
    cin >> No_Of_Constraint;
}

void Question ::Set_Objective_Cofficient()
{
    Objective_Cofficient.resize(No_Of_Variable);
    cout << "Entre cofficient of Objective equation : ";
    for (int i = 0; i < No_Of_Variable; i++)
    {
        cin >> Objective_Cofficient[i];
    }
}

void Question ::Display_Objective_Cofficient()
{
    cout << "Objective  :-  \n      " << Type << " Z = ";
    for (int i = 0; i < No_Of_Variable - 1; i++)
    {
        cout << Objective_Cofficient[i] << "x" << i + 1 << " + ";
    }
    cout << Objective_Cofficient[No_Of_Variable - 1] << "x" << (No_Of_Variable) << endl;
}

void Question ::Set_Constraint_Cofficient()
{
    Constraint_Cofficient.resize(No_Of_Constraint);
    Constraint_Condition.resize(No_Of_Constraint);
    Resource.resize(No_Of_Constraint);
    for (int i = 0; i < No_Of_Constraint; i++)
    {
        Constraint_Cofficient[i].resize(No_Of_Variable);
        cout << "Entre Constraint " << i + 1 << " Cofficient : ";
        for (int j = 0; j < No_Of_Variable; j++)
        {
            cin >> Constraint_Cofficient[i][j];
        }
        cout << "Condition (=,<=,>=) : ";
        cin >> Constraint_Condition[i];
        cout << "Resourse : ";
        cin >> Resource[i];
    }
}

void Question ::Display_Constraint_Cofficient()
{
    cout << "Constraint  :-\n";
    for (int i = 0; i < No_Of_Constraint; i++)
    {
        cout << "     ";
        for (int j = 0; j < (No_Of_Variable - 1); j++)
        {
            cout << Constraint_Cofficient[i][j] << "x" << j + 1 << " + ";
        }
        cout << Constraint_Cofficient[i][No_Of_Variable - 1] << "x" << (No_Of_Variable);

        cout << " " << Constraint_Condition[i] << " " << Resource[i] << endl;
    }
}

void Question::Set_Feasibility()
{
    Variable_Feasibility.resize(No_Of_Variable);
    cout << "Feasibility(>=0, Unristricted)\n";
    for (int i = 0; i < No_Of_Variable; i++)
    {
        cout << " Variable x" << i + 1 << " : ";
        cin >> Variable_Feasibility[i];
    }
}

void Question ::Display_Variable_Feasibility(){
    cout<<"Feasibility :-\n";
    for (int i = 0; i < No_Of_Variable; i++)
    {
        cout<<"x"<<i+1<<" "<<Variable_Feasibility[i]<<", ";
    }
    
}

int main()
{
    cout << "********   LPP Solver    ********" << endl;

    Question f;
    f.Selecion();
    f.Set_Objective_Cofficient();
    f.Set_Constraint_Cofficient();
    f.Set_Feasibility();
    cout << "\n\n*******************************************************************************\n";
    f.Display_Objective_Cofficient();
    f.Display_Constraint_Cofficient();
    f.Display_Variable_Feasibility();
    cout << "\n*******************************************************************************\n\n";
}
