#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

typedef int STATUS;

int idx;
string str;
vector<STATUS> states[50][27];
int numTar;
STATUS target[50];

char nextChar()
{
	return str[idx++];
}

vector<STATUS> move( vector<STATUS> S, char c )
{
	vector<STATUS> res;
	for ( int i = 0; i < S.size(); i++ )
	{
		if ( states[S[i]][c-'a'+1].size() != 0 )
		{
			for ( int j = 0; j < states[S[i]][c-'a'+1].size(); j++ )
				res.push_back( states[S[i]][c-'a'+1][j] );
		}
	}

	return res;
}

bool isInTarget( vector<STATUS> S )
{
	bool ok = false;
	for ( int i = 0; i < numTar; i++ )
	{
		for ( int j = 0; j < S.size(); j++ )
		{
			if ( S[j] == target[i] )
			{
				ok = true;
				break;
			}
		}
	}
	return ok;
}

void stringToVector( string str, vector<STATUS> &v )
{
	str = str.substr(1, str.length()-2);
	
	char *s = (char*)str.c_str();
	
	char *p;
	p = strtok(s,",");
	while(p)
	{
		stringstream stream;
		int num;
		stream << p;
		stream >> num;
		v.push_back( num );
		p = strtok(NULL, ",");
	}
}

vector<STATUS> e_closure( vector<STATUS> T )
{
	vector<STATUS> res;
	for( int i = 0; i < T.size(); i++ )
	{
		res.push_back( T[i] );
		if ( states[T[i]][0].size() != 0 )
		{
			for ( int j = 0; j < states[T[i]][0].size(); j++ )
				res.push_back( states[T[i]][0][j] );
		}
	}
	return res;
}

void testOutput(int N, int M)
{
	for ( int i = 0; i < N; i++ )
	{
		for ( int j = 0; j < M; j++ )
		{
			cout << "{ ";
			for ( int k = 0; k < states[i][j].size(); k++ )
				cout << states[i][j][k] << " ";
			cout << " }";
		}
		cout << endl;
	}
}

int main()
{

freopen("input.txt","r",stdin);

	int N, M;
	string tmpStatus;
	while ( cin >> N >> M, N!=0 && M!=0 )
	{
		for ( int i = 0; i < N; i++ )
		{	
			for ( int j = 0; j < M; j++ )
			{
				cin >> tmpStatus;
				//cout << tmpStatus << endl;
				stringToVector( tmpStatus, states[i][j] );
			}
		}
		//testOutput(N, M);
		
		numTar = 0;
		STATUS tmp;
		while ( cin >> tmp, tmp != -1 )
		{
			target[numTar++] = tmp;
		}

		while ( cin >> str, str != "#" )
		{
			idx = 0;

			vector<STATUS> s;
			s.push_back( 0 );
			vector<STATUS> S = e_closure( s );
			char c = nextChar();
			while( idx != str.length()+1 )
			{
				S = e_closure( move( S, c ) ); 
				c = nextChar();
			}

			if ( isInTarget( S ) )
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}

	return 0;
}
