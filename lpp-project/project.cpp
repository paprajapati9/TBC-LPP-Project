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

#include <iostream>
#include <vector>
using namespace std;

void displayVector(vector <int>);
void displayVector(vector <double>);
class LPP{
    public:
    int enteringVariable {};
    int leavingVariable {};
    double pivotElement;
    vector <int> indexOfBasic;
    void checkBasic(vector <vector<double>> constraint)
    {
        int BasicInt {},flag {1};
        
        // i will denote the column of the table
        for ( int i = 0; i < constraint[0].size(); i++)
        {
            // j will denote the row of the table
            BasicInt=0;
            flag = 1;
            for ( int j = 0; j < constraint.size(); j++)
            {
                if (constraint[j][i] < 0) flag = 0;
                BasicInt += constraint[j][i];
            }
            if (flag && (BasicInt==1))
                indexOfBasic.push_back(i);
        }
        displayVector(indexOfBasic);
    }
    // we will check for the most negative element in the Z-row
    void checkEnteringVar(vector <int> objRow)
    {
        int mostNegativeIndex = 0;
        for (int i = 0 ; i < objRow.size() ; i++)
        {
            if (objRow[i] < objRow[mostNegativeIndex]) 
			mostNegativeIndex = i;
        }
        enteringVariable = mostNegativeIndex;
    cout<<enteringVariable<<endl;
    }

    void checkleavingVariable(vector <double> res,vector <vector<double>> constraint){
    	double min_ratio=0;
    	double  ratio;
    	double currentvar;
    	for(int i=0;i<res.size();i++){
    	  currentvar=constraint[i][enteringVariable];
		  if(currentvar>0)	{
		  	ratio=res[i]/currentvar;
		  	if(min_ratio==0 || ratio<min_ratio){
		  	min_ratio=ratio;
		  	leavingVariable=i;
		  }
		  }
		  
		}
		cout<<leavingVariable<<endl;
	}
    void setPivot( vector <vector<double>> constraints ){
            pivotElement=constraints[leavingVariable][enteringVariable];
            cout<<"pivot  "<<pivotElement<<endl;
         }

    bool checkOptimality(vector <int> objective){
        for(int i=0; i<objective.size();i++){
            if(objective[i]<=0){
               cout<<"Optimality not reached"<<endl;
               return 0;
            }
        }
        cout<<"Optimality reached"<<endl;
        return 1;
    }
    void newPivotRow(vector <vector<double>> &constraints){
       for(int i=0;i<=constraints[leavingVariable].size();i++){
       constraints[leavingVariable][i]=constraints[leavingVariable][i]/pivotElement;
       }
       displayVector(constraints[leavingVariable]);
    }
    void newRow(vector <vector<double>> &constraints){
        double multFactor=1;
        for(int j=0;j<constraints.size();j++){
            if(j==leavingVariable)
                continue;
            multFactor=constraints[j][enteringVariable]*(-1);
            for(int i=0;i<constraints[j].size();i++){
                constraints[j][i]=constraints[j][i]+multFactor*constraints[leavingVariable][i];
            }
            displayVector(constraints[j]);
        }
     
    }
     
};
class Constraint :public LPP{
    public :
    vector  <vector<double>> constraints{{1,2},{2,1}};
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

class Resource :public LPP{
    public:
    vector <double> reso {2,3};

};


class ObjFunc :public LPP{
    public:
    vector<int> objective ;
    void Insert(){
        objective.push_back(-2);
        objective.push_back(-3);
    }
    
    void SlackSurp(int numConst){
        for(int i=0;i<numConst;i++){
            objective.push_back(0);
        }
    }
    void display(){
        for(int j=0;j<objective.size();j++)
        cout<<"OBJECTIVE FUNCTION : "<<objective[j]*(-1)<<endl;
        // the objective function to be displayed should be in positive form thus we are multiplying by -1
    }
};


void displayVector(vector <int> dv)
{
    for (int i=0 ; i< dv.size() ; i++)
    {
        cout<<dv[i]<<" ";
    }
    cout<<endl;
}

void displayVector(vector <double> dv)
{
    for (int i=0 ; i< dv.size() ; i++)
    {
        cout<<dv[i]<<" ";
    }
    cout<<endl;
}
    
int main(){
    cout<<" Solver"<<endl;
    Constraint c;
    ObjFunc o;
    Resource r;
    o.Insert();
    // o.display();
    o.SlackSurp(2);
    // cout<<"Objective function after converting to Std Form : "<<endl;
    // o.display();
    // c.display();
    c.SlackSurp();
    // cout<<"Constraints after converting to Std Form : "<<endl;
    // c.display();
    c.checkBasic(c.constraints);
   
    int a=c.checkOptimality(o.objective);
    
    while(!a){
    c.checkEnteringVar(o.objective);
<<<<<<< HEAD
    c.leaving_var(r.reso,c.constraints);
}
=======
    c.checkleavingVariable(r.reso,c.constraints);
    c.setPivot(c.constraints);
    c.newPivotRow(c.constraints);
    c.newRow(c.constraints);
    a=1;

    }

}
// MAX z= 2x1+3x2
//  S.to x1+2X2 <= 2
//       2x2 +x1<=3
// x1,x2>=0
>>>>>>> cbcd1a7d8147cc877ec907056264232f2e85b206
