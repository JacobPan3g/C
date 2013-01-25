#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main()
{
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);

	int N, M;
	int s[50][26];
	int target[50], tmp;
	string str;

	cin >> N >> M;

	while ( N != 0 && M != 0 )
	{

		for ( int i = 0; i < N; i++ )
			for ( int j = 0; j < M; j++ )
				cin >> s[i][j];
	
		int tag = 0;
		while (cin >> tmp, tmp!=-1)
			target[tag++] = tmp;

		cin >> str;
		while( str != "#" )
		{
			int next = 0;
			for ( int i = 0; i < str.length(); i++ )
				next = s[next][str[i]-'a'];

			bool ok = false;
			for ( int i = 0; i < tag; i++ )
				if ( next == target[i] )
				{
					cout << "YES" << endl;
					ok = true;
					break;
				}
			
			if (!ok)
				cout << "NO" << endl;

			cin >> str;
		}
	cin >> N >> M;
	}

	return 0;
}
