#include<iostream>
#include<stack>
#include<vector>
#include<queue>

using namespace std;

class graphs{
    public:
    int vertices;
    int **matrix;

    //construtor
    graphs(int vertices){
        this->vertices = vertices;
        matrix = new int*[vertices];
        for(int i=0;i<vertices;i++){
            matrix[i] = new int[vertices];
            for(int j=0;j<vertices;j++){
                matrix[i][j] = 0;
            }
        }
    }

    void insertedge(int src , int dest){
        matrix[src][dest] = 1;        
    }

    void topo(int startindex){
        bool *visited = new bool[vertices] {false};
        stack<int>s;
        vector<int>v;
        topologicalsort(startindex,visited,s);
        for(int i=0;i<vertices;i++){
            v.push_back(s.top());
            s.pop();
        }
        for(int i=0;i<v.size();i++){
            cout<<v.at(i)<<" ";
        }
    }

    void topologicalsort(int startindex , bool *visited , stack<int>&s){
        visited[startindex] = true;
        for(int i=0;i<vertices;i++){
            if(visited[i] == false && matrix[startindex][i] == 1){
                topologicalsort(i,visited,s);
            }
        }
        s.push(startindex);
    }

    void kahnsalog(int startindex){
        int *Arr = new int[vertices] {0};
        vector<int>v;
        queue<int>q;
           for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (matrix[i][j] == 1) {
                    Arr[j]++;
                }
            }
        }

        //pushing all 0 degree wali nodes in the queue
        for(int i=0;i<vertices;i++){
            if(Arr[i] == 0){
                q.push(i);
            }
        }

        while(!q.empty()){
            int val = q.front();
            q.pop();
            v.push_back(val);

            for(int i=0;i<vertices;i++){
                if(matrix[val][i] == 1){
                    Arr[i] --;
                    if(Arr[i] == 0){
                        q.push(i);
                    }
                }
            }
        }
        for(int i=0;i<vertices;i++){
            cout<<v.at(i)<<" ";
        }
    }
};

int main(){
    graphs g(5);
    g.insertedge(0,1);
    g.insertedge(0,2);
    g.insertedge(1,3);
    g.insertedge(2,3);
    g.insertedge(3,4);
    g.topo(0);
    cout<<endl;
    g.kahnsalog(0);
}