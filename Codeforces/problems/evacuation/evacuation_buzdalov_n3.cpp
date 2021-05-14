#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long i64;

struct indexed
{
    int index;
    int value;

    inline bool operator < (indexed const &that) const
    {
        return value < that.value;
    }
};

i64 v[4001][4001];
bool b[4001][4001];
int n, m;

indexed ts[4000];
indexed ss[4000];

int ans[4000];

int main()
{
    freopen("evacuation.in", "rt", stdin);
    freopen("evacuation.out", "wt", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        ts[i].index = i;
        scanf("%d", &ts[i].value);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        ss[i].index = i;
        scanf("%d", &ss[i].value);
    }
    std::sort(ts, ts + n);
    std::sort(ss, ss + m);
    for (int t = 0; t <= n; ++t)
        for (int s = 0; s <= m; ++s)
            v[t][s] = 9000000000000000000LL;
    v[0][0] = 0;
    for (int t = 0; t < n; ++t)
    {
        for (int s = 0; s < m; ++s)
        {
            i64 sum = v[t][s] + std::abs(ts[t].value - ss[s].value);
            if (v[t + 1][s + 1] > sum)
            {
                v[t + 1][s + 1] = sum;
                b[t + 1][s + 1] = true;
                for (int nt = t + 1; nt < n; ++nt)
                {
                    sum += std::abs(ts[nt].value - ss[s].value);
                    if (v[nt + 1][s + 1] > sum)
                    {
                        v[nt + 1][s + 1] = sum;
                        b[nt + 1][s + 1] = false;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    printf("%lld\n", v[n][m]);
    for (int i = n - 1, cs = m; i >= 0; --i)
    {
        ans[ts[i].index] = ss[cs - 1].index + 1;
        cs -= b[i + 1][cs];
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
