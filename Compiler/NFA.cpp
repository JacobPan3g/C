#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

typedef int STATUS;

int idx;
string str;
vector<STATUS> states[50][27];
bool target[50];
// 用来避免重复的数据结构
stack<STATUS> oldStates;
stack<STATUS> newStates;
bool alreadyOn[50];		//用来检查相应的状态是否已经在newStates中

char nextChar()
{
	return str[idx++];
}

vector<STATUS> move( STATUS s, char c )
{
	if ( c == 'E' )
		return states[s][0];
	else
		return states[s][c-'a'+1];
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

bool isInTarget( stack<STATUS> st )
{
	bool ok = false;
	while ( !st.empty() )
	{
		STATUS top = st.top();
		st.pop();
		if ( target[top] )
		{
			ok = true;
			break;
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



void addState( STATUS s )
{
	newStates.push( s );
	alreadyOn[s] = true;
	vector<STATUS> tmpV = move( s, 'E' );
	for ( int i = 0; i < tmpV.size(); i++ )
	{
		if ( !alreadyOn[ tmpV[i] ] )
			addState( tmpV[i] );
	}
}

void e_closure( vector<STATUS> T )
{
	for( int i = 0; i < T.size(); i++ )
	{
		oldStates.push( T[i] );
	}	
	while ( !oldStates.empty() )
	{
		STATUS top = oldStates.top();
		oldStates.pop();
		vector<STATUS> tmpV = move( top, 'E' );
		for ( int i = 0; i < tmpV.size(); i++ )
		{
			if ( !alreadyOn[ tmpV[i] ] )
				addState( tmpV[i] );
			
		}
	}
	while ( !newStates.empty() )
	{
		STATUS top = newStates.top();
		newStates.pop();
		oldStates.push( top );
		alreadyOn[ top ] = false;
	}
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
		// 初始化
		while ( !oldStates.empty() )
			oldStates.pop();
		for ( int i = 0; i < 50; i++ )
		{
			target[i] = false;
			for ( int j = 0; j < 27; j++ )
				states[i][j].clear();
		}
		

		for ( int i = 0; i < N; i++ )
		{	
			for ( int j = 0; j < M; j++ )
			{
				cin >> tmpStatus;
				stringToVector( tmpStatus, states[i][j] );
			}
		}
		
		STATUS tmp;
		while ( cin >> tmp, tmp != -1 )
		{
			target[tmp] = true;
		}

		while ( cin >> str, str != "#" )
		{
			idx = 0;

			vector<STATUS> s;
			s.push_back( 0 );
			e_closure( s );

			// 把S里所有状态压进oldStates里
			/*for ( int i = 0; i < S.size(); i++ )
			{
				oldStates.push( S[i] );
				//alreadyOn[ s[i] ] = true;
			}*/

			char c = nextChar();
			while( idx != str.length()+1 )
			{
				// 实现：S = e_closure( move( S, c ) );
				// oldStates与newStates之间的转换
				while ( !oldStates.empty() )
				{
					STATUS top = oldStates.top();
					oldStates.pop();

					vector<STATUS> tmpV = move(top, c);
					for ( int i = 0; i < tmpV.size(); i++ )
					{
						if ( !alreadyOn[ tmpV[i] ] )
							addState( tmpV[i] );
					}
				}
				while ( !newStates.empty() )
				{
					STATUS top = newStates.top();
					newStates.pop();
					oldStates.push( top );
					alreadyOn[top] = false;
				}
				// 实现完毕

				c = nextChar();
			}

			if ( isInTarget( oldStates ) )
				cout << "YES" << endl;
			else
				cout << "NO" << endl;

		}
	}

	return 0;
}
