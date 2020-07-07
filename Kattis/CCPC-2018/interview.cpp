#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> point;
#define X first
#define Y second

const int MAXN = 150005;
point P[MAXN];

int main(){
	int A, B, T, tA, tB;
	int N;

	scanf("%d %d %d %d %d", &A, &B, &T, &tA, &tB);
	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i )
		scanf("%d %d", &P[i].X, &P[i].Y);

	sort(P, P + N);
	priority_queue< int > dom;
	
	int res = 0;
	for ( int i=0; i < N; ){	// Note: as delta A increases, delta B decreases 
		int x = P[i].X;
		// Update the structure
		int dA = max( 0, x - A );	// delta in A
		int rem = T - dA*tA;	// remaining time
		if ( rem < 0 ) break;	// unachievable
		int dB = rem/tB;			// max. delta in B
		int bound = B + dB;			// bound in B
		// remove uncovered points
		while ( !dom.empty() && dom.top() > bound ) 
			dom.pop();
		// insert new dominated points
		for ( ; i < N && P[i].X == x ; i++ )
			if ( P[i].Y <= bound )
				dom.push( P[i].Y );
		// update the answer		
		res = max( res, (int)dom.size() );
	}
	printf("%d\n", res);
	return 0;
}
