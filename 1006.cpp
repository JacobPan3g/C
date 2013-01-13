#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// 找出字符c在字符串str的位置，以下将通过这个来求逆序和
int find( char c, char str[] )
{
	for ( int i = 0; i < 5; i++ )
		if ( str[i] == c )
			return i;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);


	char p[180][5];
	char chr[5] = {'A', 'B', 'C', 'D', 'E'};
	int cnt = 1;
	
	// 生成全排列
	for ( int i = 0; i < 5; i++ )
		p[0][i] = chr[i];
	while ( next_permutation( chr, chr+5 ) )
	{
		for ( int i = 0; i < 5; i++ )
			p[cnt][i] = chr[i];
		cnt++;
	}

	//cout << cnt;
	// 开始接受用户输入
	int n;
	char rank[110][5];
	while( cin >> n, n )
	{
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < 5; j++ )
				cin >> rank[i][j];
		
		int min = 10000;
		int sco = 0;			// 逆序数个数
		char temp[5];
		char res[5];

		// 对于全排列的每一个，算出与输入的rank的逆序和，
		for ( int i = 0; i < cnt; i++ )
		{
			for ( int j = 0; j < 5; j++ )
				temp[j] = p[i][j];
			sco = 0;

			// 与每一个输入的rank比较之后，求出逆序和
			for ( int j = 0; j < n; j++ )
			{
				for ( int k0 = 0; k0 < 4; k0++ )
					for ( int k1 = k0 + 1; k1 < 5; k1++ )
					{
						if ( find( rank[j][k0], temp ) > find( rank[j][k1], temp ) )
							sco++;
					}

			}

			if ( min > sco )
			{
				min = sco;
				memcpy( res, temp, sizeof(temp) );
			}

		}
		
		for ( int i = 0; i < 5; i++ )
			cout << res[i];
		cout << " is the median ranking with value " << min << "." << endl;
	}

	return 0;
}
