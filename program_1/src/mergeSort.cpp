#include <cstdio> 
#include <iostream> 
#include <vector>
#include <fstream>
#include "parser.h" 

void MergeSort(pair<string,int>*, int, int);
void Merge(pair<string,int>*,int,int,int);

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
//copy lex_string_vector by vector
pair<string,int>* copy_lex = new pair<string,int>[length];
for(int i=0; i<length; i++){
    copy_lex[i].first = p.QueryString(i);
    copy_lex[i].second = i+1;
}

//MergeSort
MergeSort(copy_lex,0,length-1);

//output the result
fstream out;
out.open( argv[2] ,ios::out);
 // Display all strings and word numbers 
 for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) 
 {   //cout << copy_lex.at(i).first << " " << copy_lex.at(i).second  << endl;
     out  << copy_lex[i].first << " " << copy_lex[i].second  << endl;
 } 

 out.close();
 
 // Display the accumulated time 
 cout << "The execution spends " << t.End() << " seconds" << endl; 
 getchar();

 return 1; 
}

//MergeSort Function

void MergeSort(pair<string,int>* A,int p ,int r)
{
    if(p<r){
        int q = (p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }

}

//Merge Function
void Merge(pair<string,int>* A, int p, int q, int r){
    int n1 = q-p+1;
    int n2 = r-q;
    pair<string,int>* L = new pair<string,int>[n1+1];
    pair<string,int>* R = new pair<string,int>[n2+1];
    for(int i=0;i<n1;++i){
        L[i]=A[p+i];
    }
    for(int i=0;i<n2;++i){
        R[i]=A[q+i+1];
    }

    //sorting
    int i=0;
    int j=0;
    for(int k=p ; k<=r; ++k){
        if(i==n1){
            A[k]=R[j];
            j = j+1;
        }
        else if(j==n2){
            A[k]=L[i];
            i = i+1;
        }
        else if(L[i].first<=R[j].first){
            A[k]=L[i];
            i = i+1;
        }
        else{
            A[k]=R[j];
            j = j+1;
        }
    }
    delete [] L;
    delete [] R;
}
