#include<iostream>
#include<queue>
#include<limits.h>
#include<algorithm>
using namespace std;

class Node{
    public:
    int data;
    int weight;
    Node *next;
    
    Node(int vertex , int weight){
        this->weight = weight;
        this->data = vertex;
        next = NULL;
    }
};

//use to store the pairs with adjacent node and the disatnce
class pairs{
  public:
  int adj;
  int distance;
  
  pairs(int adj , int distance){
      this->distance = distance;
      this ->adj = adj;
  }
  pairs(){
      
  }
};

class priorityqueue{
    public:
    int size;
    int capacity;
    pairs *array;
    
    priorityqueue(int capacity){
        size = 0;
        this->capacity = capacity;
        array = new pairs[capacity] ;
    }
    
    void swap(pairs &a,pairs &b){
        pairs temp = a;
        a = b;
        b= temp;
        
    }
    //used when inserting value
    void heapifyup(int index){
        while(index > 0){
            int parent = index/2;
            if(array[parent].distance > array[index].distance){
                swap(array[parent], array[index]);
                index = parent;
            }
        }
    }
    //used when popping a value out
    void haepifydown(int value){
        int index =0;
        int smallest = index ; 
        int left = 2*smallest + 1;
        int right = 2*smallest + 2;
        
        if(left < size && array[left].distance < array[smallest].distance){
            smallest = left;
        }
        if(right < size && array[right].distance < array[smallest].distance){
            smallest = right;
        }
        if(smallest != index){
            swap(array[smallest] , array[index]);
            haepifydown(smallest);
        }
    }
    
    void push(pairs p){
        if(size == capacity){
            cout<<"Cannot enter in queue"<<endl;
        }
        else{
        array[size] = p;
        size++;
        heapifyup(size-1);
        }
    }
    
    void pop(){
        if(size == 0){
            cout<<"Cannot pop queue empty"<<endl;
        }
        else{
            array[0] = array[size-1];
            size--;
            haepifydown(0);
        }
    }

    bool isempty(){
        if(size == 0)
        {
            return true;
        }
        else{
            return false;
        }
    }

    pairs front(){
        if(!isempty()){
            return array[0];
        }
        else{
            return {-1,-1};
        }
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
    
    void insertedge(int src , int det , int weight){
        Node *newnode = new Node(src,weight);
        newnode->next = list[det];
        list[det] = newnode;
        
        Node *newnode2 = new Node(det,weight);
        newnode2->next = list[src];
        list[src] = newnode2;
    }

    void dijktras(int startindex){
        //vertices define the capacity of the priority queue
        int *distance = new int[vertices];
        for(int i=0;i<vertices;i++){
            distance[i] = INT_MAX;
        }

        priorityqueue p(vertices);
        //initially startindex wala disatnce 0 ha
        distance[startindex] = 0;
        //queue mai startindex ka sath 0 pass kardiya 
        pairs p1(startindex,0);
        p.push(p1);
        while(!p.isempty()){
            pairs val = p.front();
            p.pop();
            cout<<val.adj<<" "<<val.distance<<endl;
            Node *temp = list[val.adj];
            while(temp != NULL){
                if(temp->weight + distance[val.adj] < distance[temp->data]){
                    distance[temp->data] =temp->weight + distance[val.adj] ;
                    cout<<"temp->data: "<<temp->data<<endl;
                    cout<<"distance of temp->data: "<<distance[temp->data]<<endl;
                    pairs p1(temp->data,distance[temp->data]);
                    p.push(p1);
                }
                temp = temp->next;
            }
        }
        for(int i=0;i<vertices;i++){
            cout<<distance[i]<<" ";
        }
    }
};

int main() {
    int V = 6;
    graphs graph(V);
    int *ptr;
    graph.insertedge(0, 1, 4);
    graph.insertedge(0, 2, 4);
    graph.insertedge(1, 2, 2);
    graph.insertedge(2, 3, 3);
    graph.insertedge(2, 3, 7);
    graph.insertedge(2, 5, 6);
    graph.insertedge(2, 4, 1);
    graph.insertedge(4 , 5 ,2);
    graph.insertedge(3 , 5 ,3);
    graph.dijktras(0);
}