#include<cstdio>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;
#define mp(x,y) make_pair((x),(y))
typedef pair<int,int> pii;
int L;
int m;
int q;
int d[1<<22];
int C[35];
int on[25];
int off[25];
int inv[25];

void get_mask( int idx, char *s ){
	on[idx] = 0;
	off[idx] = (1<<L) - 1;
	inv[idx] = 0;
	for( int i=0; i < L; ++i ){
		if ( s[i] == 'C' ){
			off[idx] &= ~( 1 << i ); 
		}
		else if ( s[i] == 'F' ){
			inv[idx] |= (1<<i);
		}
		else if ( s[i] == 'S' ){
			on[idx] |= (1<<i); 
		}
	}
}

void printb(int x){
	for ( int i=0; i < L; ++i ){
		if ((x>>i)&1) printf("1");
		else printf("0");
	}
}

int process( int s , int e ){
	int u,v,w;
	priority_queue< pii , vector< pii > , greater< pii > > q;
	fill( d , d + (1<<L) , INT_MAX );
	d[s] = 0;
	q.push( mp(0,s) );
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( d[u] < w ) continue;
		if ( u == e ) return d[e];
		for ( int i=0; i < m; ++i ){
			v = u | on[i];
			v &= off[i];
			v ^= inv[i];
			if ( d[v] > ( w + C[i] ) ){
				d[v] = w + C[i];
				q.push( mp(d[v],v) );
			}
		}
	}
	return -1;
}

void read_input(){
	char s[25];
	scanf("%d %d %d",&L,&m,&q);
	for ( int i=0; i < m; ++i ){
		scanf("%s %d",s,C+i);
		get_mask(i,s);
	}
}

int decode(char *s){
	int res = 0;
	for (int i=0; s[i]; ++i ){
		if ( s[i] == '1' ) res |= ( 1 << i );
	}
	return res;
}

int main(){
	char s[25];
	int runs;
	int res;
	int start,end;
	scanf("%d",&runs);
	while ( runs-- ){
		read_input();
		for ( int i=0; i < q; ++i ){
			if (i) putchar(' ');
			scanf("%s",s);
			start = decode(s);
			scanf("%s",s);
			end = decode(s);
			res = process(start,end);
			if ( res == -1 ) printf("NP");
			else printf("%d",res);
		}
		puts("");
	}
	return 0;
}
