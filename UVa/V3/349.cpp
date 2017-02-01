#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int m,n;

pair<int,int> elec[10];
int v[105][10];

int election(){
  int frec[10] = {0};
  for (int i=0; i < m; ++i)
	 if (v[i][0] != -1)
		frec[ v[i][0] ]++;
  int p = 0;
  for (int i=0; i < 5; ++i){
		if (frec[i]){
		  elec[p].first = -frec[i];
		  elec[p].second = i+1;
		  ++p;
		}
  }
  sort(elec,elec + p);
}

void eliminate(int e){
  
  for (int i=0; i<m; ++i){
		for (int j=0; j < n; ++j){
			 if (v[i][j] == e){
				  for (int k=j; k < n-1; ++k)
						v[i][k] = v[i][k+1];
				  v[i][n-1] = -1;
				  break;
			 }
		}
  }
  
  n--;
}

int main(){
  int total;
  int invalid;
  bool valid;
  int tmp[10];
  int cases = 0;
  while (scanf("%d %d",&n,&m) && (n || m)){
		cases++;
		int total = m;
		int p = 0;
		invalid = 0;
		for (int i=0; i < m; ++i){
			 valid = true;
			 for (int j=0; j < n; ++j) tmp[j] = 0;
			 for (int j=0; j < n; ++j){
				  scanf("%d",&v[p][j]);
				  if (v[p][j] < 1 || v[p][j] > n) valid = false;
				  if ( (v[p][j] - 1) >= 0 ){
						tmp[ v[p][j] - 1 ]++;
						if ( tmp[ v[p][j] - 1 ] > 1 ) valid = false;
						v[p][j]--;
				  }
			 }
			 if (!valid){
				  invalid++;
				  total--;
			 }
			 else {
				p++;
			 }
		}
		m = p;
		printf("Election #%d\n", cases);
      if (invalid)
		  printf("   %d bad ballot(s)\n", invalid);

		bool tie;

		while (1){
			 election();
			 for (int i=0; i < n; ++i) elec[i].first *= -1;
			 tie = true;
			 if (elec[0].first * 2 > m){
				  printf("   Candidate %d is elected.\n",elec[0].second);
				  break;
			 }
			 tie = true;
			 for (int i=0; i<n && tie; ++i)
				tie &= (elec[0].first == elec[i].first);
			 if (tie){
				  printf("   The following candidates are tied:");
				  for (int i=0; i < n; ++i) printf(" %d",elec[i].second);
				  putchar('\n');
				  break;
			 }
			 eliminate(elec[n-1].second - 1);
		}
  }

  return 0;
}