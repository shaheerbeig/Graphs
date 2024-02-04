#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
class Node{
    public:
    int data;
    Node *next;

    Node(int data){
        this->data = data;
        next = NULL;
    }
};

class graphs{
    public:

    int vertices;
    Node **list;
    int *parent;

    graphs(int vertices) {
        this->vertices = vertices;
        list = new Node*[vertices];
        for (int i = 0; i < vertices; ++i) {
            list[i] = nullptr;
        }
        parent = new int[vertices];
        for(int i=0;i<vertices;i++){
            parent[i] = -1;
        }
    }


    // Function to add an edge to the graph
    void addEdge(int src, int dest ) {
        Node *temp = new Node(src);
        temp->next = list[dest];
        list[dest] = temp;

        Node *temp2 = new Node(dest);
        temp2->next = list[src];
        list[src] = temp2;
    }

    void findshortestpath(int startindex , int endindex){
        bool *visited = new bool[vertices] {false}; 
        vector<int>v;
        queue<int>q;
        q.push(startindex);
        while(!q.empty()){
            int val = q.front();
            q.pop();
            //cout<<val<<" ";
            visited[val] = true;
            Node *temp = list[val];
            while(temp != NULL){
                if(visited[temp->data] == false){
                    //cout<<temp->data<<" ";
                    visited[temp->data] = true;
                    parent[temp->data] = val;
                    //cout<<parent[temp->data]<<" ";
                    q.push(temp->data);
                    //cout<<endl;
                }
                temp = temp->next;
            }
        }
        v.push_back(endindex);
        while(endindex != startindex){
            endindex = parent[endindex];
            v.push_back(endindex);
        }
        for(int i=0;i<vertices;i++){
            cout<<v.at(i)<<" ";
        }
    }

    void print(){
        for(int i=0;i<vertices;i++){
            cout<<parent[i]<<" ";
        }
    }

     void DFS(int startindex , bool *visited , stack<int> &s){
        visited[startindex] = true;
        Node *temp = list[startindex];
        while(temp != NULL){
            if(visited[temp->data] == false){
                //visited[temp->data] = true;
                DFS(temp->data,visited,s);
            }
            temp = temp->next;
        }
        s.push(startindex);
    }

    //UISNG DFS APPROACH
    void topologicalsort(int startindex){
        bool *visited = new bool[vertices] {false}; 
        stack<int>s;
        int *arr = new int[vertices];
        DFS(startindex,visited,s);

        for(int i=0;i<vertices;i++){
            arr[i] = s.top();
            s.pop();
        }

        for(int i=0;i<vertices;i++){
            cout<<arr[i]<<" ";
        }
    }

    //printpath

    void allpath(int startindex , int endindex){
        int *arr = new int[vertices];
        bool *visited = new bool[vertices] {false};
        int i=0;
        DFSpath(startindex,endindex,arr,visited,i);
    }

    void DFSpath(int startindex , int endindex , int *arr , bool *visited , int i){

        visited[startindex] = true;
        arr[i] = startindex;
        i++;
        //if the start and end point is same print the whole path
        if(startindex == endindex){
            for(int j=0;j<i;j++){
                cout<<arr[j]<<" ";
            }
            cout<<endl;
        }
        else{
            Node *temp = list[startindex];
            while(temp != NULL){
                if(!visited[temp->data]){
                    DFSpath(temp->data,endindex,arr,visited,i);
                }
                temp = temp->next;
            }  
        }
        visited[startindex] = false;
    }
};

int main(){
    graphs g(8);
    g.addEdge(0,1);
    g.addEdge(0,4);
    g.addEdge(0,5);
    g.addEdge(1,2);
    g.addEdge(4,3);
    g.addEdge(5,6);
    g.addEdge(2,3);
    g.addEdge(6,7);
    g.addEdge(7,3);
    //g.findshortestpath(0,3);
    //g.print();
    cout<<endl;
    //g.topologicalsort(0);
    g.allpath(0,3);
}