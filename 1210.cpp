#include <iostream>
#include <string>
using namespace std;

int main()
{
	string pre, post;
	cin >> pre >> post;
	
	int ans = 1;

	for ( int i = 1; i < pre.size(); i++ )
	{
		for ( int j = 0; j < post.size()-1; j++ )
		{
			if ( pre[i] == post[j] && pre[i-1] == post[j+1])
			{
				ans *= 2;
			}
		}
	}

	cout << ans;

	return 0;
}
