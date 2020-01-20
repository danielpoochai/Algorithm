#include <cstdio> 
#include <iostream> 
#include <fstream>
#include "parser.h" 

void QuickSort(pair<string, int>*, int , int);
int Partition(pair<string, int>*, int , int);
int main( int argc, char** argv ) 
{  
 // Declare the functional objects 
 AlgParser p; 
 AlgTimer t; 
 
 // Pass the arguement 1 as the input file name 
 p.Parse( argv[1] ); 
 
 // Start timer 
 t.Begin(); 

 int length = p.QueryTotalStringCount();
 //copy lex_string_vector by dynamic array
 pair<string, int>* copy_arr = new pair<string, int>[length];
 for(int i =0; i<length; i++){
    copy_arr[i].first = p.QueryString(i);
    copy_arr[i].second = i+1;
 }

 //quickSort
 QuickSort(copy_arr,0,length-1);

//output the result
fstream out;
out.open(argv[2], ios::out);

 // Display all strings and word numbers 
 for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) 
 {   //cout << p.QueryString(i) << " " << p. QueryWordOrder(i)  << endl; 
     out<< copy_arr[i].first<<" "<<copy_arr[i].second<< endl;
 } 
 
 // Display the accumulated time 
 cout << "The execution spends " << t.End() << " seconds" << endl; 
 getchar();

 return 1; 
}

void QuickSort(pair<string, int>*A, int p, int r){
    if(p<r){
        int q = Partition(A,p,r);
        QuickSort(A,p,q);
        QuickSort(A,q+1,r);
    }
}

int Partition(pair<string,int>*A, int p, int r){
    pair<string, int>x = A[p];
    int i = p;
    int j = r;
    while(true){
        while(A[j] > x){
            j = j-1;
        }
        while(A[i] < x){
            i = i+1;
        }
        if(i<j){
            pair<string, int>tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
        else{
            return j;
        }
    }
}