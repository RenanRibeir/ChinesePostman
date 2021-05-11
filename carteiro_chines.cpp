#include <iostream>
#include <math.h> 
#include <vector>
using namespace std;

#define TAM 9
#define INF 9999

int dijkstra(int G[TAM][TAM],int n,int startnode,int des) {
   int cost[TAM][TAM],distance[TAM],pred[TAM];
   int visited[TAM],count,mindistance,nextnode,i,j;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
   if(G[i][j]==0)
      cost[i][j]=INF;
   else
      cost[i][j]=G[i][j];
   for(i=0;i<n;i++) {
      distance[i]=cost[startnode][i];
      pred[i]=startnode;
      visited[i]=0;
   }
   distance[startnode]=0;
   visited[startnode]=1;
   count=1;
   while(count<n-1) {
      mindistance=INF;
      for(i=0;i<n;i++)
         if(distance[i]<mindistance&&!visited[i]) {
         mindistance=distance[i];
         nextnode=i;
      }
      visited[nextnode]=1;
      for(i=0;i<n;i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i]<distance[i]) {
         distance[i]=mindistance+cost[nextnode][i];
         pred[i]=nextnode;
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

int menor_caminho(int g[TAM][TAM],int ori,int des){

    int atual = ori,mi,t=0;     
    bool sptSet[TAM] = {};
    while(atual != des)
    {

        mi = minDistance(g[atual],sptSet);
        sptSet[mi] = true;
        t += g[atual][mi];
        cout << "t:" <<g[atual][mi]<<"\n";
        atual = mi;
    }

    return t;

}

int findStartVert(int tempGraph[TAM][TAM]){
   for(int i = 0; i<TAM; i++){
      int deg = 0;
      for(int j = 0; j<TAM; j++){
         if(tempGraph[i][j])
         deg++; //increase degree, when connected edge found
      }
      if(deg % 2 != 0) //when degree of vertices are odd
      return i; //i is node with odd degree
   }
   return 0; //when all vertices have even degree, start from 0
}
bool isBridge(int tempGraph[TAM][TAM],int u, int v){
   int deg = 0;
   for(int i = 0; i<TAM; i++)
      if(tempGraph[v][i])
         deg++;
      if(deg>1){
         return false; //the edge is not forming bridge
      }
   return true; //edge forming a bridge
}
int edgeCount(int tempGraph[TAM][TAM]){
   int count = 0;
   for(int i = 0; i<TAM; i++)
      for(int j = i; j<TAM; j++)
         if(tempGraph[i][j])
            count++;
   return count; //count nunber of edges in the graph
}
int fleuryAlgorithm(int tempGraph[TAM][TAM],int start){
   static int edge = edgeCount(tempGraph);
 int peso = 0;
   for(int v = 0; v<TAM; v++){
      if(tempGraph[start][v]){ //when (u,v) edge is presnt and not forming bridge
         if(edge <= 1 || !isBridge(tempGraph,start, v)){
            cout << start << "--" << v << " peso "<< tempGraph[start][v] << "\n";
            peso += tempGraph[start][v];
            tempGraph[start][v] = tempGraph[v][start] = 0; //remove edge from graph
            edge--; //reduce edge
            peso += fleuryAlgorithm(tempGraph,v);
         }
      }
   }
  return peso;
}

int somar_vertices(int grafo[][TAM],int l)
{
    int w_sum = 0;
    for(int i = 0;i<l;i++)
        for(int j = i;j<l;i++)
            w_sum += grafo[i][j];
    return w_sum;
}

struct par
{
    int _0;
    int _1;
};

vector<int> get_impares(int grafo[TAM][TAM],int l)
{
    int degrees[l] = {};
    vector<int> imp;
    int j = 0;

    for(int i = 0;i<l;i++)
        for(j = 0;j<l;j++)
            if(grafo[i][j]!=0)
                degrees[i]+=1;

    for(int i = 0,j=0;i < l;i++)
    {
        if(degrees[i]%2 != 0)
        {            
            imp.push_back(i);
            j++;
        }
    }

    return imp;
}

/*par get_pairs(par * p ,par * done,par * final,int q)
{      
    int l = floor((sizeof(done)/sizeof(done[0]))/2);
    par * pares_soma = new par[10];

        if(contem(p,done)){ // corrigir
            done[sizeof(done)/sizeof(done[0])] = p[0];
            
            for(int i = 0;i < q;i++){
                par * f = final;
                par * val = done;
                if(contem(i[1],val))
                    f.append(i);
                else
                    continue;
                
                if(sizeof(f)/sizeof(f[0])==l){
                    pares_soma.append(f);
                    return;}
                else:
                    val.append(i[1])
                    get_pairs(reduzir_v(p,1,q),val,f,q)
            }
        }
        else{

            get_pairs(reduzir_v(p,1,q), done, final,q);
        }

    return 
}

par * reduzir_v(par * p,int ini,int fim)
{
    par * temp = new par[ini - fim];
    for (int i = ini,j=0; i < fim;i++,j++)
    {
        temp[j] = p[i];
    }

    return temp;
}*/

int main()
{
    /*
    int matriz_distancia[TAM][TAM] = {{0,0,1,0},
                                      {0,0,1,1},
                                      {1,1,0,1},
                                      {0,1,1,0}};
    */
    
    int matriz_distancia[TAM][TAM] = {{0,6,0,3,0,0,0,0,0},
                                     {6,0,7,0,2,0,0,0,0},
                                     {0,7,0,0,0,3,0,0,0},
                                     {3,0,0,0,6,0,5,0,0},
                                     {0,2,0,6,0,5,0,6,0},
                                     {0,0,3,0,5,0,0,0,4},
                                     {0,0,0,5,0,0,0,10,0},
                                     {0,0,0,0,6,0,10,0,5},
                                     {0,0,0,0,0,4,0,5,0}};
 
    /*int matriz_distancia[TAM][TAM] = {{0,6,0,3,0,0,0,0,0},
                                     {6,0,7,8,2,7,0,8,0},
                                     {0,7,0,0,0,3,0,0,0},
                                     {3,8,0,0,6,11,5,12,0},
                                     {0,2,0,6,0,5,0,6,0},
                                     {0,0,3,11,5,0,0,9,4},
                                     {0,0,0,5,0,0,0,10,0},
                                     {0,8,0,12,6,9,10,0,5},
                                     {0,0,0,0,0,4,0,5,0}};*/
    
    vector<int> imp = get_impares(matriz_distancia,TAM);
    int qtd_impares = imp.size();
    if( qtd_impares == 0)
        return somar_vertices(matriz_distancia,TAM);
  
    //gerar pares
    vector<par> pares[qtd_impares];
    par t;

    cout << "----------Pares Impares-----------" <<endl;
    cout << endl;

    for(int i = 0;i < qtd_impares - 1;i++)
    {
        for(int j = i+1;j<qtd_impares;j++)
        {
            cout << imp[i] << ":"<<imp[j]<<"\n";
            t._0 = imp[i];
            t._1 = imp[j];
            pares[i].push_back(t);
        }
    }

    int matriz_distancia_e[TAM][TAM];

    for(int i = 0; i < TAM;i++)
        for(int j = 0; j < TAM;j++)
            matriz_distancia_e[i][j] = matriz_distancia[i][j];

    for(int i = 0,k = qtd_impares-1;i < qtd_impares-1;i++){
        for(int j = 0;j<k;j++){
            cout << pares[i][j]._0 << ":"<< pares[i][j]._1 <<"\n";
            int menor = dijkstra(matriz_distancia,9,pares[i][j]._0,pares[i][j]._1);
            matriz_distancia_e[pares[i][j]._0][pares[i][j]._1] = menor;
            matriz_distancia_e[pares[i][j]._1][pares[i][j]._0] = menor;
        }
        k--;
    }    
    cout << endl <<"--Menor Caminho do grafo Eulirizado--"<< endl << endl;
    int peso = fleuryAlgorithm(matriz_distancia_e,1);
    cout << endl<<"Peso total: " <<  endl <<peso;
}