#include <queue>
#include "parser.h"
#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <climits>
#include <math.h>
#include <fstream>

using namespace std;

class node;
class comparison;
double** Initial_H_Weight_matrix(int H, int V, int capacity);
double** Initial_V_Weight_matrix(int H, int V, int capacity);
vector<pair<int,int> > Dijkstra(node** N, double** W_h, double** W_v, int H, int V, pair<int,int> start, pair<int,int> end, int capacity);
vector<pair<int,int> > Construct_Path(node* end, node** N, double** W_H, double** W_V, int capacity);
void Initialize_N_matrix(node** N, int H, int V);
void Initialize_Single_Source(node** N, pair<int,int> start);
void make_adjacent_list(node** N,int H, int V);
void Relax(node* u, node* v, double** W_H, double** W_V, priority_queue<node*,vector<node*>, comparison> &);
void reset_predecessor_n_distance_n_explored(node** N, int H, int V);

class node{
public:
    node();
    node(pair<int,int> cor, int width, pair<int,int> pre);

    bool operator < (const node& B){
        if (distance < B.distance){
            return true;
        }
        return false;
    }
    bool operator > (const node& B){
        if (distance > B.distance){
            return true;
        }
        return false;
    }
    //set 
    void set_predecessor(pair<int,int> pre){
        predecessor = pre ;
    }
    void set_distance(int dis){
        distance = dis;
    }
    void set_explored(bool a){
        explored = a;
    }
    //get
    bool get_explored(){
        return explored;
    }
    int get_id(node) {
        return node_id;
    }
    int get_distance()const{
        return distance;
    }
    void update_adjacent_list(node* n){
        adjacent_list.push_back(n);
    }
    vector<node*> get_adjacent_list(){
        return adjacent_list;
    }
    pair<int,int> get_cor()const{
        return original_cor;
    };
    pair<int,int> get_predecessor(){
        return predecessor;
    }
private:
    bool explored; 
    int node_id; 
    double distance;
    pair<int,int> predecessor;
    pair<int,int> original_cor;
    vector<node*> adjacent_list;
};

node:: node(){
    node_id = -1;
    original_cor = make_pair(-1,-1);
    distance = INT_MAX;
    predecessor = make_pair(-1,-1);
    explored = false;
}
node:: node(pair<int,int> cor, int width, pair<int,int> pre){
    node_id = cor.first + cor.second * width;
    original_cor = cor;
    distance = INT_MAX;
    predecessor = pre;
    explored = false;
}

class comparison{
public:
    bool operator ()(node* &A, node* &B){
        return A->get_distance() > B->get_distance();
    }
};

void Initialize_N_matrix(node** N, int H, int V){
    for(int i=0; i<H; ++i){
        for(int j=0; j<V; ++j){
            pair<int,int> cor (i,j);
            pair<int,int> pre (-1,-1);
            node n = node(cor,H,pre);
            N[i][j] = n;
        }
    }
}

void Initialize_Single_Source(node** N, pair<int,int> start){
    N[start.first][start.second].set_distance(0);
}

double** Initial_H_Weight_matrix(int H, int V, int capacity){
    //construct horizontal edge Weight matrix H-1xV
    double** W_h = new double* [H-1];
    for(int i=0; i<H-1; ++i){
        W_h[i] = new double[V];
    }
    for(int i=0; i<H-1; ++i){
        for(int j=0; j<V; ++j){
            W_h[i][j] = pow(2, (double)1/capacity);
        }
    }
    return W_h;
}

double** Initial_V_Weight_matrix(int H, int V, int capacity){
    //construct vertical edge weight matrix HxV-1
    double** W_v = new double* [H];
    for(int i=0; i<H; ++i){
        W_v[i] = new double[V-1];
    }
    for(int i=0; i<H; ++i){
        for(int j=0; j<V-1; ++j){
            W_v[i][j] = pow(2,(double) 1/capacity);
        }
    }
    return W_v;
}

void check_Q(priority_queue<node*,vector<node*>, comparison> Q){
        //cerr<< Q.top()->get_distance()<<endl;
        cerr<< Q.top()->get_cor().first<<" "<<Q.top()->get_cor().second<<endl;
        /*for(int i = 0; i<Q.top()->get_adjacent_list().size(); ++i){
            cerr<<"adj"<< Q.top()->get_adjacent_list()[i]->get_cor().first<<" "<<Q.top()->get_adjacent_list()[i]->get_cor().second<<endl;
        }*/
}

vector<pair<int,int> > Dijkstra(node** N, double** W_h, double** W_v, int H, int V, pair<int,int> start, pair<int,int> end, int capacity){
    Initialize_Single_Source(N,start);
    priority_queue<node*, vector<node*>, comparison> Q;
    Q.push(&N[start.first][start.second]);
    while(!Q.empty()){
        bool leave = false;
        node* out = Q.top();
        while(out->get_explored()){
            Q.pop();
            if(Q.empty()){
                leave = true;
                break;
            }
            out = Q.top();
        }
        if(leave){
            break;
        }
        vector<node*> adj_list = out->get_adjacent_list(); 
        for(int i=0; i < adj_list.size(); ++i){
            Relax(out, adj_list[i], W_h, W_v, Q);
        }
        Q.pop();
        out->set_explored(true);
    }
    vector<pair<int,int> >re_path = Construct_Path(&(N[end.first][end.second]),N,W_h,W_v,capacity);
    //Q = priority_queue<node*,vector<node*>, comparison> ();
    return re_path;
}

void make_adjacent_list(node** N,int H, int V){
    for(int i=0; i<H; ++i){
        for(int j=0; j<V ; ++j){
            int x_cor = N[i][j].get_cor().first;
            int y_cor = N[i][j].get_cor().second;
            if(x_cor==0){ //add right neighbor
                N[i][j].update_adjacent_list(&(N[i+1][j]));
            }
            else if(x_cor==H-1){ //add left neighbor
                N[i][j].update_adjacent_list(&(N[H-2][j]));                
            }
            else{
                N[i][j].update_adjacent_list(&(N[i+1][j]));
                N[i][j].update_adjacent_list(&(N[i-1][j]));
            }
            if(y_cor==0){
                N[i][j].update_adjacent_list(&(N[i][j+1]));
            }
            else if(y_cor==V-1){
                N[i][j].update_adjacent_list(&(N[i][V-2]));
            }
            else{
                N[i][j].update_adjacent_list(&(N[i][j-1]));
                N[i][j].update_adjacent_list(&(N[i][j+1]));
            }    
        }
    }
}

void Relax(node* u, node* v, double** W_H, double** W_V, priority_queue<node*, vector<node*>, comparison> &Q){
    pair<int,int> u_cor = u->get_cor();
    pair<int,int> v_cor = v->get_cor();
    //call W_V
    if(u_cor.first == v_cor.first){
        if(v->get_distance()>u->get_distance()+W_V[(u_cor.first+v_cor.first)/2][(u_cor.second+v_cor.second)/2]){
            v->set_distance(u->get_distance()+W_V[(u_cor.first+v_cor.first)/2][(u_cor.second+v_cor.second)/2]);
            v->set_predecessor(u_cor);
            Q.push(v);
        }
    } 
    //call W_H
    else{
        if(v->get_distance()>u->get_distance()+W_H[(u_cor.first+v_cor.first)/2][(u_cor.second+v_cor.second)/2]){
            v->set_distance(u->get_distance()+W_H[(u_cor.first+v_cor.first)/2][(u_cor.second+v_cor.second)/2]);
            v->set_predecessor(u_cor);
            Q.push(v);
        }
    }
}

vector<pair<int,int> > Construct_Path(node* end, node** N, double** W_H, double** W_V, int capacity){
    vector<pair<int,int> > reverse_path;
    reverse_path.push_back(end->get_cor());
    while(end->get_predecessor()!=make_pair(-1,-1)){
        pair<int,int> now = end->get_cor();
        pair<int,int> pre = end->get_predecessor();
        reverse_path.push_back(pre);
        end = &N[pre.first][pre.second];
        //update W_V
        if(now.first==pre.first){
            W_V[(now.first+pre.first)/2][(now.second+pre.second)/2] += 1;
            W_V[(now.first+pre.first)/2][(now.second+pre.second)/2] *= pow(2,(double)1/capacity);
            W_V[(now.first+pre.first)/2][(now.second+pre.second)/2] -= 1;
        }
        //update W_H
        else{
            W_H[(now.first+pre.first)/2][(now.second+pre.second)/2] += 1;
            W_H[(now.first+pre.first)/2][(now.second+pre.second)/2] *= pow(2,(double)1/capacity);
            W_H[(now.first+pre.first)/2][(now.second+pre.second)/2] -= 1;
        }
    }
    return reverse_path;
}

void reset_predecessor_n_distance_n_explored(node** N, int H, int V){
    for(int i=0; i<H; ++i){
        for(int j=0; j<V; ++j){
            N[i][j].set_predecessor(make_pair(-1,-1));
            N[i][j].set_distance(INT_MAX);
            N[i][j].set_explored(false);
        }
    }
}


int main(int argc, char **argv)
{
    if( argc < 2 ){ cout << "Usage: ./parser [input_file_name]" << endl; return 1; }

    AlgParser parser;

    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }

    //Initialize output file
    fstream out;
    out.open(argv[2], ios::out);

    //grid information
    int H = parser.gNumHTiles();
    int V = parser.gNumVTiles();
    int capacity = parser.gCapacity();
    int nets = parser.gNumNets();

    //Initialize N matrix
    node** N = new node* [H];
    for(int i=0; i<H; ++i){
        N[i] = new node[V];
    }
    Initialize_N_matrix(N, H, V);
   //Initialize weight_matrix
    double** W_h = Initial_H_Weight_matrix(H, V, capacity);
    double** W_v = Initial_V_Weight_matrix(H, V, capacity);
    //Initialize adjacent list
    make_adjacent_list(N,H,V);

    //store the results
    vector<pair<int,int> >* results = new vector<pair<int,int> > [nets]; 
    
    //determined the routing order
    vector<pair<double,int> > order; //order[i] = (how many pins in box_i (i_th net),idNet)
    for(int i=0; i<nets; ++i){
        order.push_back(make_pair(0.0,i));
    }
    bool** Box = new bool* [H]; //store the pins
    for(int i=0; i<H; ++i){
        Box[i] = new bool [V];
    }
    for(int i=0;i<H;++i){
        for(int j=0; j<V;++j){
            Box[i][j]=false;
        }
    }
    for(int idNet = 0; idNet < nets;  ++idNet){
        pair<int,int> start = parser.gNetStart(idNet);
        pair<int,int> end = parser.gNetEnd(idNet);
        Box[start.first][start.second] = true;
        Box[end.first][end.second]= true;
    }
    
    //construct order with boxing and manhattan distance
    for(int idNet = 0; idNet<nets; ++idNet){
        pair<int,int> start = parser.gNetStart(idNet);
        pair<int,int> end = parser.gNetEnd(idNet);
        double h = (double)H/2;
        double v = (double)V/2;
        double upper_bound = (double)(H+V);
        int distance = abs(start.first-end.first)+abs(start.second-end.second);
        order[idNet].first = order[idNet].first + upper_bound - (double)(distance);
        double dis_cen = abs((double)((start.first+end.first)/2)-h) + abs((double)((start.second+end.second)/2)-v);
        order[idNet].first = order[idNet].first + (upper_bound-dis_cen);
        if(start.first<end.first){
            for(int i=start.first; i<=end.first; ++i){
                if(start.second<end.second){
                    for(int j=start.second; j<=end.second; ++j){
                        if(Box[i][j]==true){
                            if(make_pair(i,j)!=start&& make_pair(i,j)!=end){
                                order[idNet].first += 1;}}}}
                else{
                    for(int j=end.second; j<=start.second; ++j){
                        if(Box[i][j]==true){
                            if(make_pair(i,j)!=start&& make_pair(i,j)!=end){
                                order[idNet].first += 1;}}}}}}
        else{
            for(int i=end.first; i<=start.first; ++i){
                if(start.second<end.second){
                    for(int j=start.second; j<=end.second; ++j){
                        if(Box[i][j]==true){
                            if(make_pair(i,j)!=start&& make_pair(i,j)!=end){
                                order[idNet].first += 1;}}}}
                else{
                    for(int j=end.second; j<=start.second; ++j){
                        if(Box[i][j]==true){
                            if(make_pair(i,j)!=start&& make_pair(i,j)!=end){
                                order[idNet].first += 1;}}}}}}
    }
    sort(order.begin(),order.end());

    for (int idNet = 0; idNet < nets; ++idNet){
        pair<int,int> start = parser.gNetStart(order[idNet].second);
        pair<int,int> end = parser.gNetEnd(order[idNet].second);
        vector<pair<int,int> > subresult;
        subresult=(Dijkstra(N, W_h, W_v, H, V, start, end, capacity));
        reset_predecessor_n_distance_n_explored(N, H, V);

        //output result
        int size = subresult.size();
        out << order[idNet].second << " " << size-1 << endl;
        out << subresult[size-1].first << " " << subresult[size-1].second << " "; 
        for(int i=size-2; i>0; --i){
            out << subresult[i].first << " " << subresult[i].second << endl;
            out << subresult[i].first << " " << subresult[i].second << " ";
        }
        out << subresult[0].first << " " << subresult[0].second<<endl;
        subresult.resize(0);
    }
    out.close();
    //delete N n Box
    for(int i=0 ; i<H ; ++i){
        delete [] N[i];
        delete [] Box[i];
    }
    delete [] N;
    delete [] Box;
    //delete W
    for(int i=0; i<H-1; ++i){
        delete[] W_h[i];
    }
    delete[] W_h;
    for(int i=0; i<V-1; ++i){
        delete[] W_v[i];
    }
    delete[] W_v;  
    return 0;
}

