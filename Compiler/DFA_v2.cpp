#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

typedef int STATUS;

int idx;
string str;
STATUS states[50][26];
int numTar;
STATUS target[50];

char nextChar()
{
	return str[idx++];
}

STATUS move( STATUS s, char c )
{
	return states[s][c-'a'];
}

bool isInTarget( STATUS s )
{
	bool ok = false;
	for ( int i = 0; i < numTar; i++ )
	{
		if ( s == target[i] )
		{
			ok = true;
			break;
		}
	}
	return ok;
}

int main()
{

freopen("input.txt","r",stdin);

	int N, M;
	while ( cin >> N >> M, N!=0 && M!=0 )
	{
		for ( int i = 0; i < N; i++ )
		{	
			for ( int j = 0; j < M; j++ )
			{
				cin >> states[i][j];
			}
		}
		
		numTar = 0;
		STATUS tmp;
		while ( cin >> tmp, tmp != -1 )
		{
			target[numTar++] = tmp;
		}

		while ( cin >> str, str != "#" )
		{
			idx = 0;

			STATUS s = 0;
			char c = nextChar();
			while( idx != str.length()+1 )
			{
				s = move( s, c ); 
				c = nextChar();
			}

			if ( isInTarget( s ) )
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}

	return 0;
}
