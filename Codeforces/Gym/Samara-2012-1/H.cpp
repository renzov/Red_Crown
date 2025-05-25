#include<cstdio>
#include<cstring>

char s[100005];
int k;
int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int f[26] = {0};
  int n;
  scanf("%d %s",&k,s);
  n = strlen(s);
  int r = 0;
  int l = 0;
  int bestl = 0;
  int bestr = 0;
  int cnt = 0;
  int pos;
  while ( r < n ){
	 while ( r < n ){
		pos = s[r] - 'a';
		if( f[pos] == 0 ){
		  cnt++; f[pos]++;
		  if ( cnt > k ) break;
		  if ( (r-l) > (bestr-bestl) ){
			 bestl = l; bestr = r;
		  }
		} 
		else {
		  if ( (r-l) > (bestr-bestl) ){
			 bestl = l; bestr = r;
		  }
		  f[pos]++;
		}
		r++;
	 }
	 while ( r < n && cnt > k ){
		pos = s[l] - 'a';
		f[pos]--;
		if ( f[pos] == 0 ) cnt--;
		l++;
	 }
	 r++;
  }
  printf("%d %d\n",bestl+1,bestr+1);
  return 0;
}