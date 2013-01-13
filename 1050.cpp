#include <iostream>
#include <algorithm>
using namespace std;

int ans;
bool ok;

int Div( int x, int y )
{
	if ( x < y )
		swap( x, y );
	if ( y == 0 || x % y != 0 )
		return -1;
	return x / y;
}

void dfs( int arr[], int size )
{
	if ( ok )
		return;
	// Test
	//cout << "Test begin!" << endl;
	//for ( int i = 0; i < size; i++ )
	//	cout << arr[i] << endl;
	//cout << "Test end!" << endl;

	// 注意ans，target和arr[0]之间的关系
	// 使用ans来找出最接近target的（也包括了等于target的）
	if ( arr[0] <= arr[5] &&  arr[0] > ans )
	{
		ans = arr[0];
		if ( ans == arr[5] )
		{
			ok = true;
			return;
		}
	}

	// 只剩一个数，不能再算了
	if ( size == 1 )
		return;

	int num[6];
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = i+1; j < size; j++ )
		{
			for ( int k = 0, h = 1; k < size; k++ )
				if ( k != i && k != j )
					num[h++] = arr[k];
			num[5] = arr[5];
			
			// Open
			num[0] = arr[i] + arr[j];
			dfs( num, size - 1 );

			num[0] = arr[i] - arr[j];
			dfs( num, size - 1 );
			num[0] = arr[j] - arr[i];
			dfs( num, size - 1 );

			num[0] = arr[i] * arr[j];
			dfs( num, size - 1 );

			num[0] = Div( arr[i], arr[j] );
			if ( num[0] != -1 )
				dfs( num, size - 1 );
		}
	}
}

int main()
{
	int N;
	cin >> N;
	while ( N-- )
	{
		int a[6];
		for ( int i = 0; i < 6; i++ )
			cin >> a[i];
		
		ok = false;
		ans = -200000;
		dfs( a, 5 );
		cout << ans << endl;
	}

	return 0;
}
