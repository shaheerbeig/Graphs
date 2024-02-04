#include<iostream>
using namespace std;

class graphs{
    public:
    int vertices;
    int **matrix;
    int *parent;
    int *rank;

    graphs(int vertices) {
        this->vertices = vertices;
        matrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            matrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                matrix[i][j] = 0;
            }
        }
        parent = new int[vertices];
        rank = new int[vertices];
    }

    void addedge(int s , int d){
        matrix[s][d] = matrix[d][s] = 1;
    }

    void initializeparent(){
        for(int i=0;i<vertices;i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findparent(int n){
        if(parent[n] == n){
            return parent[n];
        }
        else{
            return parent[n] = findparent(parent[n]);
        }
    }

    void unions(int i , int j){
        int u = parent[i];
        int v = parent[j];

        if(rank[u] < rank[v]){
            parent[u] = v;
        }
        else if(rank[v] < rank[u]){
            parent[v] = u;
        }
        else if(rank[v] == rank[u]){
            parent[v] = u;
            rank[u]++;
        }
    }

    int numprovinces(){
        bool *visited = new bool[vertices] {false};
        initializeparent();
        for(int i=0;i<vertices;i++){
            for(int j=0;j<vertices;j++){
                if(matrix[i][j] == 1){
                    unions(i,j);
                }
            }
        }
        int ctr=0;
        for(int i=0;i<vertices;i++){
            if(parent[i] == i){
                ctr++;
            }
        }
        return ctr;
    }
};

int main(){
    graphs g(5);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(1,3);
    g.addedge(1,4);
    g.addedge(2,3);
    g.addedge(2,4);
    g.addedge(4,3);
    cout<<"Provinces are: "<<g.numprovinces();
}