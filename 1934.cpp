#include <iostream>
using namespace std;

struct Ball
{
	int l;
	int r;
};

int main()
{
	int t;
	cin >> t;
	while( t-- )
	{
		Ball balls[500001];
		
		int n;
		int m;
		cin >> n >> m;
		
		// 这里留一个0位置来指示哪个是开头
		for ( int i = 0; i <= n; i++ )
		{
			balls[i].l = i - 1;
			balls[i].r = i + 1;
		}

		while( m-- )
		{
			int op, a, b;
			cin >> op >> a >> b;
			if ( op == 1 )
			{
				// 处理移走a后留下的空缺
				balls[ balls[a].l ].r = balls[a].r;
				balls[ balls[a].r ].l = balls[a].l;
				// 告诉a新位置的邻居
				balls[a].l = balls[b].l;
				balls[a].r = b;
				// 告诉邻居们a来了
				balls[ balls[b].l ].r = a;
				balls[b].l = a;
			}
			else
			{
				// 大体意思和上面一样
				balls[ balls[a].l ].r = balls[a].r;
				balls[ balls[a].r ].l = balls[a].l;

				balls[a].l = b;
				balls[a].r = balls[b].r;

				balls[ balls[b].r ].l = a;
				balls[b].r = a;
			}
		}
		int counter = 1;
		int s = balls[0].r;
		while ( counter <= n )
		{
			cout << s << " ";
			s = balls[s].r;
			counter++;
		}
		cout << endl;
	}
	return 0;
}
