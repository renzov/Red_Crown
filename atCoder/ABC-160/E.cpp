#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int main(){
	int X, Y, A, B, C;
	priority_queue< int, vector<int>, greater<int> > qA;
	priority_queue< int, vector<int>, greater<int> > qB;
	priority_queue<int> qC;
	int v;
	long long res = 0;

	scanf("%d %d %d %d %d", &X, &Y, &A, &B, &C);
	for ( int i=0; i < A; ++i ){
		scanf("%d", &v);
		res += v;
		qA.push(v);
	}
	for ( int i=0; i < B; ++i ){
		scanf("%d", &v);
		res += v;
		qB.push(v);
	}
	for ( int i=0; i < C; ++i ){
		scanf("%d", &v);
		qC.push(v);
	}
	
	while ( (int)qA.size() > X ){ 
		res -= qA.top();
		qA.pop();
	}
	while ( (int)qB.size() > Y ){ 
		res -= qB.top();
		qB.pop();
	}
	
	while ( !qC.empty() ){
		if ( qC.top() <= min( qA.top(), qB.top() ) )
			break;
		if ( qA.top() <= qB.top() ){
			res -= qA.top();
			qA.pop();
			qA.push( qC.top() );
		}
		else {
			res -= qB.top();
			qB.pop();
			qB.push( qC.top() );
		}
		res += qC.top();		
		qC.pop();
	}	
	printf("%lld\n", res);
	return 0;
}
