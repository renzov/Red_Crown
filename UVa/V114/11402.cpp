#include<cstdio>
#include<cstring>
const int MAX = 2097150;
int sum[MAX];
char prop[MAX];
int cad[1024005];
char tmp[55];

void build_tree(int n,int L,int R){
  prop[n] = (char)0;
  if (L==R){
	 sum[n] = cad[L];
	 return;
  }
  int m = (L + R) >> 1;
  build_tree(2*n+1,L,m);
  build_tree(2*n+2,m+1,R);
  sum[n] = sum[2*n+1] + sum[2*n+2];
}

void change_prop(int n,char p){
  if (p==(char)0) return;
  if (prop[n] == (char)0 || p != 'I') prop[n] = p;
  else if (prop[n] == 'I') prop[n] = 0;
  else prop[n] = (prop[n] == 'F')? 'E':'F';
}

void update(int n,int L,int R,int l,int r,char op){
	 if (L==l && r==R){
		if (op == 'F') sum[n] = R - L + 1;
		else if (op == 'E') sum[n] = 0;
		else sum[n] = (R - L + 1) - sum[n];
		if (L==R) prop[n] = 0;
		else change_prop(n,op);
		return;
	 }
	 int m = (L + R) >> 1;
	 if (prop[n]){
		if (prop[n] == 'F'){ sum[2*n + 1] = m - L + 1; sum[2*n+2] = R - m; }
		else if (prop[n] == 'E'){ sum[2*n + 1] = 0; sum[2*n + 2] = 0; }
		else { sum[2*n+1] = (m - L + 1) - sum[2*n+1]; sum[2*n+2] = (R - m) - sum[2*n+2]; }
		if ((R-L) == 1){ prop[2*n + 1] = 0; prop[2*n + 2] = 0; }
		else { change_prop(2*n+1,prop[n]); change_prop(2*n+2,prop[n]); }
		prop[n] = 0;
	 }
	 if (r <= m) update(2*n+1,L,m,l,r,op);
	 else if (l > m) update(2*n+2,m+1,R,l,r,op);
	 else update(2*n+1,L,m,l,m,op),update(2*n+2,m+1,R,m+1,r,op);
	 sum[n] = sum[2*n+1] + sum[2*n+2];
}

int query(int n,int L,int R,int l,int r){
  if (L==l && r==R) return sum[n];
  int m = (L + R) >> 1;
  if (prop[n]){
		if (prop[n] == 'F'){ sum[2*n + 1] = m - L + 1; sum[2*n+2] = R - m; }
		else if (prop[n] == 'E'){ sum[2*n + 1] = 0; sum[2*n + 2] = 0; }
		else { sum[2*n+1] = (m - L + 1) - sum[2*n+1]; sum[2*n+2] = (R - m) - sum[2*n+2]; }
		if ((R-L) == 1){ prop[2*n + 1] = 0; prop[2*n + 2] = 0; }
		else { change_prop(2*n+1,prop[n]); change_prop(2*n+2,prop[n]); }
		prop[n] = 0;
  }
  if (r <= m) return query(2*n+1,L,m,l,r);
  else if (l > m) return query(2*n+2,m+1,R,l,r);
  return query(2*n+1,L,m,l,m) + query(2*n+2,m+1,R,m+1,r);
}

int main(){
  int n;
  int runs;
  int s;
  int t;
  int q;
  int cases = 0;
  int a,b;
  char type;
  int m;
  
  scanf("%d",&runs);
  while (runs--){
		cases++;
		scanf("%d",&m);
		n = 0;
		for (int i=0; i < m; ++i){
			 scanf("%d %s",&t,tmp);
			 s = strlen(tmp);
			 for (int j=0; j < t; ++j)
				for (int k=0; k < s; ++k)
					 cad[n++] = (tmp[k] - '0');
		}
		build_tree(0,0,n-1);
		printf("Case %d:\n",cases);
		scanf("%d",&q);
		int c = 0;
		for (int i=0; i < q; ++i){
			 scanf(" %c %d %d",&type,&a,&b);
			 if (type == 'S'){ printf("Q%d: %d\n",++c,query(0,0,n-1,a,b)); }
			 else update(0,0,n-1,a,b,type);
		}
  }
  
  return 0; 
}