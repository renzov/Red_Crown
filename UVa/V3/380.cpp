#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<vector>
using namespace std;

struct triple {
	int s,e,t;
	triple (int S,int E,int T){
		s=S;
		e=E;
		t=T;
	}
	triple(){}
};

map<int,int> f;
vector< triple > T[100]; 
set<int> visited;
int n;
int Time;

int dfs(int target){
	if (f.find(target) == f.end()) return target;
	if (visited.find(target) != visited.end()) return 9999;
	visited.insert(target);
	/* vemos a quien se envia */
	int idx = f[target];
	for (int i=0; i < T[idx].size(); ++i){
		if (Time < T[idx][i].s) return target;
		if (Time <= T[idx][i].e) return dfs( T[idx][i].t );
	}
	return target;
}

int main(){
	int runs;
	int source;
	int target;
	int idx;
	int len;
	int start;
	
	scanf("%d",&runs);
	
	puts("CALL FORWARDING OUTPUT");
	
	for (int cases=1; cases <= runs; cases++){
		
		f.clear();
		n = 0;
		for (int i=0; i < 100; ++i) T[i].clear();
		
		printf("SYSTEM %d\n",cases);
		
		while (scanf("%d",&source) && source){
			scanf("%d %d %d",&start,&len,&target);
			if (f.find(source) == f.end()){
				f[source] = n;
				T[n].push_back( triple( start , start + len , target ) );
				n++;
			}
			else {
				idx = f[source];
				T[idx].push_back( triple( start , start + len , target ) );
			}
		}
		
		while (scanf("%d",&Time) && Time != 9000 ){
			scanf("%d",&target);
			visited.clear();
			printf("AT %04d CALL TO %04d RINGS %04d\n",Time,target,dfs(target));
		}
		
	}
	puts("END OF OUTPUT");
	return 0;
}