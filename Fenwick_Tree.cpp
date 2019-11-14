//by szubrilina

//An arr  of n integers is given. There are m requests of two types: the first  type is "c(pos, newval)" - change arr[pos] into newval.
//The second is "s(r, l)" - get sum of elements from l to r positions. FenwickTree is used to solve this problem. It requires O(logn) time to answer one request.


#include <iostream>
#include <vector>

using namespace std;

int sum(int position, std::vector<int> &fenwickTree)
{
	int sum = 0;
	for (; position >= 0; position = (position & (position + 1)) - 1)
		sum += fenwickTree[position];

	return sum;
}

int get_sum(int r, int l, std::vector<int> &fenwickTree)
{
	return sum(r, fenwickTree) - sum(l - 1, fenwickTree);
}

void add_value(int position, int delta, std::vector<int> &fenwickTree)
{
	for (; position < (int)fenwickTree.size(); position = (position | (position + 1)))
		fenwickTree[position] += delta;
}


int main()
{
	int n;
	std::cin >> n;

	std::vector<int> arr(n, 0);
	std::vector<int> fenwickTree(n, 0);

	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
		add_value(i, arr[i], fenwickTree);
	}

	int m; //number of requests

	std::cin >> m;

	for (int i = 0; i < m; ++i)
	{
		char type;

		std::cin >> type;

		if (type == 'u') //from update
		{
			int position;
			int new_value;

			std::cin >> position;
			std::cin >> new_value;

			int old_value = arr[i];

			arr[i] = new_value;

			add_value(position - 1, 0 - old_value, fenwickTree);
			add_value(position - 1, new_value, fenwickTree);
		}
		else //type == 's' from sum 
		{
			int l, r;
			std::cin >> l >> r;

			std::cout << get_sum(r - 1, l - 2, fenwickTree) << std::endl;
		}
	}
	return 0;
}