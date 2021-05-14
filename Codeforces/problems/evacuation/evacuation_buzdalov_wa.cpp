#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>

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

int n, m;

indexed ts[4000];
indexed ss[4000];

int sep[4001];
int ans[4000];
int diff[4000][4000];

int main()
{
    freopen("evacuation.in", "rt", stdin);
    freopen("evacuation.out", "wt", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        ts[i].index = i;
        scanf("%d", &ts[i].value);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        ss[i].index = i;
        scanf("%d", &ss[i].value);
    }
    std::sort(ts, ts + n);
    std::sort(ss, ss + m);

    for (int t = 0; t < n; ++t)
    {
        for (int s = 0; s < m; ++s)
        {
            diff[t][s] = std::abs(ts[t].value - ss[s].value);
        }
    }

    sep[0] = -1;
    sep[m] = n - 1;
    for (int s = 1; s < m; ++s)
    {
        for (int t = 0; t < n; ++t)
        {
            if (diff[t][s - 1] < diff[t][s])
            {
                sep[s] = t;
            }
        }
        sep[s] = std::max(sep[s], sep[s - 1] + 1);
    }
    for (int s = m - 1; s > 0; --s)
    {
        sep[s] = std::min(sep[s], sep[s + 1] - 1);
    }
    i64 curr = 0;
    for (int s = 0; s < m; ++s)
    {
        for (int t = sep[s] + 1; t <= sep[s + 1]; ++t)
        {
            curr += diff[t][s];
        }
    }

    for (int s = 0; s < m; ++s)
    {
        for (int t = sep[s] + 1; t <= sep[s + 1]; ++t)
        {
            ans[ts[t].index] = ss[s].index + 1;
        }
    }
    printf("%lld\n", curr);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}
