#include <iostream>
#include <vector>
using namespace std;

class Question
{
public:
    string Type;
    int No_Of_Variable;
    int No_Of_Constraint;
    int No_Of_Slack_Surplus;
    vector<string> Constraint_Condition;
    vector<string> Variable_Feasibility;
    vector<double> Objective_Cofficient;
    vector<vector<double>> Constraint_Cofficient;
    vector<double> Resource;

    void Selection(void);
    void Set_Objective_Cofficient(void);
    void Set_Constraint_Cofficient(void);
    void Set_Feasibility();
    void Display_Objective_Cofficient(void);
    void Display_Constraint_Cofficient(void);
    void Display_Variable_Feasibility(void);
    void Convert_Objective_Standard_Form(void);
    void Convert_Constraint_Standard_Form(void);
    void Display_Variable_Feasibility_After_Standard(void);
};

void Question ::Selection()
{
    cout << "\nWhich type (Max/Min)       :  ";
    cin >> Type;
    cout << "Enter No of variable (n)   :  ";
    cin >> No_Of_Variable;
    cout << "Enter No of Constrains (m) :  ";
    cin >> No_Of_Constraint;
}

void Question ::Set_Objective_Cofficient()
{
    Objective_Cofficient.resize(No_Of_Variable);
    cout << "Enter cofficient of Objective equation : ";
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
        cout << "Enter Constraint " << i + 1 << " Cofficient : ";
        for (int j = 0; j < No_Of_Variable; j++)
        {
            cin >> Constraint_Cofficient[i][j];
        }
        cout << "Condition (<=,>=) : ";
        cin >> Constraint_Condition[i];
        cout << "Resourse : ";
        cin >> Resource[i];

        while (Constraint_Condition[i] == ">=" && Resource[i] > 0)
        {
            cout << "Resorce must negative i.e (condition >=) Entre again :";
            cin >> Resource[i];
        }
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

void Question ::Display_Variable_Feasibility()
{
    cout << "Feasibility :-\n";
    for (int i = 0; i < No_Of_Variable; i++)
    {
        cout << "x" << i + 1 << " " << Variable_Feasibility[i] << ", ";
    }
}

void Question ::Convert_Objective_Standard_Form()
{
    if (Type == "min" || Type == "Min" || Type == "MIN")
    {
        Type = "Max";
        for (int i = 0; i < Objective_Cofficient.size(); i++)
        {
            Objective_Cofficient[i] = Objective_Cofficient[i] * -1;
        }
    }

    No_Of_Slack_Surplus = 0;

    for (int i = 0; i < Constraint_Condition.size(); i++)
    {
        if (Constraint_Condition[i] == "<=" || Constraint_Condition[i] == ">=")
        {
            Objective_Cofficient.push_back(0);
            No_Of_Slack_Surplus++;
            No_Of_Variable++;
        }
    }
}

void Question ::Convert_Constraint_Standard_Form()
{

    for (int i = 0; i < No_Of_Constraint; i++)
    {
        Constraint_Cofficient[i].resize(No_Of_Variable);

        if (Constraint_Condition[i] == "<=")
        {
            Constraint_Cofficient[i][No_Of_Variable - No_Of_Slack_Surplus + i] = 1;
        }

        if (Constraint_Condition[i] == ">=")
        {
            Constraint_Cofficient[i][No_Of_Variable - No_Of_Slack_Surplus + i] = -1;
            for (int j = 0; j < No_Of_Variable; j++)
            {
                if (Constraint_Cofficient[i][j] != 0)
                    Constraint_Cofficient[i][j] = Constraint_Cofficient[i][j] * -1;
            }
            Resource[i] = Resource[i] * -1;
        }
    }
}

void Question::Display_Variable_Feasibility_After_Standard()
{
    cout << "Feasibility :\n";
    cout << "     All variable : >= 0";
}

int main()
{
    cout << "********   LPP Solver    ********" << endl;
    cout << "\n For Simplex method Only (Constraint <= type only )" << endl;

    Question f;
    f.Selection();
    f.Set_Objective_Cofficient();
    f.Set_Constraint_Cofficient();
    f.Set_Feasibility();
    cout << "\n\n*******************************************************************************\n";
    f.Display_Objective_Cofficient();
    f.Display_Constraint_Cofficient();
    f.Display_Variable_Feasibility();
    cout << "\n*******************************************************************************\n\n";
    cout << "\n\n\n*******************************************************************************\n";
    cout << "STANDARD FORM :\n\n";
    f.Convert_Objective_Standard_Form();
    f.Display_Objective_Cofficient();
    f.Convert_Constraint_Standard_Form();
    f.Display_Constraint_Cofficient();
    f.Display_Variable_Feasibility_After_Standard();
    cout << "\n*******************************************************************************\n\n";
}