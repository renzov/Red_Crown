#include<cstdio>
#include<cstring>

struct R {
  int a,b;
  double f;
};

R r[35];

int from , to;
int n;

inline bool pertain(int idx,int p){
  return r[idx].a == p || r[idx].b == p;
}

bool serial(int x,int y){
  bool A = pertain(y,r[x].a);
  bool B = pertain(y,r[x].b);
  return (A && !B) || (!A && B);
}

bool parallel(int x,int y){
  return pertain(y,r[x].a) && pertain(y,r[x].b);
}


bool has_free(){

  int p;
  bool found;
  bool A,B;

  do {
	 found = false;
	 for (p=0; p < n; ++p){
		  if (pertain(p,from) || pertain(p,to)) continue;
		  A = false;
		  B = false;
		  for (int i=0; i < n; ++i){
				if (i!=p){
					 if (pertain(i,r[p].a)) A = true;
					 if (pertain(i,r[p].b)) B = true;
				}
		  }
		  if (!A || !B){
				found = true;
				r[p] = r[--n];
				p--;
		  }
	 }
  }
  while (found);
  return false;
}

bool others(int r1,int r2,int p){
  for  (int i=0; i<n; ++i){
	 if (i==r1 || i==r2) continue;
	 if (pertain(i,p)) return true;
  }
  return false;
}

bool has_serial(){
  int i,j;
  R tmp;
  bool found = false;
  int join;
  
  for (i=0; i < n; ++i){
	 for (j=i+1; j < n; ++j){
		  if (serial(i,j)){
				join = (pertain(j,r[i].a))? r[i].a:r[i].b;
				if (join != from && join != to && !others(i,j,join)){
					tmp.a = (r[i].a==join)? r[i].b:r[i].a;
					tmp.b = (r[j].a==join)? r[j].b:r[j].a;
					found = true;
					tmp.f = r[i].f + r[j].f;
					r[i] = tmp;
					r[j] = r[--n];
					j--;
				}
		  }
	 }
  }
  return found;
}

bool has_parallel(){
  int i,j;
  bool found = false;
  double f;
  for (i=0; i < n; ++i){
	 f = 1 / r[i].f;
	 for (j=i+1; j < n; ++j){
		if (parallel(i,j)){
			 found = true;
			 f += 1 / r[j].f;
			 r[j] = r[--n];
			 j--;
		}
	 }
	 r[i].f = 1 / f;
  }
  return found;
}

int main(){

  int res;
  int cases = 0;
  while (scanf("%d %d %d",&n,&from,&to) && ( n || from || to )){
		cases++;
		for (int i=0; i < n; ++i){
			 scanf("%d %d %lf",&r[i].a,&r[i].b,&r[i].f);
		}

		while (has_free() | has_serial() | has_parallel());
		
		for (res=0; res < n; ++res){
		  if (pertain(res,from) && pertain(res,to)){
			 break;
		  }
		}
		if (res == n){
			printf("No circuit from %d to %d.\n", from, to);
		}
		else {
		  printf("Case %d: %.2lf Ohms\n", cases, r[res].f);
		}
  }

  return 0;
}