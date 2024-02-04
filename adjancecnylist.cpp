#include<iostream>
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

    void addedge(int to , int from , bool val){
        //bool val 0 means undirected 
        // bool val 1 means directed

        Node *newnode1 = new Node(from);
        newnode1->next = list[to];
        list[to] = newnode1;

        //means undircted so we will make another connection
        if(val == 0){
        Node *newnode2 = new Node(to);
        newnode2->next = list[from];
        list[from] = newnode2;            
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
    g.addedge(3,1,1);
    g.addedge(3,2,0);
    g.addedge(3,4,0);
    g.addedge(4,1,1);
    g.print();
}