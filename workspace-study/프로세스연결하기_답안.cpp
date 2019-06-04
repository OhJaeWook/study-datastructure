#include<stdio.h>
int n;
int a[12][12];
int p[12][2];
int pl = 0;
int rl, res;


void dfs(int dep, int cl, int cnt)
{
	if (cl + (pl - dep) < rl)return;
	if (dep == pl)
	{
		if (rl < cl || (rl == cl && res > cnt))
		{
			rl = cl;
			res = cnt;
		}
		return;
	}
	int i, j;
	int si, sj;
	si = p[dep][0];
	sj = p[dep][1];
	j = sj;
	for (i = si + 1; i < n; i++)if (a[i][j] == 1)break;
	if (i == n) {
		for (i = si + 1; i < n; i++)a[i][j] = 1;
		dfs(dep + 1, cl + 1, cnt + (n - si - 1));
		for (i = si + 1; i < n; i++)a[i][j] = 0;
	}
	for (i = si - 1; i >= 0; i--)if (a[i][j] == 1)break;
	if (i < 0) {
		for (i = si - 1; i >= 0; i--)a[i][j] = 1;
		dfs(dep + 1, cl + 1, cnt + si);
		for (i = si - 1; i >= 0; i--)a[i][j] = 0;
	}
	i = si;
	for (j = sj + 1; j < n; j++)if (a[i][j] == 1)break;
	if (j == n) {
		for (j = sj + 1; j < n; j++)a[i][j] = 1;
		dfs(dep + 1, cl + 1, cnt + (n - sj - 1));
		for (j = sj + 1; j < n; j++)a[i][j] = 0;
	}
	for (j = sj - 1; j >= 0; j--)if (a[i][j] == 1)break;
	if (j < 0) {
		for (j = sj - 1; j >= 0; j--)a[i][j] = 1;
		dfs(dep + 1, cl + 1, cnt + sj);
		for (j = sj - 1; j >= 0; j--)a[i][j] = 0;
	}
	dfs(dep + 1, cl, cnt);
}
int main()
{
	int t, tv = 0;
	int i, j, k, l;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		rl = -1; res = 9999;
		pl = 0;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				scanf("%d", &a[i][j]);
				if (a[i][j] == 1)
				{
					p[pl][0] = i;
					p[pl][1] = j;
					pl++;
				}
			}
		}
		dfs(0, 0, 0);
		printf("#%d %d\n", ++tv, res);
	}
}
