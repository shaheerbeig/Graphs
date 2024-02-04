#include<iostream>
#include<vector>
using namespace std;

class Node{
    public:
    int destination;
    int weight;
    Node *next;

    Node(int destination , int weight){
        this->destination = destination;
        this->weight = weight;
        next = NULL;
    }

};

//priority queue ma hum aik pair bhejainga jisko min heap ka according solve karainga. The pair will have a  destinantionnode or uska weight. if we would
//have been asked for MST we will amke a parent to keep its track.
class Pairs{
    public:
    int destinationnode;
    int weight;

    Pairs(int  destinationnode , int weight){
        this-> destinationnode =  destinationnode;
        this->weight = weight;  
    }
    Pairs(){
        destinationnode = 0;
        weight = 0;
    }
};

class PriorityQueue{
    public:
    //is table ka andar hum pairs ko push karainga
    Pairs *table;
    int size;
    int capacity;

    PriorityQueue(int capacity){
        this->capacity = capacity;
        this->size = 0;
        table = new Pairs[capacity];
    }

    //swapping of the pair values
    void swap(Pairs &p1 , Pairs &p2){
        Pairs temp = p1;
        p1 = p2;
        p2 = temp;
    }

    void heapifyUp(int index){
        while(index > 0){
            int parent = index-1 /2;
            if(table[index].weight < table[parent].weight){
                swap(table[index],table[parent]);
                index = parent;
            }
            else{
                break;
            }
        }
    }

    void push(Pairs p){
        if(size == capacity){
            cout<<"Queue is Full cannot enter more"<<endl;
        }
        else{
            table[size] = p;
            size++;
            heapifyUp(size-1);
        }
    }

    void heapifyDown(int index){
        int smallest = index;
        int leftchild = 2*index + 1 ;
        int rightchild = 2*index + 2;

        if(leftchild < size && table[leftchild].weight < table[smallest].weight){
            smallest = leftchild;
        }
        if(rightchild < size && table[rightchild].weight < table[smallest].weight){
            smallest = rightchild;
        }
        if(smallest != index){
            swap(table[smallest],table[index]);
            heapifyDown(smallest);

        }
    }

    void pop(){
        if(size == 0){
            cout<<"Cannot pop further"<<endl;
        }
        else{
            table[0] = table[size-1];
            size--;
            heapifyDown(0);
        }
    }

    Pairs top(){
        if(size == 0){
            cout<<"No element to return "<<endl;
        }
        Pairs val = table[0];
        return val;
    }

    bool isempty(){
        if(size == 0){
            return true;
        }
        else{
            return false;
        }
    }
};

class Graph{
    public:
    int vertices;
    Node **list;

    Graph(int vertices){
        this->vertices = vertices;
        list = new Node*[vertices];
        for(int i=0;i<vertices;i++){
            list[i] = NULL;
        }
    }

    //undirected edge insertion
    void insertEdge(int src , int dest , int weight){
        Node *tempnode1 = new Node(src,weight);
        tempnode1->next = list[dest];
        list[dest] = tempnode1; 

        Node *tempnode2 = new Node(dest,weight);
        tempnode2->next = list[src];
        list[src] = tempnode2;         
    }

    int primsalgo(int startindex){
        //keep track of visited vertices
        bool *visited = new bool[vertices] {false};
        Pairs *MST = new Pairs[vertices];
        PriorityQueue pq(vertices);
        int sum= 0;
        Pairs p(startindex,0);
        pq.push(p);
        int i=0;
        while(!pq.isempty()){
            Pairs val = pq.top();
            pq.pop();
            
            if(visited[val.destinationnode] == false){
                sum += val.weight;
                visited[val.destinationnode] = true;
                Pairs p(val.destinationnode,val.weight);
                MST[i] = Pairs(val.destinationnode,val.weight);
                i++;
                Node *temp = list[val.destinationnode];
                while(temp != NULL){
                    if(visited[temp->destination] == false){
                        Pairs p(temp->destination,temp->weight);
                        pq.push(p);
                    }
                    temp = temp->next;
                } 
            }
        }
        cout<<"Edge - Weight"<<endl;
        for(int i=0;i<vertices;i++){
            cout<<MST[i].destinationnode<<"     |    "<<MST[i].weight<<endl;
        }
        return sum;
    }
};  

int main(){
    Graph g(5);
    g.insertEdge(0,1,1);
    g.insertEdge(0,2,2);
    g.insertEdge(1,4,7);
    g.insertEdge(1,3,5);
    g.insertEdge(2,3,4);
    g.insertEdge(3,4,3);

    cout<<"The Sum Of The MST is "<<g.primsalgo(0); 
}