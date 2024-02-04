#include<iostream>
using namespace std;
class Graph{
	public:
		int** matrix;
		int vertices;
		int edges;
		
		Graph(int n){
			vertices = n;
			
			matrix = new int*[n];
			for (int i = 0; i < n; i++)
				matrix[i] = new int[n];
				
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					matrix[i][j] = 0;
			
			edges = 0;
		}
		
		void addEdge(int from, int to){
			matrix[from][to] = 1;
			edges++;
			return;
		}
		
		void printMatrix(){
			for (int i = 0; i < vertices; i++){
				for (int j = 0; j < vertices; j++){
					cout << matrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		
		void printMatrix(int** m){
			for (int i = 0; i < vertices; i++){
				for (int j = 0; j < vertices; j++){
					cout << m[i][j] << " ";
				}
				cout << endl;
			}
		}
		
		bool checkSame(int** m2){
			bool flag = true;
			for (int i = 0; i < vertices; i++){
				for (int j = 0; j < vertices; j++){
					if (matrix[i][j] != m2[i][j]){
						flag = false;
						break;
					}
				}
			}
			
			return flag;
		}
		
		int** swapRows(int** m, int tr1, int tr2){
			int** newMatrix = new int*[vertices];
			for (int i = 0; i < vertices; i++)
				newMatrix[i] = new int[vertices];
			
			for (int i = 0; i < vertices; i++)
				for (int j = 0; j < vertices; j++)
					newMatrix[i][j] = m[i][j];
			
			for (int i = 0; i < vertices; i++)
				swap(newMatrix[tr1][i], newMatrix[tr2][i]);
			
			for (int i = 0; i < vertices; i++)
				swap(newMatrix[i][tr1], newMatrix[i][tr2]);
			
			//cout << "(swapping done for " << tr1 << ", and " << tr2 << ")\n";
			return newMatrix;
		}
		
		bool checkIsomorphic(int** m2){
			if (checkSame(m2)){
				return true;
			}
			
			int i = 0;
			int j = 1;
			while(i != vertices - 1){
				//cout << "swapping " << i << ", and " << j << endl;
				int** tempMatrix = swapRows(m2, i, j);
				
				//cout << "Checking:\n";
				//printMatrix();
				//cout << "and:\n";
				//printMatrix(tempMatrix);
				if (checkSame(tempMatrix)){
					return true;
				}
				
				j++;
				if (j == vertices){
					i++;
					j = i+1;
				}
			}
			
			return false;
		}
};

int main(){
	Graph g1(4);
	g1.addEdge(0, 1);
	g1.addEdge(0, 3);
	g1.addEdge(1, 3);
	g1.addEdge(2, 0);
	g1.addEdge(2, 3);
	g1.addEdge(3, 0);
	g1.addEdge(3, 1);
	
	cout << "Graph1:\n";
	g1.printMatrix();
	cout << endl;
	
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(0, 3);
	g2.addEdge(1, 0);
	g2.addEdge(1, 3);
	g2.addEdge(2, 0);
	g2.addEdge(2, 1);
	g2.addEdge(3, 1);
	
	cout << "Graph2:\n";
	g2.printMatrix();
	cout << endl;
	
	
	if (g1.checkIsomorphic(g2.matrix)){
		cout << "They are isomorphic\n";
	}else{
		cout << "Not isomorphic\n";
	}
	
	
	return 0;
}