#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
using namespace std;

int main()
{
freopen( "input.txt", "r", stdin );

	string str;
	while ( cin >> str, str != "#" )
	{
		stack<char> st;
		for ( int i = 0; i < str.size(); i++ )
		{
			if ( str[i] >= '0' && str[i] <= '9' )
				cout << str[i];
			else if ( str[i] == '(' )
				st.push( str[i] );
			else if ( str[i] == ')' )
			{
				while ( st.top() != '(' )
				{
					cout << st.top();
					st.pop();
				}
				st.pop();
			}
			else if ( str[i] == '+' || str[i] == '-' )
			{
				if ( !st.empty() && st.top() != '(' )
				{
					cout << st.top();
					st.pop();
				}
				st.push( str[i] );
			}
			else if ( str[i] == '*' || str[i] == '/' )
			{
				while ( !st.empty() && (st.top() == '*' || st.top() == '/' ) )
				{
					cout << st.top();
					st.pop();
				}
				st.push( str[i] );
			}
		}
		while ( !st.empty() )
		{
			cout << st.top();
			st.pop();
		}
		cout << endl;
	}
	return 0;
}
