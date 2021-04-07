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
    double optimalSolution {}; //stores optimal solution at each simplex table
    int enteringVariable {}; //stores index of the entering variable in indexOfBasic vector
    int leavingVariable {}; //stores index of the entering variable in objective vector
    double pivotElement; //stores value of the pivot element at each simplex table
    vector <int> indexOfBasic; //stores index of current basic variables in objective vector

    /**
     * Checks initial basic variables  by reading the constraints
     * and adds thier variable in indexOfBaisc vector.
     * @param constraint: 2D constraints vector.
     */
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
        //displayVector(indexOfBasic);
    }

    /**
     * Checks for the most negative/positive element in the Z-row
     * based on type of lpp problem max/min.
     * @param objRow: Objective row vector.
     * @param problemType: Min or Max type of problem, 0 for min, 1 for max.
     * By default problem type is 1 that is maximizarion problem. 
     */
    void checkEnteringVar(vector <double> objRow, int problemType=1)
    {
        int enteringVarIndex = 0;
        for (int i = 0 ; i < objRow.size() ; i++)
        {
            if(problemType){
                if (objRow[i] < objRow[enteringVarIndex]) 
                    enteringVarIndex = i;
            }else{
                if (objRow[i] > objRow[enteringVarIndex]) 
                    enteringVarIndex = i;
            }
            
        }
        enteringVariable = enteringVarIndex;
        cout<<"Entering variable is: x"<<enteringVariable+1<<endl;
    }

    void checkleavingVariable(vector <double> res,vector <vector<double>> constraint){
    	double min_ratio=0;//declaring and initialisation var to store minimum ratio
        double  ratio;//a variable which will store all ratios 
    	double currentvar;//to calculate the ratios we have to select particular entries of the rows ,so we need this variable to store index of  the same.
    	for(int i=0;i<res.size();i++){//initialising a for-loop from zero to size of resource vector
    	    currentvar=constraint[i][enteringVariable];//value of currentvar will be i'th term of constraint's row in the enteringVar column
            if(currentvar>0)	{//only elements which are >=0 will be considered for min ratio
            	ratio=res[i]/currentvar;//to find ratios we are dividing resource column with currentvar 
            	if(min_ratio==0 || ratio<min_ratio){//condition for the least of the ratio obtained
                	min_ratio=ratio;// assigning min_ratio the value of least of the ratios obtained
                	leavingVariable=i;//the value of i for which we will get min ratio we be assigned to leavingVar for further calc's
                }
		    }
		}
		cout<<"Leaving variable is: x"<<indexOfBasic[leavingVariable]+1<<endl;//printing leaving variable. 
	}

    void setPivot( vector <vector<double>> constraints ){
        pivotElement=constraints[leavingVariable][enteringVariable];
        cout<<"Pivot element is: "<<pivotElement<<endl<<endl;
    }

    /** 
     * The optimality is acheived if every element in the objective row is greater than 0 for maximization problem here
     * The vector objective stores the Z row elements of the problem for every iteration.
     * We run a loop to check for every element in the vector objective.
     * If all the elements of the vector objective or the Z row are greater than 0, the optimality has reached.
     * If even any one element is not positive, the program continues.
     */
    bool checkOptimality(vector <double> objective){
        cout<<"\nChecking Optimality...\n";
        for(int i=0; i<objective.size();i++){
            if(objective[i]<0){
               cout<<"Optimality not reached\n\n";
               return 0;
            }
        }
        cout<<"Optimality reached"<<endl;
        return 1;
    }

    void newPivotRow(vector <vector<double>> &constraints , vector <double> &reso){
        reso[leavingVariable]= reso[leavingVariable]/pivotElement;
        for(int i=0;i<=constraints[leavingVariable].size();i++)
        {
            constraints[leavingVariable][i]=constraints[leavingVariable][i]/pivotElement;
        }      
    }

    void newRow(vector <vector<double>> &constraints , vector <double> &objective , vector <double> &reso )
    {
        double multFactor=1;

        for(int j=0;j<reso.size();j++)
        {
            if(j==leavingVariable)
                continue;
            multFactor=constraints[j][enteringVariable]*(-1);
            reso[j]=reso[j]+multFactor*reso[leavingVariable];
        }

        multFactor=objective[enteringVariable]*(-1);
        optimalSolution=optimalSolution+multFactor*reso[leavingVariable];
        cout<<optimalSolution<<" ";

        displayVector(reso);

        multFactor=objective[enteringVariable]*(-1);
        for(int j=0;j<objective.size();j++)
        {
            objective[j]=objective[j]+multFactor*constraints[leavingVariable][j];
        }
        displayVector(objective);
        
        multFactor=1;
        for(int j=0;j<constraints.size();j++){
            if(j==leavingVariable){
                displayVector(constraints[leavingVariable]);
                continue;
            }
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
    vector <int> constype{-1,-1}; //type of constraints ,have to determine consttype from the user input

    void display(vector <double> res){

        for (int i = 0; i < constraints.size(); ++i)
        {
            for (int j = 0; j < constraints[i].size(); ++j)
            {
                if(j<(constraints[i].size()-1))
                    cout<<constraints[i][j]<<"x"<<j+1<<" + ";
                else
                    cout<<constraints[i][j]<<"x"<<j+1<<" = "<<res[i];
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
    vector <double> reso {2,3}; //stores resource coefficient

};


class ObjFunc :public LPP{
    public:
    vector<double> objective ; //stores objective coefficient.

    //Insert coefficient of objective function to objective vector.
    void Insert(){ //Have to take objective function values from user 
        objective.push_back(-2);
        objective.push_back(-3);
    }

    /**
     * Adds slack and surplus in the Objective row vector .
     * @param numConst: No. of constraints in the LPP problem.
     * By default problem is <= or >= type so
     * the no of constraints can define the no.of zeros to be added in objective row vector.
    */
    void SlackSurp(int numConst){
        for(int i=0;i<numConst;i++){
            objective.push_back(0);
        }
    }

    /**
     * Displays Objective function.
     * By default objective parameters are negative .
     * @param coeff : stores the negative value of objective coefficient 
     *                if it not equal to 0(to make them positive) otherwise 
     *                it stores 0 as it is.
     * Adds '+' between each objective variable except the last one.
     */
    void display(){
        cout<<"**** LPP Problem ****\n\n";
        cout<<"Max Z = ";
        for(int j=0;j<objective.size();j++){
            int coeff=(objective[j]!=0) ? (objective[j]*(-1)) : 0;
            if(j<(objective.size()-1)){
                cout<<coeff<<"x"<<j+1<<" + ";
            }
            else{
                cout<<coeff<<"x"<<j+1;
            }
        }
        cout<<"\n\n";
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
    cout<<"\t\t\t  ***** LPP Solver *****\n\n\n";
    Constraint c;
    ObjFunc o;
    Resource r;
    o.Insert();
    o.SlackSurp(2);//Find out how many slack/surplus var. to be added in ObjFunc 
    o.display();
    c.SlackSurp();
    cout<<"Subject To: \n";
    c.display(r.reso);

    //Check initial basic variables
    c.checkBasic(c.constraints);
   
    int a=c.checkOptimality(o.objective);
    
    while(!a){
        c.checkEnteringVar(o.objective);
        c.checkleavingVariable(r.reso,c.constraints);
        c.setPivot(c.constraints);
        c.newPivotRow(c.constraints, r.reso);
        c.newRow(c.constraints, o.objective , r.reso);
        a = c.checkOptimality(o.objective);
        cout<<endl;
    }
    cout<<"Optimal Solution is : "<<c.optimalSolution;
}
// MAX z= 2x1+3x2
//  S.to x1+2X2 <= 2
//       2x2 +x1<=3
// x1,x2>=0