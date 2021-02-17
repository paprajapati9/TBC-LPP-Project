//  LPP Solver 
//solver:
//2 Var 2 Constraints 
//Objective function 
//
//constraints 
//feasibility 
//Maximisation
//conversion  
//Standard form
//
//
//Basic var 
//Entering var
//Leaving var
//
//Pivot element,Pivot row 
//Optimality Condition 
//Optimal Table
//
//Variable value,Optimal solution
//
//
//Coefficent of both variables in the obj
//
//Coeff in C1
//Coeff in C2
//
//C vector=[1,2]
//A 2dvector ={[1,3,],[2,4]}
//B vector =[2,3]
//loop start:
//Optimality check kro
//if Ci>=0
//
//C vector me entering var()
//getColumn of entering var 
//Exiting var(column of entering var , b vector)
//
//Pivot element()
//New (Exiting var row) = Exiting var row/pivot element
//
//make_entering_var_column_zero();
//loop end;
//print solution;                   

#include <vector>
#include <iostream>
using namespace std;

class LPP{
    
};
class Constraint{
    public :
    vector< vector<double> > constraints{{1,2},{2,1}};
    //-1 denotes<= condition ,
    // 0 denotes = condition ,
    // 1 denotes >= condition
    vector <int> constype{-1,-1}; //type of constraints

    void display(){
        for (int i = 0; i < constraints.size(); ++i)
        {
            for (int j = 0; j < constraints[i].size(); ++j)
            {
                cout<<constraints[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    void SlackSurp(){
        for (int i = 0; i < constraints.size(); ++i)
        {
            if(constype[i] == -1){
                addZeros(i, i);
                constraints[i].push_back(1);
                addZeros(constraints.size()-i-1, i);
            }
            else if(constype[i] == 1){
                addZeros(i, i);
                constraints[i].push_back(-1);
                addZeros(constraints.size()-i-1, i);
            }
        }
    }

    void addZeros(int number, int index){
        for (int i = 0; i < number; ++i)
        {
            constraints[index].push_back(0);
        }
    }

    
};

class Resource{
    public:
    vector <double> reso {2,3};

};
class ObjFunc{
    public:
    vector<int> objective ;
    void Insert(){
        objective.push_back(2);
        objective.push_back(3);
    }
    
    void SlackSurp(int numConst){
        for(int i=0;i<numConst;i++){
            objective.push_back(0);
        }
    }
    void display(){
        for(int j=0;j<objective.size();j++)
        cout<<"OBJECTIVE FUNCTION : "<<objective[j]<<endl;
    }
};
    
int main(){
    cout<<" Solver"<<endl;
    Constraint c;
    ObjFunc o;
    o.Insert();
    o.display();
    o.SlackSurp(2);
    cout<<"Objective function after converting to Std Form : "<<endl;
    o.display();
    c.display();
    c.SlackSurp();
    cout<<"Constraints after converting to Std Form : "<<endl;
    c.display();
}