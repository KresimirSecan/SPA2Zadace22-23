#include <iostream>
#include <vector>

using namespace std;
class Graph
{
private:
    vector<vector<int>> AMatrix;

    int totalWeightOfGraph(vector<vector<int>> adjMatrix)
    {
        int totalweight = 0;
        int n = adjMatrix.size();

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if(j + i < n)
                    totalweight += adjMatrix[i][j + i];

        return totalweight;   
    }

    void printGraph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                if(adjMatrix[i][j + i] != 0  && j + i < n)
                    cout << i << " - " << j + i << " (" << adjMatrix[i][j + i] << ")" << endl;
        } 
    }
    
    pair<int, int> findMinWeightIndex(vector<int> visited)
    {
        //index i minvalue
        int index = 1e9;
        int minValue = 1e9;
        int start = 1e9;

        for (int i = 0; i < visited.size(); ++i)
        {
            if(visited[i] == 1)
            {
                for (int j = 0; j < visited.size(); ++j)
                {
                    if(AMatrix[i][j] != 0 && AMatrix[i][j] < minValue && visited[j] == 0)
                    {
                        minValue = AMatrix[i][j];
                        index = j;
                        start = i;
                    }
                }
            }
        }
        
        return make_pair(start, index);
    }

    int find(int i, vector<int> &parent)
    {
        while(parent[i] != i)
            i = parent[i];

        return i;
    }

    void union_new(int i, int j, vector<int> &parent)
    {
        int a = find(i, parent);
        int b = find(j, parent);

        parent[a] = b;
    }

public:

    //konstruktor, paziti na kopiranje
    Graph(vector<vector<int>> &adjMatrix)
    {
        AMatrix = adjMatrix;
    }

    int GraphWeight()
    {
        return totalWeightOfGraph(AMatrix);
    }

    void print()
    {
        printGraph(AMatrix);
    }

    Graph primMST()
    {
        //pokupi dimenziju grafa nad kojim radimo mst
        int n = AMatrix.size();

        //napravi praznu matricu susjedstava
        vector<vector<int>> matrix(n, vector<int>(n, 0));

        //indikatori posjecenosti
        vector<int> visited(n, 0);

        //proizvoljno posjecen vrh, nije bitno ali krecemo od 0
        visited[0] = 1;

        //ponavljaj n - 1 puta jer imamo jednog dodanog vec
        for(int i = 0; i < n - 1; ++i)
        {
            //spremi dobivene vrijednosti
            pair<int, int> start_minIndex = findMinWeightIndex(visited);
            int start = start_minIndex.first, minIndex = start_minIndex.second;

            //spremi second kao novi visited, lijevi je uvijek visited
            visited[minIndex] = 1;

            //ispuni novu matricu 
            matrix[start][minIndex] = AMatrix[start][minIndex];
            matrix[minIndex][start] = AMatrix[minIndex][start];

        }

        //napravi novi graf
        Graph MSTG(matrix);

        //vrati graf
        return MSTG;        
    }

    Graph kruskalMST()
    {
        int n = AMatrix.size();
        //random counter samo
        int k = 0;

        //prazna matrica susjedstava i parent array za cuvanje informacije
        //koji su elementi u kojem skupu
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<int> parent(n);

        //napravi parent array tako da je svako svoj predstavnik
        for(int i = 0; i < n; ++i)
            parent[i] = i;

        //ponavljaj petlju n - 1 puta
        while(k < n - 1)
        {
            int a = -1;
            int b = -1;
            int minValue = 1e9;
            //iteriraj po grafu i to po gornjoj dijagonali
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    //postoji brid izmedju i-j, nisu spojeni, brid ima manji value nego minimum trenutni
                    if(AMatrix[i][j + i] != 0 && (j + i < n) && (find(i, parent) != find(j + i, parent)) && AMatrix[i][j + i] < minValue)
                    {
                        //setaj minvalue, pokupi i,j u a i b varijable
                        minValue = AMatrix[i][j + i];
                        a = i;
                        b = j + i;
                    }
                }
            }

            //unija dva koja nisu u istom setu
            union_new(a, b, parent);

            //ispunjavanje nove matrice
            matrix[a][b] = AMatrix[a][b];
            matrix[b][a] = AMatrix[b][a];

            k++;
        }

        //napravi novi graf
        Graph MSTG(matrix);

        //vrati graf
        return MSTG;
    }
};

int main()
{
    int n, k, l, r, w;
    n = 7;
    k = 9;
    //broj cvorova,bridova
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    matrix[0][1] = 50;
    matrix[1][0] = 50;

    matrix[0][2] = 60;
    matrix[2][0] = 60;

    matrix[4][1] = 90;
    matrix[1][4] = 90;

    matrix[3][1] = 120;
    matrix[1][3] = 120;

    matrix[2][5] = 50;
    matrix[5][2] = 50;

    matrix[3][5] = 80;
    matrix[5][3] = 80;

    matrix[3][6] = 70;
    matrix[6][3] = 70;

    matrix[6][4] = 40;
    matrix[4][6] = 40;

    matrix[5][6] = 140;
    matrix[6][5] = 140;

    Graph G(matrix);  

    G.print();
    cout << "Total weight of G: " << G.GraphWeight() << endl;
    
    Graph MSTofG = G.primMST();

    MSTofG.print();
    cout << "Total weight of MSTofG: " << MSTofG.GraphWeight() << endl;
    
    Graph MSTofG2 = G.kruskalMST();

    MSTofG2.print();
    cout << "Total weight of MSTofG2: " << MSTofG2.GraphWeight() << endl;

    
}