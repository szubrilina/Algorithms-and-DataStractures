//by szubrilina
//An array of n integers is given. There are requests of two types: answer the value of element a[i] ("get)" or add to all elements from l to r some value ("add")

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef double dl;
typedef long long ll;


void built(ll v, ll l, ll r, vector<ll> &t, vector<ll> &a)
{
	if (l == r)
	{
		t[v] = a[l];
	}
	else
	{
		ll m = (l + r) / 2;

		built(v * 2, l, m, t, a);
		built(v * 2 + 1, m + 1, r, t, a);
	}
}

void push(ll v, vector<ll> &add)
{
	add[v * 2] += add[v];
	add[v * 2 + 1] += add[v];

	add[v] = 0;
}

ll get(ll v, ll l, ll r, ll pos, vector<ll> &t, vector<ll> &add)
{
	if (l == r)
	{
		return t[v] + add[v];
	}

	push(v, add);

	ll m = (l + r) / 2;

	if (pos <= m)
		return get(v * 2, l, m, pos, t, add);
	else
		return get(v * 2 + 1, m + 1, r, pos, t, add);
}

void update(ll v, ll tl, ll tr, ll l, ll r, ll del, vector<ll> &t, vector<ll> &add)
{
	if (l > r)
		return;

	if (tl == l && tr == r)
	{
		add[v] += del;
	}
	else
	{
		push(v, add);

		ll tm = (tl + tr) / 2;

		update(v * 2, tl, tm, l, min(r, tm), del, t, add);
		update(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, del, t, add);
	}
}

int main()
{
	ll n;
	scanf("%lld", &n);

	vector<ll> t, a, add;

	a.resize(n);
	t.resize(4 * n, 0);
	add.resize(4 * n, 0);

	for (int i = 0; i < n; ++i)
	{
		scanf("%lld", &a[i]);
	}

	built(1, 0, n - 1, t, a);

	ll m;
	scanf("%lld", &m);

	for (int i = 0; i < m; ++i)
	{
		char c;
		scanf("\n%c", &c);

		if (c == 'g') //request "get": ask the value of ind'th element
		{
			int ind;
			scanf("%lld", &ind);
			--ind;

			ll value = get(1, 0, n - 1, ind, t, add);
			printf("%lld\n", value);
		}
		else //request "add": add delta to all elements from l-index to r-index 
		{
			ll l, r, del;
			scanf("%lld%lld%lld", &l, &r, &del);

			--l;
			--r;

			update(1, 0, n - 1, l, r, del, t, add);
		}
	}

	return 0;
}