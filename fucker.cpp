/*
Write a program that prompts the user for an integer value in the range
0 to 32,767 and then prints the individual digits of the numbers on a line
with 3 spaces btw the digits. The first line is to start with the leftmost
digit and print all 5 digits; the second line is to start with the second digit
from the left and print four digits, and so fourth.
ex-  
0 0 1 2 3 4 
0 1 2 3 4
1 2 3 4 
2 3 4
3 4
4
*/
# include <iostream>
using namespace std;

int main(){


  unsigned int a=0,b=0,c=0,remc{0}
                   ,d=0,remd{0},e=0,reme{0},f=0;


  cout<<"Please Enter an Integer b/w 0 - 32,767 : "<<endl;
  cin>>a;

  b=(a%10000);
  b=(a-b)/(10000);
  cout<<b<<"   ";

  c=(a-(b*10000));
   remc=(c%1000);
      c=(c-remc)/(1000);
  cout<<c<<"   ";

  d=(a-(b*10000)-(c*1000));
   remd=(d%100);
      d=(d-remd)/100;
  cout<<d<<"   ";

  e=(a-(b*10000)-(c*1000)-(d*100));
   reme=(e%10);
      e=(e-reme)/10;
  cout<<e<<"   ";

  f=(a-(b*10000)-(c*1000)-(d*100)-(e*10));
   cout<<f<<"   "<<endl;

   
   cout <<c<<"   "<<d<<"   "<<e<<"   "<<f<<endl;
   cout <<d<<"   "<<e<<"   "<<f<<endl;
   cout <<e<<"   "<<f<<endl;
   cout <<f<<endl;
// this is how u code.
 return 0;
}
