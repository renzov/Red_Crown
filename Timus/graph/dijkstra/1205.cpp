#include<cstdio>
#include<queue>
#include<cmath>
#include<list>

using namespace std;

struct point{
  double x,y;
};

int n;
double G[205][205];
point p[205];
double d[ 205 ];
int pred[ 205 ];

double dist(int a,int b){
  return sqrt( ( (p[a].x - p[b].x) * (p[a].x - p[b].x) )  +  ( (p[a].y - p[b].y) * (p[a].y - p[b].y) ) );
}

void dijkstra(int s,int e){
	 priority_queue< pair<double,int> , vector< pair<double,int> > , greater< pair<double,int> > > q;
	 for (int i=0; i<n; ++i){
		d[i] = 10e10;
		pred[i] = -1;
	 }
	 d[s] = 0.0;
	 q.push( make_pair(0.0,s) );
	 int u;
	 double w;

	 while (!q.empty()){
		  u = q.top().second;
		  w = q.top().first; 
		  q.pop();
		  if ( w > d[u]) continue;
		  if (u == e) break;
		  for (int v = 0; v < n; ++v){
			 if (u!=v && ( (d[u] + G[u][v]) < d[v] ) ){
				  pred[v] = u;
				  d[v] = d[u] + G[u][v];
				  q.push( make_pair(d[v],v) );
			 } 
		  }
	 }

	 printf("%.7lf\n",d[e]);
	 u = e;
	 list<int> res;
	 while (u >= 0){
		if (u != e && u != s) res.push_front(u);
		u = pred[u];
	 }
	 printf("%d",(int)res.size());
	 for(list<int>::iterator it = res.begin(); it != res.end() ; ++it){
		printf(" %d",*it + 1);
	 }
	 putchar('\n');
}

int find_index(double x,double y){
  p[n].x = x;
  p[n].y = y;

  for (int i=0; i < n; ++i){
	 G[i][n] = G[n][i] = -1.0;
  }
  return n++;
}

int main(){
  
  double sf,su;
  double x,y;

  scanf("%lf %lf",&sf,&su);
  scanf("%d",&n);
  for (int i=0; i < n; ++i){
	 for (int j=i+1; j < n; ++j)
		G[i][j] = G[j][i] = -1.0;
  }
  for (int i=0; i < n; ++i)
	 scanf("%lf %lf",&p[i].x,&p[i].y);
  int u,v;
  while (scanf("%d %d",&u,&v) && u){
	 u--,v--;
	 G[u][v] = G[v][u] = ( dist(u,v) / su ) ;
  }
  scanf("%lf %lf",&x,&y);
  int start = find_index(x,y);
  scanf("%lf %lf",&x,&y);
  int end = find_index(x,y);
  
  for (int i=0; i < n; ++i)
	 for (int j=i+1; j < n; ++j)
		if (G[i][j] < 0)
		  G[i][j] = G[j][i] = ( dist(i,j) / sf ) ;

  dijkstra(start,end);

  return 0;
}