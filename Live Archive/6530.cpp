#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int diff[MAXN];

int main(){
	int N, G;
	int M;
	int wins;
	int S, R;
	while ( scanf("%d %d", &N, &G) == 2 ){
		M = wins = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &S, &R);
			if ( S > R ) wins += 3;
			else diff[M++] = R - S;
		}
		sort( diff, diff + M );
		if ( M == 0 || diff[0] > G ){
			printf("%d\n", wins);
			continue;
		}
		int l = 0;
		int r = l;
		int draws = 0;
		while ( r < M && diff[r] + draws <= G ){
			draws += diff[r]; 
			r++;
		}
		//printf("l = %d - r = %d\n", l, r);
		int best = wins + (r - l);
		while ( l < M && G > diff[l] ){
			G -= (diff[l] + 1);
			draws -= diff[l];
			l++;				
			wins += 3;
			while ( l < r && draws > G ){
				draws -= diff[r - 1];
				r--;
			}
			//printf("l = %d - r = %d\n", l, r);			
			best = max( best, wins + (r - l) );
		}
		printf("%d\n", best);
	}
	return 0;
}
