#include <iostream>
#include <string>
using namespace std;

class LPP
{
    public:

    static const int num_of_variable {2};
    static const int num_of_constraint {2};
    int Variable_Feasibility[num_of_variable] {};
    void fesiability()

    {
        cout<<"\nEnter fesiability condition:\n1 for  <= 0\n0 for  >= 0\n-1 for   unrestricted\n\n";
        for (int i = 0; i < num_of_variable; i++)
        {
            cout<<"X"<<i+1<<" : ";
            cin>>Variable_Feasibility[i];
        }
    }
};

class Objective :public LPP
{
    public:

    int cost_Coeff[num_of_variable] {};
    void setCostCoeff()
    {
        cout<<"\nFor Objective Function ::\n";
        for (int i = 0; i < num_of_variable; ++i)
        {
            cout<<"\nX"<<i+1<<" : ";
            cin>>cost_Coeff[i];
        }
    }
};

class Resource :public LPP
{
    public:
    
    int res_vector[num_of_constraint] {};
    void setResource()
    {
        cout<<"\nFor Resource Vector ::\n";
        for (int i = 0; i < num_of_constraint; i++)
        {
            cout<<"\nResource for Constraint "<<i+1<<" : ";
            cin>>res_vector[i];
        }
    }
};

class Constraint :public LPP
{   
    public:

    int coeff_matrix[num_of_constraint][num_of_variable];
    void setCoeffMatrix()
    {
        for(int i = 0; i < num_of_constraint; i++)
        {
            cout<<"\nFor constraint "<<i+1<<endl;
            for(int j = 0; j <num_of_variable; j++)
            {
                cout<<"\nX"<<j+1<<" : ";
                cin>>coeff_matrix[i][j];
            }
        }
    }

    int transpose_matrix[num_of_variable][num_of_constraint];
    void setTransposeMatrix()
    {
        for (int i = 0; i < num_of_variable; i++)
        {
            for(int j = 0; j < num_of_constraint; j++)
            {
                transpose_matrix[i][j] = coeff_matrix[j][i];
            }
        }
    }

    void showTransposeMatrix()
    {
        for (int i = 0; i < num_of_variable; i++)
        {
            for(int j = 0; j < num_of_constraint; j++)
            {
                cout<<transpose_matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

};

int main()
{
    LPP l;
    Objective o;
    Constraint c;
    Resource r;

    o.setCostCoeff();
    c.setCoeffMatrix();
    r.setResource();
    l.fesiability();
    c.setTransposeMatrix();
    return 0;
}

