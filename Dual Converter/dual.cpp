#include <iostream>
#include <string>
using namespace std;

class LPP
{
    public:
        int num_of_variable {};
        int num_of_constaint {};
};

class Objective :public LPP
{
    int cost_Coeff[num_of_constaint] {};

    void setCostCoeff()
    {
        for (int i = 0; i < num_of_variable; i++)
        {
            cout<<"\nX"<<i<<" : ";
            cin>>cost_Coeff[i];
        }
    }
};

class Constraint :public LPP
{
    int coeff_matrix[num_of_constaint][num_of_variable] {};

    for (int i = 0; i < num_of_constraint; i++)
    {
        cout<<"\nFor constraint "<<i<<endl;
        for(int j = 0; j <num_of_variable; j++)
        {
            cout<<"\nX"<<j<<" : ";
            cin>>coeff_matrix[i][j];
        }
    }

};

int main()
{
    return 0;
}