#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define x first
#define y second

typedef pair <double, double> point; 

const int MaxN = 310;

int N, disc[MaxN], low[MaxN], lf[MaxN], dad[MaxN], T;
point P[MaxN], S;
bool adj[MaxN][MaxN], bio[MaxN], flag_no;
double R[MaxN], r;

inline int sgn(double x) {
  if (x < 0) return -1;
  if (x > 0) return 1;
  return 0;
}

inline double sqr(double x) { return x * x; }

inline double dist(point A, point B) {
  return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

inline double rand_slope(void) { return 456135.5312; }

point intersect(double k, double l, point A, point B) {
  if (A.x == B.x) return point(A.x, A.x * k + l);
  double k2 = (B.y - A.y) / (B.x - A.x);
  double l2 = A.y - A.x * k2;
  
  double X = (l2 - l) / (k - k2);
  double Y = k * X + l;
  return point(X, Y);
}

bool intersect_half(point A, point B) {
  double k = rand_slope();
  double c1 = A.y - A.x * k, c2 = B.y - B.x * k;
  if (sgn(c1) == sgn(c2)) return false;
  point P = intersect(k, S.y - S.x * k, A, B);
  //printf("(%.2lf %.2lf)\n",P.x,P.y);
  return P.x >= S.x;
}

void init(void) {
  scanf("%d",&N);
  for (int i = 0; i < N; ++i)
    scanf("%lf %lf %lf",&P[i].x,&P[i].y,&R[i]);
  scanf("%lf %lf %lf",&S.x,&S.y,&r);
  for (int i = 0; i < N; ++i)
    R[i] += r;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i != j && dist(P[i], P[j]) < R[i] + R[j])
	adj[i][j] = true;
}

void dfs(int x) {
  bio[x] = true;
  disc[x] = low[x] = ++T;

  lf[x] = -1;

  for (int y = 0; y < N; ++y) {
    if (!adj[x][y]) continue;
    if (bio[y] && low[x] > disc[y]) {
      low[x] = disc[y];
      lf[x] = y;
    }
    else if (!bio[y]) {
      dad[y] = x;
      dfs(y);
      if (low[x] > low[y]) {
	low[x] = low[y];
	lf[x] = lf[y];
      }
    }
  }

  if (lf[x] == -1)
    return;

  int tot = 0, curr = x;
  if (intersect_half(P[x], P[lf[x]])) ++tot;
  //printf("[%d %d]\n",lf[x],x);
  while (curr != lf[x]) {
    //printf("[%d %d]\n",curr,dad[curr]);
    if (intersect_half(P[curr], P[dad[curr]])) ++tot;
    curr = dad[curr];
  }
  //printf("\n");
  if (tot & 1) flag_no = true;
}

void solve(void) {
  for (int i = 0; i < N; ++i)
    if (!bio[i])
      dfs(i);
  printf(flag_no ? "NO\n" : "YES\n");
}

void open_files(void) {
  freopen("out.in", "r", stdin);
  freopen("out.out", "w", stdout);
}

int main(void) {
  open_files();
  init();
  solve();
  return 0;
}

