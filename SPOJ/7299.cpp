#include<cstdio>
const int MAX = 900000;
int Z[MAX][3];
int prop[MAX];

void apply_prop(int n,int t){
	int a = Z[n][0];
	int b = Z[n][1];
	int c = Z[n][2];
	if (t == 1){
		Z[n][1] = a;
		Z[n][2] = b;
		Z[n][0] = c;
	}
	else if (t == 2){
		Z[n][2] = a;
		Z[n][1] = c;
		Z[n][0] = b;
	}
}

void build_tree(int n,int L,int R){
	prop[n] = 0;
	Z[n][2] = Z[n][1] = 0;
	Z[n][0] = R - L + 1;
	if (L==R) return;
	int m = (L + R) >> 1;
	build_tree(2*n + 1,L,m);
	build_tree(2*n + 2,m+1,R);
}

void update(int n,int L,int R,int l,int r){
	if (L==l && r==R){
		prop[n] = (prop[n] + 1)%3;
		apply_prop(n,1);
		if (l==r) prop[n] = 0;
		return;
	}
	if (prop[n]){
		prop[2*n+1] = (prop[2*n+1] + prop[n])%3;
		prop[2*n+2] = (prop[2*n+2] + prop[n])%3;
		apply_prop(2*n+1,prop[n]); apply_prop(2*n+2,prop[n]);
		if ((R-L) == 1){ prop[2*n + 1] = 0; prop[2*n + 2] = 0; }
		prop[n] = 0;
	}
	int m = (L+R) >> 1;
	if (l > m) update(2*n+2,m+1,R,l,r);
	else if (m >= r) update(2*n+1,L,m,l,r);
	else update(2*n+1,L,m,l,m),update(2*n+2,m+1,R,m+1,r);
	for (int i=0; i < 3; ++i) Z[n][i] = Z[2*n+1][i] + Z[2*n+2][i];
}

int query(int n,int L,int R,int l,int r){
	if (l==L && r==R) return Z[n][0];
	if (prop[n]){
		prop[2*n+1] = (prop[2*n+1] + prop[n])%3;
		prop[2*n+2] = (prop[2*n+2] + prop[n])%3;
		apply_prop(2*n+1,prop[n]); apply_prop(2*n+2,prop[n]);
		if ((R-L) == 1){ prop[2*n + 1] = 0; prop[2*n + 2] = 0; }
		prop[n] = 0;
	}
	int m = (L + R) >> 1;
	if (l > m) return query(2*n+2,m+1,R,l,r);
	else if (m >= r) return query(2*n+1,L,m,l,r);
	return query(2*n+1,L,m,l,m) + query(2*n+2,m+1,R,m+1,r);
}

int main(){
	int n,q;
	int t,a,b;
	scanf("%d %d",&n,&q);
	build_tree(0,0,n-1);
	for (int i=0; i < q; ++i){
		scanf("%d %d %d",&t,&a,&b);
		if (t) printf("%d\n",query(0,0,n-1,a,b));
		else update(0,0,n-1,a,b);
	}
	return 0;
}

