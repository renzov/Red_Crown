#include<cstdio>
#include<queue>
using namespace std;
int G[22][22];
int path[22];
int d[22];
int n;
int cnt;

void backtrack(int u,int nmv){
	if (n==u){
		cnt++;
		printf("%d",path[0]);
		for (int i=1; i < nmv; ++i)
			printf(" %d",path[i]);
		putchar('\n');
	}
	else {
		int j;
		for (int i=1; i < 22; ++i){
			if (G[u][i] && (i!=u) && d[i]!=-1){
				for (j=0; j < nmv; ++j)
					if (i==path[j]) break;
				if (j==nmv){
					path[nmv] = i;
					backtrack(i,nmv + 1);
				}
			}
		}
	}
}

void bfs(int u){
	queue<int> q;
	q.push(u);
	d[u] = 0;
	int top; 
	while (!q.empty()){
		top = q.front();
		q.pop();
		for (int i=1;i<=21; ++i){
			if ((i!=top) && G[top][i] && d[i]==-1){
				q.push(i);
				d[i] = d[top] + 1;
			}
		}
	}
}

int main(){
	int cases=0;
	int u,v;
	while (scanf("%d",&n) != EOF){
		cases++;
		for (int i=1; i <= 21; ++i){
			for (int j=1; j <= 21; ++j){
				G[i][j]=0;
			}
			G[i][i]=0;
			d[i]=-1;
		}
		scanf("%d %d",&u,&v);
		while (u && v){
			G[u][v] = G[v][u] = 1;
			scanf("%d %d",&u,&v);
		}
		bfs(n);
		cnt=0;
		path[0] = 1;
		printf("CASE %d:\n",cases);
		backtrack(1,1);
		printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,n);
	}
	
	return 0;
}