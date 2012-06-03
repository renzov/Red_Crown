/* @JUDGE_ID: 00000 336 C++ */
#include<stdio.h>
#include<map>
#include<vector>
#include<queue>

using namespace std;
int main(){
 int n;
 map<int,int> hash;
 map<int,int>::iterator it;
 vector< vector<int> > graph;
 queue<int> q;
 int v1,v2,node1,node2;
 int ttl,vIni;
 int numNode,top;
 int i,j;
 int cont,runs=0;
  
 while (1){
   scanf("%d",&n);
   if (!n) break;
   /* inicializacion de variables */
   numNode = 0;
   hash.clear();
   graph.clear();
   graph.push_back(vector<int> (0));
   /* */
   for (i=1; i <= n; i++){
       scanf("%d",&v1);
       scanf("%d",&v2);
       
       it = hash.find(v1);
       /* verificamos la existencia de los nodos */
       if (it == hash.end()){  
         numNode++;
         hash.insert( pair<int,int>(v1,numNode) );
         node1 = numNode;
         graph.push_back(vector<int> (0));
       }
       else {
         node1 = it->second;   
       }
       
       it = hash.find(v2);
       if (it == hash.end()){
         numNode++;
         hash.insert( pair<int,int>(v2,numNode) );
         node2 = numNode;
         graph.push_back(vector<int> (0) );
       }
       else {
         node2 = it->second;   
       }
   
       graph[node1].push_back(node2);
       graph[node2].push_back(node1);
       
   }  
   
  
   while (1){
   
     scanf("%d",&vIni);
     scanf("%d",&ttl);
   
     if (!vIni && !ttl) break;
     runs++;
     if (hash.find(vIni) == hash.end()){
       printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n",runs,numNode,vIni,ttl);
     }
     else { 
       vector<bool> lista(numNode + 2, false); 
       vector<int> valTTL(numNode + 2, -1);
       it = hash.find(vIni);
       q.push(it->second);
       valTTL[it->second] = ttl;
    
       /* recorrido BFS */
   
       while (!q.empty()){
         top = q.front();
         lista[top]=true;
         q.pop();
         for (i=0; i < graph[top].size(); i++){
            v2 = graph[top][i];
            if (!lista[v2]){
              valTTL[v2] = (valTTL[v2] < (valTTL[top] - 1 ) )? valTTL[top] - 1:valTTL[v2];
              if (valTTL[v2] > 0){
                q.push(v2);
              }         
            } 
         }   
       }
       cont = 0;
       for (i=1; i <= numNode; i++){
         if (valTTL[i] < 0){
           cont++;    
         }
       }
       printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n",runs,cont,vIni,ttl);
     }
   }
 }
       
 return 0;    
}
