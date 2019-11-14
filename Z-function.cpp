#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef double dl;


vector<int> z_function(string &s)
{
	vector<int> z((int)s.size());

	int l = 0;
	int r = 0;

	z[0] = (ll)s.size();

	for (int i = 1; i < (ll)s.size(); ++i)
	{
		if (i < r)
			z[i] = min(r - i, z[i - l]);

		while (i + z[i] < (ll)s.size() && s[z[i]] == s[i + z[i]])
			++z[i];

		if (i + z[i] >= r)
		{
			l = i;
			r = i + z[i];
		}
	}

	return z;
}

void solve()
{
	string s;

	cin >> s;

	vector<int> ans = z_function(s);

	for (int in : ans)
		cout << in << " ";

	cout << endl;
}

int main()
{
	solve();

	return 0;
}

