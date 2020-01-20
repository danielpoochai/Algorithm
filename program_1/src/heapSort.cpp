#include <cstdio> 
#include <iostream> 
#include <fstream>
#include <vector>
#include "parser.h" 

void Build_Max_Heap(pair<string, int>*, int);
void Max_Heapify(pair<string, int>* , int, int);
void Heap_Sort(pair<string,int>*, int);

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
 //by dynamic array
pair <string, int>* copy_arr = new pair<string,int>[length];
for(int i=0; i<length; ++i){
    copy_arr[i].first = p.QueryString(i);
    copy_arr[i].second = i+1;
}

//HeapSort copy_arr
Heap_Sort(copy_arr,length-1);

//output the result
fstream out;
out.open(argv[2],ios::out);

 // Display all strings and word numbers 
 for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) 
 {   //cout << p.QueryString(i) << " " << p. QueryWordOrder(i)  << endl; 
     out << copy_arr[i].first<<" "<<copy_arr[i].second<<endl;
 } 
 
 // Display the accumulated time 
 cout << "The execution spends " << t.End() << " seconds" << endl; 

 getchar();
 
 return 1; 
} 

void Build_Max_Heap(pair<string,int>* A, int length){
    int heap_size=length;
    for(int i =(heap_size-1)/2; i>=0; i--){
        Max_Heapify(A,i,length);
    }
}

void Max_Heapify(pair<string, int>* A, int i, int length){
    int l = 2*i; //left
    int r = 2*i+1; //right
    int largest;
    if(l<=length && A[l]>A[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if(r<=length && A[r]>A[largest]){
        largest = r;
    }
    if (largest!=i){
        pair<string,int> tmp = A[i];
        A[i] = A[largest];
        A[largest] = tmp;
        Max_Heapify(A,largest,length);
    }
}   

void Heap_Sort(pair<string, int>* A, int length){
    int len = length;
    Build_Max_Heap(A, length);
    for(int i = length ; i>=0 ; --i){
        pair<string, int> tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        length = length-1;
        Max_Heapify(A,0,length);
    }
}