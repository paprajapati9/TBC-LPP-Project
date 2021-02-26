#include <iostream>
#include <vector>
using namespace std;

class Question
{
public:
    int No_Of_Variable;
    int No_Of_Constraint;
    vector<int> Objective_Cofficient;
    vector<vector<int>> Constraint_cofficient;

    void Selecion(void);
    void Input_Objective_Cofficient(void);
    void Display_Objective_Cofficient(void);
    void Input_Constraint_Cofficient(void);
    void Display_Constraint_Cofficient(void);
};

void Question ::Selecion()
{
    cout << "Entre No of variable (n): ";
    cin >> No_Of_Variable;
    cout << "Entre No of Constrains (m): ";
    cin >> No_Of_Constraint;
}

void Question ::Input_Objective_Cofficient()
{
    for (int i = 0; i < No_Of_Variable; i++)
    {
        int temp;
        cin >> temp;
        Objective_Cofficient.push_back(temp);
    }
}



void Question ::Input_Constraint_Cofficient()
{
    for (int i = 0; i < No_Of_Constraint; i++)
    {
        for (int j = 0; j < No_Of_Variable; j++)
        {
            int temp1;
            cin >> temp1;
            Constraint_cofficient[i][j]=temp1;
        }
    }
}

int main()
{
    cout << "**********************   LPP Solver    **********************" << endl;

    Question f;
    f.Selecion();
    f.Input_Objective_Cofficient();
    f.Input_Constraint_Cofficient();
}