#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int sum;
	int len;
	int maxSum;
	int prefSum;
	int suffSum;
	int maxLen;
	int prefLen;
	int suffLen;
};
const int MAX = 100005;
int a[MAX];
node seg_tree[4 * MAX];

void calculate( node &parent , node &left , node &right){
	parent.len = left.len + right.len;
	parent.sum = left.sum + right.sum;
	//Calculate prefSum/Len
	if ( left.prefSum > (left.sum + right.prefSum) ){
		parent.prefSum = left.prefSum;
		parent.prefLen = left.prefLen;
	}
	else {
		parent.prefSum = left.sum + right.prefSum;
		parent.prefLen = left.len + right.prefLen;
	}
	//Calculate suffSum/Len
	if ( right.suffSum > ( right.sum + left.suffSum ) ){
		parent.suffSum = right.suffSum;
		parent.suffLen = right.suffLen;
	}
	else {
		parent.suffSum = right.sum + left.suffSum;
		parent.suffLen = right.len + left.suffLen; 
	}
	int midSum = left.suffSum + right.prefSum;
	int midLen = left.suffLen + right.prefLen;
	//Calculate maxSum/Len
	parent.maxSum = left.maxSum; parent.maxLen = left.maxLen;
	if ( parent.maxSum < right.maxSum || ( parent.maxSum == right.maxSum && parent.maxLen < right.maxLen ) ){
		parent.maxSum = right.maxSum; parent.maxLen = right.maxLen;
	}
	if ( parent.maxSum < midSum || ( parent.maxSum == midSum && parent.maxLen < midLen ) ){
		parent.maxSum = midSum; parent.maxLen = midLen;
	}
}

void build_tree( int n , int L , int R ){
	if ( L==R ){
		seg_tree[n].sum = seg_tree[n].suffSum = seg_tree[n].prefSum = seg_tree[n].maxSum = a[L];
		seg_tree[n].len = seg_tree[n].prefLen = seg_tree[n].suffLen = seg_tree[n].maxLen = 1;
		return;
	}
	int M = ( L + R ) >> 1;
	int l = n << 1;
	int r = ( n << 1 ) + 1;
	build_tree( l , L , M );
	build_tree( r , M + 1, R );
	calculate( seg_tree[n] , seg_tree[l] , seg_tree[r] );
}

node query(int n , int L, int R, int l, int r){
	if ( L==l && r==R ){
		return seg_tree[n];
	}
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( n << 1 , L , M , l , r );
	if ( l > M ) return query( (n << 1) + 1 , M + 1 , R , l , r );
	node left = query( n << 1 , L , M , l , M );
	node right = query( (n<<1) + 1 , M + 1 , R , M + 1, r );
	node res;
	calculate( res , left , right );
	return res;
}

int main(){
	int runs;
	int N,Q;
	int A,B;
	node res;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&N);
		for ( int i=1; i <= N; ++i ) scanf("%d",a+i);
		build_tree( 1 , 1 , N );
		scanf("%d",&Q);
		while ( Q-- ){
			scanf("%d %d",&A,&B);
			if ( B < A ) swap(A,B);
			res = query( 1 , 1 , N , A , B );
			printf("%d %d\n",res.maxSum,res.maxLen);		
		}
	}	
		
	return 0;
}
