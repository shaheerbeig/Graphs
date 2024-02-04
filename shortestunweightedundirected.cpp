#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
// Node structure to represent a vertex in the graph
class Node {
    public:
    int data;
    Node* next;

    Node(int data){
        this->data = data;
        next  =NULL;
    }
};

class Graph {
    public:
    int numVertices;
    Node** adjacencyList;

public:
    // Constructor
    Graph(int vertices) {
        numVertices = vertices;
        adjacencyList = new Node*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = nullptr;
        }
    }

    // Function to add an edge to the graph
    void insertedge(int src, int dest ) {
        Node *newnode = new Node(dest);
        newnode->next = adjacencyList[src];
        adjacencyList[src] = newnode;

        Node *newnode2 = new Node(src);
        newnode2->next = adjacencyList[dest];
        adjacencyList[dest] = newnode2; 
    }

    void shortestunweighted(int startindex , int endindex){

        queue<int>q;
        int *arr = new int[numVertices] ;
        vector<int>v;
        arr[startindex] = -1;
        bool *visited = new bool[numVertices] {false};
        q.push(startindex);
        while(!q.empty()){
            int val = q.front();
            q.pop();
            visited[val] = true;

            Node *temp = adjacencyList[val];
            while(temp != NULL){
                if(visited[temp->data] == false){
                    arr[temp->data] = val;
                    q.push(temp->data);
                }
                temp = temp->next;
            }
        }
        v.push_back(endindex);
        while(endindex != startindex){
            endindex = arr[endindex];
            v.push_back(endindex); 
        }

       reverse(v.begin(),v.end());

        for(int i=0;i<v.size();i++){
            cout<<v.at(i)<<" ";
        }
    }
};

int main(){
    Graph g(5);
    g.insertedge(0,1);
    g.insertedge(0,2);
    g.insertedge(1,3);
    g.insertedge(2,3);
    g.insertedge(3,4);
    g.shortestunweighted(0,4);
}