#include "Graph.h"
#include <fstream>

using namespace std;

Graph::Graph(int w, int m)
{
    edges = m;
    verticles = w;
    incidence_matrix = new int *[verticles];
    unscanned_graph_matrix = new int *[verticles];
    neighborhood_list = new ListElement *[verticles];
    unscanned_graph_list = new ListElement *[verticles];
    K = new Edge[edges];
    KO = new Edge[edges];
    inverted_edges = 0;
}

Graph::~Graph()
{
    for (int i = 0; i < verticles; i++)
    {
        e1 = neighborhood_list[i];

        while(e1)
        {
            e2 = e1;
            e1 = e1->next;
            delete e2;
        }
    }

    delete[] neighborhood_list;


    for (int i = 0; i < verticles; i++)
    {
        delete[] incidence_matrix[i];
    }

    delete[] incidence_matrix;
}

void Graph::changeToUnscannedGraph()
{
    int i, j;
    for (i = 0; i < verticles; i++)
    {
        unscanned_graph_matrix[i] = new int[edges];
    }

    for (i = 0; i < verticles; i++)
    {
        for (j = 0; j < edges; j++)
        {
            unscanned_graph_matrix[i][j] = 0;
        }
    }

    for (i = 0; i < verticles; i++)
    {
        unscanned_graph_list[i] = NULL;
    }

    for (i = 0; i < edges; i++)
    {
        j = 0;
        while(j < inverted_edges)
        {

            if (KO[j].wp == K[i].wp && KO[j].wk == K[i].wk) break;
            else j++;
        }

        if(j == inverted_edges)
        {
            KO[inverted_edges].wp = K[i].wk;
            KO[inverted_edges].wk = K[i].wp;
            KO[inverted_edges].weight = K[i].weight;
            inverted_edges++;
        }
    }

    int wp, wk, weight;

    for (int i = 0; i < inverted_edges; i++)
    {
        wp = KO[i].wp;
        wk = KO[i].wk;
        weight = KO[i].weight;
        e1 = new ListElement;
        e1->w = wk;
        e1->weight = weight;
        e1->next = unscanned_graph_list[wp];
        unscanned_graph_list[wp] = e1;
        e2 = new ListElement;
        wp = KO[i].wk;
        wk = KO[i].wp;
        weight = KO[i].weight;
        e2->w = wk;
        e2->weight = weight;
        e2->next = unscanned_graph_list[wp];
        unscanned_graph_list[wp] = e2;
        unscanned_graph_matrix[KO[i].wp][i] = 1;
        unscanned_graph_matrix[KO[i].wk][i] = 1;
    }
}

void Graph::generateEdges()
{
    int c = 0;
    int *T;
    int b;
    int to_add_1;
    int to_add_2;
    int a, i, j;
    int count_degree = 0;
    int *in_tree;
    int *not_in_tree;
    srand(time(NULL));

    a = verticles;
    not_in_tree = new int[a]; // utworzenie tablicy, która zawiera jakie wierzchołki się nie znajdują w drzewie

    for (i = 0; i < a; i++)
    {
        not_in_tree[i] = i;
    }

    in_tree = new int[a]; // utworzenie tablicy z zawartymi wierzchołkami w drzewie
    b = rand() % a;
    to_add_1 = not_in_tree[b]; // pobieram wartość wierzchołka drzewa
    not_in_tree[b] = not_in_tree[a - 1];
    a--; // dekrementuję liczbę pozostałych wierzchołków do zbadania
    in_tree[c] = to_add_1; // umieszczam wartość wierzchołka do nowego drzewa
    c++; // inkrementuję indeks tablicy, w której umieszczam nowe wierzchołki grafu

    for (i = 0; i < (verticles - 1); i++)
    {
        b = rand() % c;
        to_add_1 = in_tree[b];

        b = rand() % a;
        to_add_2 = not_in_tree[b];
        not_in_tree[b] = not_in_tree[a - 1];
        a--;
        in_tree[c] = to_add_2;
        c++;
        K[i].wp = to_add_1;
        K[i].wk = to_add_2;
    }

    for (i = 0; i < (verticles - 1); i++)
    {
        b = rand() % verticles;
        swap(K[b].wk, K[b].wp);
    }

    for (i = verticles - 1; i < edges; i++)
    {
        a = verticles;
        T = new int[a];
        for (int k = 0; k < a; k++)
        {
            T[k] = k;
        }

        b = rand() % a;
        to_add_1 = T[b];
        T[b] = T[a - 1];
        a--;

        while(true)
        {

            count_degree = 0;

            for (j = 0; j < i; j++)
            {
                if (K[j].wp == to_add_1)
                    count_degree++;
                if (count_degree == verticles - 1) break;
            }

            if (count_degree == verticles - 1)
            {
                b = rand() % a;
                to_add_1 = T[b];
                T[b] = T[a - 1];
                a--;
            }
            else break;
        }

        a = verticles;

        for (int k = 0; k < a; k++)
        {
            T[k] = k;
        }

        T[to_add_1] = T[a - 1];
        a--;

        b = rand() % a;
        to_add_2 = T[b];
        T[b] = T[a - 1];
        a--;

        for (j = 0; j < i; j++)
        {
            while (to_add_1 == K[j].wp && to_add_2 == K[j].wk)
            {
                b = rand() % a;
                to_add_2 = T[b];
                T[b] = T[a - 1];
                a--;
                j = 0;
            }
        }
        K[i].wp = to_add_1;
        K[i].wk = to_add_2;
        delete[]T;
    }

    for (i = 0; i < edges; i++)
    {
        K[i].weight = (rand() % 9) + 1;
    }

    delete[] not_in_tree;
    delete[] in_tree;
}

void Graph::generateGraph()
{
    for (int i = 0; i < verticles; i++)
    {
        incidence_matrix[i] = new int[edges]; // tworzenie macierzy incydencji
    }

    for (int i = 0; i < verticles; i++)
    {
        for (int j = 0; j < edges; j++)
        {
            incidence_matrix[i][j] = 0; // ustawienie każdej wartości w macierzy na zero
        }

    }

    for (int i = 0; i < verticles; i++)
    {
        neighborhood_list[i] = NULL; // utworzenie nowej listy sąsiedztwa
    }

    generateEdges(); // wywołanie metody generującej krawędzie
    changeToUnscannedGraph();
    ofstream save;

    save.open("graf.txt", ios::app); // odczyt danych z pliku

    if(save.good())
    {
        for (int i = 0; i < edges; i++) // pobieranie parametrów grafu z pliku
        {
            int wp = K[i].wp;
            int wk = K[i].wk;
            int weight = K[i].weight;
            save << endl << wp << " " << wk << " " << weight;
            e1 = new ListElement;
            e1->w = wk;
            e1->weight = weight;
            e1->next = neighborhood_list[wp];
            neighborhood_list[wp] = e1;
            incidence_matrix[wp][i] = 1;
            incidence_matrix[wk][i] = -1;
        }
        save.close();
    }
}

bool Graph::checkConsistence() // metoda sprawdzająca spójność grafu
{
    Stack stack;
    int w, u, i;
    int count = 0;

    visited = new bool[verticles];

    for (i = 0; i < verticles; i++)
    {
        visited[i] = false; // początkowo żaden wierzchołek nie jest odwiedzony
    }

    stack.push(0); // wrzucam wierzchołek na stos
    visited[0] = true; // zmieniam jego wartość logiczną na odwiedzony

    while (!stack.empty()) // pętla się wykonuje dopóki stos nie jest pusty
    {
        w = stack.top();
        stack.pop();
        count++;

        for (e1 = unscanned_graph_list[w]; e1; e1 = e1->next) // sprawdzam kolejne wierzchołki przy przejściu DFS
        {
            u = e1->w;
            if (!visited[u])
            {
                visited[u] = true; // zmiana wartości logicznej wierzchołka na odwiedzony
                stack.push(u);
            }
        }
    }
    delete[]visited;

    if (count == verticles)
    {
        return true; // jeśli liczba odwiedzonych wierzchołków w grafie jest równa liczbie wierzchołków nowego grafu to graf jest spójny
    }
    else return false; // jeśli warunek nie jest spełniony to nie jest spójny
}

void Graph::DFSMatrix(int w)
{
    Time time;
    Stack stack;
    visited = new bool[verticles];

    for (int i = 0; i < verticles; i++)
    {
        visited[i] = false;
    }

    cout << "Graf nieskierowany:\n\n";

    cout << "      ";

    for (int i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << i;

    }
    cout << "\n" << "      ";

    for (int i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << "-";

    }

    cout << "\n";

    for (int i = 0; i < verticles; i++)
    {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < inverted_edges; j++)
        {
            cout << setw(3) << unscanned_graph_matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "Wagi krawedzi: ";

    for (int i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << KO[i].weight;
    }
    cout << "\n" << "\n";
    cout << "Przebyta droga (przez wierzcholki):\n";
    time.start();
    stack.push(w);
    while (!stack.empty())
    {

        w = stack.top();
        stack.pop();

        if (!visited[w])
        {
            visited[w] = true;
            for(int i = edges - 1; i >= 0; i--)
            {
                if (unscanned_graph_matrix[w][i] != 0)
                    for(int j = 0; j < verticles; j++)
                        if (j != w && unscanned_graph_matrix[j][i] != 0)
                        {
                            if (!visited[j])
                            {
                                stack.push(j);
                            }
                        }

            }
            cout << w << ", ";
        }
    }
    cout << "\n\n";

    time.stop();
    cout << "\n" << "Czas wykonania: " << time.executionTime() << "\n";
    delete[] visited;
    stack.~Stack();
}

void Graph::DFSList(int w)
{
    Time time;
    Stack stack;
    visited = new bool[verticles];

    for(int i = 0; i < verticles; i++)
    {
        visited[i] = false;
    }
    cout << "\n" << "Graf nieskierowany:\n";

    for(int i = 0; i < verticles; i++)
    {
        cout << "[" << i << "] = ";
        e1 = unscanned_graph_list[i];
        while(e1)
        {
            cout << /*setw(3)*/" " << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << "\n";
    }
    cout << "\n" << "\n";
    cout << "Przebyta droga (przez wierzcholki):\n";
    time.start();
    stack.push(w);
    int u;

    while (!stack.empty())
    {
        w = stack.top();
        stack.pop();

        if (!visited[w])
        {
            visited[w] = true;
            for (e1 = unscanned_graph_list[w]; e1; e1 = e1->next)
            {
                u = e1->w;
                if (!visited[u])
                {
                    stack.push(u);
                }
            }
            cout << w << ", ";
        }

    }

    time.stop();
    cout << "\n" << "Czas wykonania: " << time.executionTime() << "\n";
    delete[]visited;
    stack.~Stack();
}

void Graph::DijkstraMatrix(int w) // tworzenie macierzy incydencji dla algorytmu Dijkstry
{
    int root, node, heap_size;
    int parent, left_son, right_son;
    int min_cost, min_son, son;
    int *cost, *predecessors, *heap;
    int *heap_position;

    Time time;
    Stack stack;

    int width;
    cost = new int[verticles];
    predecessors = new int[verticles];
    visited = new bool[verticles];
    heap = new int[verticles];
    heap_position = new int[verticles];

    for (int i = 0; i < verticles; i++)
    {
        cost[i] = MAXINT; // dojście do nowego wierzchołka kosztuje nas nieskończoność zasobów
        predecessors[i] = -1; // poprzednik jest niezdefiniowany
        visited[i] = false; // także żaden wierzchołek nie jest odwiedzony
        heap[i] = heap_position[i] = i;
    }


    time.start();
    heap_size = verticles;

    cost[w] = 0;
    node = heap[0];
    heap[0] = heap[w];
    heap[w] = node;
    heap_position[w] = 0;
    heap_position[0] = w;

    for (int i = 0; i < verticles; i++)
    {
        root = heap[0];
        heap[0] = heap[--heap_size];
        heap_position[heap[0]] = parent = 0;

        while(true)
        {
            left_son = parent + parent + 1;
            right_son = left_son + 1;
            if(left_son >= heap_size) break;
            min_cost = cost[heap[left_son]];
            min_son = left_son;

            if ((right_son < heap_size) && (min_cost > cost[heap[right_son]]))
            {
                min_cost = cost[heap[right_son]];
                min_son = right_son;
            }
            if (cost[heap[parent]] <= min_cost)
                break;
            node = heap[parent];
            heap[parent] = heap[min_son];
            heap[min_son] = node;
            heap_position[heap[parent]] = parent;
            heap_position[heap[min_son]] = min_son;
            parent = min_son;
        }

        visited[root] = true;

        for (int l = 0; l < edges; l++)
        {
            if (incidence_matrix[root][l] != 0)
                for (int j = 0; j < verticles; j++)
                    if (j != root && incidence_matrix[j][l] == -1 && !visited[j] &&
                            (cost[j] > cost[root] + K[l].weight))
                    {
                        cost[j] = cost[root] + K[l].weight;
                        predecessors[j] = root;

                        for(son = heap_position[j]; son; son = parent)
                        {
                            parent = son / 2;
                            if (cost[heap[parent]] <= cost[heap[son]])
                                break;
                            node = heap[parent];
                            heap[parent] = heap[son];
                            heap[son] = node;
                            heap_position[heap[parent]] = parent;
                            heap_position[heap[son]] = son;
                        }
                    }
        }
    }
    time.stop();
    cout << "\n" << "Czas wykoniania: " << time.executionTime() << "\n";
    cout << "\n";

    cout << "Najkrotsza sciezka w grafie, rozpoczynajac od wierzcholka " << w << ":\n";
    for (int i = 0; i < verticles; i++)
    {
        width = -2;

        cout << i << ": ";


        if (cost[i] == MAXINT || cost[i] < 0)
            cout << "Brak\n";
        else
        {
            for (int j = i; j > -1; j = predecessors[j])
            {
                stack.push(j);
                width = width + 2;
            }

            while (!stack.empty())
            {
                cout << stack.top() << " ";
                stack.pop();
            }
            for (int j = 0; j < verticles - width; j++)
                cout << " ";
            cout << setw(5) << "(" << cost[i] << ")" << "\n";
        }
    }
    cout << "\n" << "\n";
}

void Graph::DijkstraList(int w) // tworzenie listy sąsiedztwa dla algorytmu Dijkstry
{
    int root, node, heap_size;
    int parent, left_son, right_son;
    int min_cost, min_son, son;
    int *cost, *predecessors, *heap, *heap_position;
    Time time;
    Stack stack;
    int width;

    cost = new int[verticles];
    predecessors = new int[verticles];
    visited = new bool[verticles];
    heap = new int[verticles];
    heap_position = new int[verticles];

    for (int i = 0; i < verticles; i++)
    {
        cost[i] = MAXINT;
        predecessors[i] = -1;
        visited[i] = false;
        heap[i] = heap_position[i] = i;
    }

    time.start();
    heap_size = verticles;

    cost[w] = 0;
    node = heap[0];
    heap[0] = heap[w];
    heap[w] = node;
    heap_position[w] = 0;
    heap_position[0] = w;

    for (int i = 0; i < verticles; i++)
    {
        root = heap[0];
        heap[0] = heap[--heap_size];
        heap_position[heap[0]] = parent = 0;
        while (true)
        {
            left_son = parent + parent + 1;
            right_son = left_son + 1;
            if (left_son >= heap_size) break;
            min_cost = cost[heap[left_son]];
            min_son = left_son;
            if ((right_son < heap_size) && (min_cost > cost[heap[right_son]]))
            {
                min_cost = cost[heap[right_son]];
                min_son = right_son;
            }
            if (cost[heap[parent]] <= min_cost)
                break;
            node = heap[parent];
            heap[parent] = heap[min_son];
            heap[min_son] = node;
            heap_position[heap[parent]] = parent;
            heap_position[heap[min_son]] = min_son;
            parent = min_son;
        }

        visited[root] = true;

        if (neighborhood_list[root] != NULL)
            for (e1 = neighborhood_list[root]; e1; e1 = e1->next)
                if (!visited[e1->w] && (cost[e1->w] > cost[root] + e1->weight))
                {
                    cost[e1->w] = cost[root] + e1->weight;
                    predecessors[e1->w] = root;

                    for (son = heap_position[e1->w]; son; son = parent)
                    {
                        parent = son / 2;
                        if (cost[heap[parent]] <= cost[heap[son]])
                            break;
                        node = heap[parent];
                        heap[parent] = heap[son];
                        heap[son] = node;
                        heap_position[heap[parent]] = parent;
                        heap_position[heap[son]] = son;
                    }
                }
    }
    time.stop();
    cout << "\n" << "Czas wykoniania: " << time.executionTime() << "\n";
    cout << "\n";

    cout << "Najkrotsza sciezka w grafie, rozpoczynajac od wierzcholka " << w << ":" << "\n";
    for (int i = 0; i < verticles; i++)
    {
        width = -2;

        cout << i << ": ";


        if (cost[i] == MAXINT || cost[i] < 0)
            cout << "Brak\n";
        else
        {
            for (int j = i; j > -1; j = predecessors[j])
            {
                stack.push(j);
                width = width + 2;
            }

            while (!stack.empty())
            {
                cout << stack.top() << " ";
                stack.pop();
            }
            for (int j = 0; j < verticles - width; j++)
                cout << " ";
            cout << setw(5) << "(" << cost[i] << ")" << "\n";
        }
    }
    cout << "\n\n";
}

void Graph::Prim_matrix() // tworzenie macierzy incydencji dla algorytmu Prima
{

    int w, i, j, g;
    Time time;
    Edge edge;
    priority_queue<Edge, vector<Edge>, Edge> kolejka;
    SpanningTree *tree = new SpanningTree(verticles, edges);
    visited = new bool[verticles];
    for (i = 0; i < verticles; i++)
    {
        visited[i] = false;
    }

    cout << "Graf nieskierowany:\n";

    cout << "      ";
    for (i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << i;

    }
    cout << "\n" << "      ";
    for (i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << "-";

    }

    cout << "\n";
    for (i = 0; i < verticles; i++)
    {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < inverted_edges; j++)
            cout << setw(3) << unscanned_graph_matrix[i][j];
        cout << "\n";
    }
    cout << "\n";
    cout << "Wagi krawedzi grafu: ";
    for (i = 0; i < inverted_edges; i++)
    {
        cout << setw(3) << KO[i].weight;
    }
    cout << "\n\n";
    time.start();

    w = 0;
    visited[w] = true;
    for (i = 1; i < verticles; i++)
    {
        for (g = 0; g < inverted_edges; g++)
        {

            if (unscanned_graph_matrix[w][g] != 0)
                for (j = 0; j < verticles; j++)
                    if (j != w && unscanned_graph_matrix[j][g] != 0 && !visited[j])
                    {
                        edge.wp = w;
                        edge.wk = j;
                        edge.weight = KO[g].weight;
                        kolejka.push(edge);

                    }
        }
        do
        {
            edge = kolejka.top();
            kolejka.pop();

        }
        while (visited[edge.wk]);

        tree->addEdge(edge);
        visited[edge.wk] = true;
        w = edge.wk;

    }
    time.stop();
    cout << "\n" << "Czas wykonania: " << time.executionTime() << "\n";
    cout << "Minimalne drzewo rozpinajace (MST): ";
    tree->display();
    delete tree;
}

void Graph::PrimList() // tworzenie listy sąsiedztwa dla algorytmu Prima
{
    int w;
    Time time;
    Edge k;
    priority_queue<Edge, vector<Edge>, Edge> kolejka;
    SpanningTree *tree = new SpanningTree(verticles, edges);
    visited = new bool[verticles];
    for (int i = 0; i < verticles; i++)
    {
        visited[i] = false;
    }
    cout << "\n" << "Graf nieskierowany:\n\n";
    for (int i = 0; i < verticles; i++)
    {
        cout << "[" << i << "] =";
        e1 = unscanned_graph_list[i];
        while (e1)
        {
            cout << setw(3) << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << "\n";
    }
    cout << "\n";
    time.start();
    w = 0;
    visited[w] = true;

    for (int i = 1; i < verticles; i++)
    {

        for (e1 = unscanned_graph_list[w]; e1; e1 = e1->next)
        {
            if (!visited[e1->w])
            {
                k.wp = w;
                k.wk = e1->w;
                k.weight = e1->weight;
                kolejka.push(k);
            }
        }
        do
        {
            k = kolejka.top();
            kolejka.pop();

        }
        while (visited[k.wk]);

        tree->addEdge(k);
        visited[k.wk] = true;
        w = k.wk;

    }

    time.stop();
    cout << "\n" << "Czas wykonania: " << time.executionTime() << "\n";
    cout << "\n";
    cout << "Minimalne drzewo rozpinajace (MST): ";
    tree->display();
    delete tree;
}

void Graph::display() // metoda wyświetlająca macierz incydencji i listę sąsiedztwa
{
    cout << "Macierz incydencji:\n";
    int i;
    cout << "      ";
    for (i = 0; i < edges; i++)
    {
        cout << setw(3) << i;

    }

    cout << "\n" << "      ";
    for (i = 0; i < edges; i++)
    {
        cout << setw(3) << "-";

    }

    cout << "\n";
    for (i = 0; i < verticles; i++)
    {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < edges; j++)
            cout << setw(3) << incidence_matrix[i][j];
        cout << "\n";
    }
    cout << "\n";
    cout << "Wagi krawedzi grafu: ";
    for (i = 0; i < edges; i++)
    {
        cout << setw(3) << K[i].weight;
    }

    cout << "\n\n" << "Lista poprzednikow i nastepnikow:\n";
    for (i = 0; i < verticles; i++)
    {
        cout << "[" << i << "] =";
        e1 = neighborhood_list[i];
        while (e1)
        {
            cout << /*setw(3)*/" " << e1->w << "(" << e1->weight << ") ";
            e1 = e1->next;
        }
        cout << "\n";
    }
}
