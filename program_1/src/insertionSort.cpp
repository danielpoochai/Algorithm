#include <cstdio> 
#include <iostream> 
#include <vector>
#include <fstream>
#include "parser.h" 
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
/*copy the lex_string_vector by vector
vector <pair<string,int>> copy_lex;
for(int i=0; i<length; ++i){
    pair<string,int> now(p.QueryString(i),i);
    copy_lex.push_back(now);
}*/

//copy the lex_string_vector by dynamic array
pair<string,int>* copy_arr = new pair<string,int>[length];
for(int i=0; i<length; ++i){ 
    copy_arr[i].first=p.QueryString(i);
    copy_arr[i].second=i+1;
}

/*insertion sort copy_lex
for(int i=1; i<length; ++i){
    pair<string,int> key = copy_lex.at(i);
    int j = i-1;
    while(j>=0 && copy_lex.at(j).first>key.first){
        copy_lex.at(j+1)=copy_lex.at(j);
        j=j-1;
    }
    copy_lex.at(j+1)=key;
}*/

//insertion sort copy_arr
for(int i=1; i<length; ++i){
    pair<string,int> key = *(copy_arr+i);
    int j = i-1;
    while(j>=0 && (*(copy_arr+j)).first>key.first){
        *(copy_arr+j+1)=*(copy_arr+j);
        j=j-1;
    }
    (*(copy_arr+j+1))=key;
}


//count the appear position 

/*vector <pair<bool, int>> position;
for(int i=0; i<length; ++i){
    pair<bool,int> now(false,-1);
    position.push_back(now);
}
for(int i=0; i<length; ++i){
    string key = copy_lex.at(i);
    for(int j=0; j<length; ++j){
        if(p.QueryString(j)==key&&position.at(j).first==false){
            position.at(j).first=true;
            position.at(i).second=j;
            break;
        }
    }
}*/

//output result
fstream out;
out.open(argv[2],ios::out);

 // Display all strings and word numbers 
 for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ ) 
 {  // cout << copy_lex.at(i).first << " " << copy_lex.at(i).second  << endl; 
    //cout<< (*(copy_arr+i)).first<<" "<<(*(copy_arr+i)).second<< endl;
    out<< (*(copy_arr+i)).first<<" "<<(*(copy_arr+i)).second<< endl;
 } 
 
 out.close();
 // Display the accumulated time 
 cout << "The execution spends " << t.End() << " seconds" << endl; 
 getchar();

 return 1; 
}