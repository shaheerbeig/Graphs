#include<iostream>
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

    graphs(int vertices){
        this->vertices = vertices;
        list = new Node*[vertices];
        for(int i=0;i<vertices;i++){
            list[i] = NULL;
        }
    }

    void addedge(int to , int from , bool direction){
        //0 means undirected
        //1 means directed

        Node *newnode = new Node(from);
        newnode->next = list[to];
        list[to] = newnode;

        if(direction == 0){
        Node *newnode2 = new Node(to);
        newnode2->next = list[from];
        list[from] = newnode2;
        }
    }

    void BFS(int startindex){
        queue<int>q;
        bool *visited = new bool[vertices];
        for(int i=0;i<vertices;i++){
            visited[i] = false;
        }
        visited[startindex] = true;
        q.push(startindex);
        while(!q.empty()){
            int val = q.front();
            q.pop();
            cout<<val<<" ";
            Node *curr = list[val];
            while(curr != NULL){
                if(visited[curr->data] == false){
                    q.push(curr->data);
                    visited[curr->data] = true;
                }
                curr = curr->next;
            }
        }
    }

void DFS(int startindex) {
    stack<int> s;
    bool* visit = new bool[vertices];
    for (int i = 0; i < vertices; i++) {
        visit[i] = false;
    }
    visit[startindex] = true; 
    s.push(startindex);
    while (!s.empty()) {
        int val = s.top();
        cout << val << " ";
        Node* ptr = list[val];
        while (ptr != NULL) {
            if (!visit[ptr->data]) {
                s.push(ptr->data);
                cout<<ptr->data<<" ";
                visit[ptr->data] = true;
                break;
            }
            else{
            ptr = ptr->next;
            }
        }
        if(ptr == NULL){
        s.pop();
        }
    }
}

    void print(){
        for(int i=1;i<vertices;i++){
            cout<<"Vertex "<<i<<" is connected to ";
            Node *curr = list[i];
                while(curr != NULL){
                cout<<curr->data;
                if(curr->next!= NULL){
                    cout<<",";
                }
                else{
                    cout<<".";
                }
                curr= curr->next;
            }
            cout<<endl;
        }
    }

};  

int main(){
    graphs g(5);
    g.addedge(1,2,1);
    g.addedge(1,3,0);
    g.addedge(3,4,0);
    g.addedge(4,5,1);
    cout<<"Printing adjancency list:"<<endl;
    g.print();
    cout<<endl;
    cout<<"Printing BFS: "<<endl;
    g.BFS(1);
    cout<<endl;
}