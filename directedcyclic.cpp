#include<iostream>
#include<queue>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    Node(int data){
        this->data = data;
        next = NULL;
    }
};

class pairs{
    public:
    int data;
    bool value;

    pairs(int data , bool value){
        this->data = data;
        this->value = value;
    }

    pairs(){

    }
};

class Graph{
    public:
    int vertices;
    Node **list;
    Graph(int size){
        vertices  = size;
        list = new Node*[vertices];
        for(int i=0;i<vertices;i++){
            list[i] = NULL;
        }
    }

    //creating a directed graph
    void addEdge(int src , int dest){
        //0 val undirected
        //1 val directed
        Node *newnode = new Node(dest);
        newnode->next = list[src];
        list[src] = newnode;

        /*Node *newnode2 = new Node(src);
        newnode2->next = list[dest];
        list[dest] = newnode2;
        */ 
    }

    bool checkdirectedDFS(){
        pairs *visited = new pairs[vertices] {{0,false}};
        pairs *dfsvisited = new pairs[vertices] {{0,false}};
        for(int i=0;i<vertices;i++){
            if(visited[i].value == false){
                bool cycle = checkDFS(i,visited,dfsvisited);
                if(cycle == true){
                    return true;
                }
            }
        }
        return false;
    }

    bool checkDFS(int startindex , pairs *visited , pairs *dfsvivited){
        visited[startindex].value = true;
        dfsvivited[startindex].value = true;

        Node *temp = list[startindex];
        while(temp != NULL){
            if(visited[temp->data].value ==false){
                bool cycled = checkDFS(temp->data,visited,dfsvivited);
                if(cycled == true){
                    return true;
                }
            }
            else if(visited[temp->data].value == true && dfsvivited[temp->data].value == true){
                return true;
            }
            temp = temp->next;
        }
        dfsvivited[startindex].value = false;
        return false;
    }

    void printGraph() {
        for (int i = 0; i < vertices; ++i) {
            std::cout << "Adjacency list for vertex " << i << ": ";
            Node* current = list[i];
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};
int main(){
    Graph graph(6);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(3, 1);
    graph.addEdge(2, 4);
    graph.addEdge(4, 3);
    graph.addEdge(4, 5);
    graph.printGraph();

    if(graph.checkdirectedDFS()){
        cout<<"Cycle exsists"<<endl;
    }
    else{
        cout<<"No Cycle"<<endl;
    }
}

    