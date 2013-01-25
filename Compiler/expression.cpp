#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

stack<char> opStack;
stack<int> numStack;

int toNumber( string str )
{
	int res;
	stringstream ss( str );
	ss >> res;
	return res;
}

int calculator( int a, int b, char op )
{
	int res;
	if ( op == '+' )
		res = a + b;
	else if ( op == '-' )
		res = a - b;
	else if ( op == '*' )
		res = a * b;
	else if ( op == '/' )
		res = a / b;
	return res;
}

// 这里要注意两个数的顺序，numStack栈顶是第二个操作数
void calculate()
{	
	int b = numStack.top();
	numStack.pop();
	int a = numStack.top();
	numStack.pop();
	numStack.push( calculator( a, b, opStack.top() ) );
	opStack.pop();
}

int main()
{
freopen( "input.txt", "r", stdin );

	string str;
	while ( cin >> str, str != "#" )
	{
		while ( str.size() > 0 )
		{
			char c = str[0];
			if ( c >= '0' && c <= '9' )
			{
				numStack.push( toNumber( str ) );
				while ( str[0] >= '0' && c <= '9' )
					str.erase( 0, 1 );
			}
			else
			{
				str.erase( 0, 1 );
				if ( c == '(' )
					opStack.push( c );
				else if ( c == ')' )
				{
					while ( opStack.top() != '(' )
						calculate();
					opStack.pop();
				}
				else if ( c == '+' || c == '-' )
				{
					if ( !opStack.empty() && opStack.top() != '(' )
						calculate();
					opStack.push( c );
				}
				else if ( c == '*' || c == '/' )
				{
					if ( !opStack.empty() && ( opStack.top() == '*' || opStack.top() == '/' ) )
						calculate();
					opStack.push( c );
				}
			}
		}
		// 最后，把剩下的运算全部算完
		// 等所有运算算完后，opStack变空，numStack只剩下最终结果一个数
		while ( !opStack.empty() )
			calculate();
		cout << numStack.top() << endl;
		numStack.pop();
	}
	
	return 0;
}
