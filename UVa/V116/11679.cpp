#include<cstdio>
int b[30];

int main(){
	int N,M;
	int u,v,w;
	
	while (1){
		scanf("%d %d",&N, &M);
		if (!N && !M) break;
		for (int i=0; i < N ; ++i)
			scanf("%d",b+i);
		while (M--){
			scanf("%d %d %d",&u,&v,&w);
			u--,v--;
			b[u] -= w;
			b[v] += w;
		}
		bool ok = true;
		for (int i=0; i < N; ++i){
			if (b[i] < 0){
				ok = false;
				break;
			}
		}
		if (ok) puts("S");
		else puts("N");
	}
	return 0;
}