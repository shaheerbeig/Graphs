#include<iostream>
using namespace std;
class Pairs{
    public:
    int src;
    int dest;
    int weight;

    Pairs(int s , int d , int w){
        this->weight = w;
        this->src = s;
        this->dest = d;
    }
    Pairs(){
        src = weight = dest = 0;
    }

};

//sorting global function
void swap(Pairs& a, Pairs& b) {
    Pairs temp = a;
    a = b;
    b = temp;
}
// Partition function for quicksort
int partition(Pairs arr[], int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].weight <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
// Quicksort function
void quicksort(Pairs arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void print(Pairs arr[] , int size){
    for(int i=0;i<size;i++){
        cout<<"DEST: "<<arr[i].dest<<" SRC: "<<arr[i].src<<" Weight: "<<arr[i].weight<<endl;
    }
}

class Graphs{
    int vertices;
    Pairs *array;
    public:
    Graphs(int vertices){
        this->vertices = vertices;
        array = new Pairs[vertices];
    }

    //initializing the arrays with respective values
    void initializearrays(int *parent , int *rank , int vertices){
        for(int i=0;i<vertices;i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findparent(int *parent , int node){
        if(parent[node] == node){
            return parent[node];
        }
        return parent[node] = findparent(parent,parent[node]);
    }
    //making unioin of the disjoint components
    void getunion(int v , int u ,int *parent , int *rank){
        v = parent[v];
        u = parent[u];

        if(rank[v] < rank[u]){
            parent[v] = u;
        }
        else if(rank[u] < rank[v]){
            parent[u] = v;
        }
        else if(rank[u] == rank[v]){
            parent[v] = u;
            rank[u] ++;
        }
    }

    int Kruskals(int vertices , Pairs *p , int edges){
        int *parent = new int[vertices];
        int *rank = new int[vertices];
        initializearrays(parent,rank,vertices);
        //this function will perform the sort on basis of the weight
        quicksort(p,0,edges-1);
        int TOTALMSTWEIGHT=0;
        for(int i=0;i<edges;i++){
            // in dono values ka parents niklainga
            int s = findparent(parent,p[i].src);
            int d = findparent(parent,p[i].dest);
            int weight = p[i].weight;
            // if the values dont have same parents means are different components
            if(s != d){
                getunion(s,d,parent,rank);
                TOTALMSTWEIGHT += weight;
            }
        }
        return TOTALMSTWEIGHT;
    }
};

int main(){
    int edges,src , dest , weight;
    int V=6;
    Pairs *array;
    cout<<"Enter edges: ";
    cin>>edges;
    array = new Pairs[edges];
    for(int i=0;i<edges;i++){
        cout<<"Enter src , dest , weight:";
        cin>>src>>dest>>weight;
        array[i] = Pairs(src,dest,weight);
    }
    Graphs g(V);
    print(array,edges);
    cout<<"Sum of MST is: "<<g.Kruskals(V,array,edges);
}