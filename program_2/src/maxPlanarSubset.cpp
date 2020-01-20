#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void maxplanarsubset(int*, int**, bool**, int);
void backtrace(int, int, bool**, int*, int*);

int main (int argc, char** argv)
{
    fstream in;
    in.open(argv[1],ios::in);
    if(in){
        int number;
        string line;
        getline(in, line, '\n');
        istringstream is(line);
        is>>number;
        int ** M = new int* [number]();
        bool ** S = new bool* [number]();
        for(int i=0; i<number; ++i){
            M[i] = new int[number]();
            S[i] = new bool[number]();
        }
        int* Chord = new int[number]; //Chord[j]=i
        int* Group = new int[number];
        for(int i=0; i<number; i++){
            Group[i]=-1;
        }
        for(int i=0; i<number/2; i++){
            if(getline(in,line,'\n')){
                istringstream templine(line);
                string vertex;
                getline(templine, vertex, ' ');
                int a = atoi (vertex.c_str());
                getline(templine, vertex, '\n');
                int b = atoi(vertex.c_str());
                Chord[b] = a;
                Chord[a] = b;
            }
        }  
        maxplanarsubset(Chord, M, S, number);
        backtrace(0,number-1,S,Group,Chord);      
        //output
        fstream out;
        out.open(argv[2], ios::out);

        out<<M[0][number-1]<<endl;
        for(int i=0; i<number; ++i){
            if(Group[i]!=-1){
                out<<i<<" "<<Group[i]<<endl;
            }
        }
    }
}

void maxplanarsubset(int* C, int** M, bool** S,int number)
{
    for(int j=0; j<number; ++j){
        int k = C[j];
        for(int i=0; i<j; ++i){
            if(k!=0){ 
                if(i<=k&&k<j&&((M[i][k-1]+1+M[k+1][j-1])>M[i][j-1])){
                    M[i][j]=M[i][k-1]+1+M[k+1][j-1];
                    S[i][j]=true; //C[j],j in group
                }
                else{
                    M[i][j]=M[i][j-1];
                    S[i][j]=false;
                }
            }
            else{ //k==0
                if(i<=k&&k<j&&((M[k+1][j-1]+1)>M[i][j-1])){
                    M[i][j]=M[k+1][j-1]+1;
                    S[i][j]=true;
                }
                else{
                    M[i][j]=M[i][j-1];
                    S[i][j]=false;
                }
            }
        }
    }
}

void backtrace(int i, int j, bool** S, int* G, int* C){
    if(i<j){
        if(S[i][j]==true){
            G[C[j]]=j;
            backtrace(i,C[j]-1,S,G,C);
            backtrace(C[j]+1,j,S,G,C);
        }
        else{
            backtrace(i,j-1,S,G,C);
        }
    } 
}