#include <iostream>
#include <string>
using namespace std;

class LPP
{
    public:
        static const int num_of_variable = {2};
        static const int num_of_constraint {2};
};

class Objective :public LPP
{
    int cost_Coeff[num_of_constraint] {};

    public:
    void setCostCoeff()
    {
        for (int i = 1; i <= num_of_variable; ++i)
        {
            cout<<"\nX"<<i<<" : ";
            cin>>cost_Coeff[i];
        }
    }
};

class Constraint :public LPP
{   
    int coeff_matrix[num_of_constraint][num_of_variable];
    void setCoeffMatrix()
    {
        for(int i = 0; i < num_of_constraint; i++)
        {
            cout<<"\nFor constraint "<<i<<endl;
            for(int j = 0; j <num_of_variable; j++)
            {
                cout<<"\nX"<<j<<" : ";
                cin>>coeff_matrix[i][j];
            }
        }
    }

};

int main()
{
    LPP l;
    // l.setNumVar();
    Objective o;
    o.setCostCoeff();
    return 0;
}