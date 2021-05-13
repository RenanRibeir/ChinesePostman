#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

#define TAM 9
#define INF 9999

struct par
{
   int _0;
   int _1;
   int peso = INF;
};

int dijkstra(int G[TAM][TAM], int n, int startnode, int des)
{
   int cost[TAM][TAM], distance[TAM], pred[TAM];
   int visited[TAM], count, mindistance, nextnode, i, j;
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         if (G[i][j] == 0)
            cost[i][j] = INF;
         else
            cost[i][j] = G[i][j];
   for (i = 0; i < n; i++)
   {
      distance[i] = cost[startnode][i];
      pred[i] = startnode;
      visited[i] = 0;
   }
   distance[startnode] = 0;
   visited[startnode] = 1;
   count = 1;
   while (count < n - 1)
   {
      mindistance = INF;
      for (i = 0; i < n; i++)
         if (distance[i] < mindistance && !visited[i])
         {
            mindistance = distance[i];
            nextnode = i;
         }
      visited[nextnode] = 1;
      for (i = 0; i < n; i++)
         if (!visited[i])
            if (mindistance + cost[nextnode][i] < distance[i])
            {
               distance[i] = mindistance + cost[nextnode][i];
               pred[i] = nextnode;
            }
      count++;
   }

   return distance[des];
}

int minDistance(int dist[], bool sptSet[])
{
   int min = INF, min_index;

   for (int v = 0; v < TAM; v++)
      if (sptSet[v] == false && dist[v] <= min && dist[v] != 0)
         min = dist[v], min_index = v;

   return min_index;
}

int min(int vet[])
{
   int min = INF;

   for (int v = 0; v < TAM; v++)
      if (vet[v] <= min)
         min = vet[v];

   return min;
}

par min(par vet[])
{
   par min;
   min.peso = INF;
   for (int v = 0; v < TAM; v++)
      if (vet[v].peso <= min.peso)
         min = vet[v];

   return min;
}

int menor_caminho(int g[TAM][TAM], int ori, int des)
{

   int atual = ori, mi, t = 0;
   bool sptSet[TAM] = {};
   while (atual != des)
   {

      mi = minDistance(g[atual], sptSet);
      sptSet[mi] = true;
      t += g[atual][mi];
      cout << "t:" << g[atual][mi] << "\n";
      atual = mi;
   }

   return t;
}

int findStartVert(int tempGraph[TAM][TAM])
{
   for (int i = 0; i < TAM; i++)
   {
      int deg = 0;
      for (int j = 0; j < TAM; j++)
      {
         if (tempGraph[i][j])
            deg++;
      }
      if (deg % 2 != 0)
         return i;
   }
   return 0;
}
bool isBridge(int tempGraph[TAM][TAM], int u, int v)
{
   int deg = 0;
   for (int i = 0; i < TAM; i++)
      if (tempGraph[v][i])
         deg++;
   if (deg > 1)
   {
      return false;
   }
   return true;
}
int edgeCount(int tempGraph[TAM][TAM])
{
   int count = 0;
   for (int i = 0; i < TAM; i++)
      for (int j = i; j < TAM; j++)
         if (tempGraph[i][j])
            count++;
   return count;
}
int fleuryAlgorithm(int tempGraph[TAM][TAM], int start)
{
   static int edge = edgeCount(tempGraph);
   int peso = 0;
   for (int v = 0; v < TAM; v++)
   {
      if (tempGraph[start][v])
      {
         if (edge <= 1 || !isBridge(tempGraph, start, v))
         {
            cout << start << "--" << v << " peso " << tempGraph[start][v] << "\n";
            peso += tempGraph[start][v];
            tempGraph[start][v] = tempGraph[v][start] = 0;
            edge--;
            peso += fleuryAlgorithm(tempGraph, v);
         }
      }
   }
   return peso;
}

int somar_vertices(int grafo[][TAM], int l)
{
   int w_sum = 0;
   for (int i = 0; i < l; i++)
      for (int j = i; j < l; i++)
         w_sum += grafo[i][j];
   return w_sum;
}

vector<int> get_impares(int grafo[TAM][TAM], int l)
{
   int degrees[l] = {};
   vector<int> imp;
   int j = 0;

   for (int i = 0; i < l; i++)
      for (j = 0; j < l; j++)
         if (grafo[i][j] != 0)
            degrees[i] += 1;

   for (int i = 0, j = 0; i < l; i++)
   {
      if (degrees[i] % 2 != 0)
      {
         imp.push_back(i);
         j++;
      }
   }

   return imp;
}

int main()
{


   int matriz_distancia[TAM][TAM] = {{0, 6, 0, 3, 0, 0, 0, 0, 0},
                                     {6, 0, 7, 0, 2, 0, 0, 0, 0},
                                     {0, 7, 0, 0, 0, 3, 0, 0, 0},
                                     {3, 0, 0, 0, 6, 0, 5, 0, 0},
                                     {0, 2, 0, 6, 0, 5, 0, 6, 0},
                                     {0, 0, 3, 0, 5, 0, 0, 0, 4},
                                     {0, 0, 0, 5, 0, 0, 0, 10, 0},
                                     {0, 0, 0, 0, 6, 0, 10, 0, 5},
                                     {0, 0, 0, 0, 0, 4, 0, 5, 0}};

   //Inicializa matriz com indices impares do grafo
   vector<int> imp = get_impares(matriz_distancia, TAM);
   int qtd_impares = imp.size();

   if (qtd_impares == 0)
      return somar_vertices(matriz_distancia, TAM);

   //gerar pares
   vector<par> pares[qtd_impares];
   par t;

   cout << "----------Pares Impares-----------" << endl;
   cout << endl;

   for (int i = 0; i < qtd_impares - 1; i++)
   {
      for (int j = i + 1; j < qtd_impares; j++)
      {
         //cout << imp[i] << ":" << imp[j] << "\n";
         t._0 = imp[i];
         t._1 = imp[j];
         pares[i].push_back(t);
      }
   }

   int matriz_distancia_e[TAM][TAM];
   int impar[TAM] = {};

   //copia grafo original para um que vai ser eurelizado
   for (int i = 0; i < TAM; i++)
      for (int j = 0; j < TAM; j++)
         matriz_distancia_e[i][j] = matriz_distancia[i][j];

    for (int i = 0; i < imp.size(); i++)
         impar[imp[i]] = true;

   int j,menor = INF;

   for (int i = 0, k = qtd_impares - 1; i < qtd_impares - 1; i++)
   {
      par vet[TAM];
      for (j = 0; j < k; j++)
      {
         cout << pares[i][j]._0 << ":" << pares[i][j]._1 << "\n";
         int d = dijkstra(matriz_distancia, TAM, pares[i][j]._0, pares[i][j]._1);
         vet[j]._0 = pares[i][j]._0;
         vet[j]._1 = pares[i][j]._1;
         vet[j].peso = d;
      }

      par m = min(vet);

      cout << m._0 << " " << m._1<<  " " << m.peso<<endl;
      matriz_distancia_e[m._0][m._1] = m.peso; 
      matriz_distancia_e[m._1][m._0] = m.peso;

      k--;
   }

   for (int i = 0; i < TAM ; i++)
   {
      for (int j = 0; j < TAM; j++)
      {
         cout << matriz_distancia_e[i][j] << " ";
      }
      cout << endl;
   }

   cout << endl
        << "--Menor Caminho do grafo Eulirizado--" << endl
        << endl;
   int peso = fleuryAlgorithm(matriz_distancia_e, 1);
   cout << endl
        << "Peso total: " << endl
        << peso;
}