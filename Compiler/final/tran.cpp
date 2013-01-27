#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
using namespace std;

stack<int> nodeStack;
stack<char> opStack;
int idx;
int num;

struct Node
{
	int id;
	char c;
	int left;
	int right;
} node[200];

bool isCat( string str, int i )
{
	if ( i == 0 )
		return false;
	else if ( ((str[i-1] >= 'a' && str[i-1] <= 'e') || (str[i-1] == '*' || str[i-1] == '?' || str[i-1] == '+')) && ((str[i] >= 'a' && str[i] <= 'b') || str[i] == '#' ) )
		return true;
	else
		return false;
}

// 生成非叶子节点
void generate()
{	
	node[idx].id = 0;
	node[idx].c = opStack.top();
	opStack.pop();

	node[idx].right = nodeStack.top();
	nodeStack.pop();
	// 单元运算符只赋给right
	if ( node[idx].c == '|' || node[idx].c == '.' )
	{
		node[idx].left = nodeStack.top();
		nodeStack.pop();
	}

	nodeStack.push( idx );
	idx++;
}

// 生成叶子节点
void generate( char c )
{
	node[idx].id = num;
	node[idx].c = c;
	node[idx].left = -1;
	node[idx].right = -1;

	nodeStack.push( idx );
	num++;
	idx++;
}

int main()
{
freopen( "input.txt", "r", stdin );

	string str;
	while ( cin >> str, str != "#" )
	{
		str = str + "#";
		cout << str << endl;
		idx = 0;
		num = 1;	// 用来设置叶子节点的id

		for ( int i = 0; i < str.size(); i++ )
		{
			char c = str[i];
			if ( (c >= 'a' && c <= 'e') || c == '#' )
			{
				// 判断是否该输入一个连接符
				// .具有最低的优先级
				if ( isCat( str, i ) )
				{
					if ( !opStack.empty() && ( opStack.top() != '(' && opStack.top() != '|' ) )
						generate();
					opStack.push( '.' );
				}
				// 生成叶子节点
				generate( c );
			}
			else if ( c == '(' )
			{
				opStack.push( c );
			}
			else if ( c == ')' )
			{
				while ( opStack.top() != '('  )
					generate();
				opStack.pop();
			}
			else if ( c == '|' )
			{
				// 所有在栈中优先级比’|‘高的，先运算
				if ( !opStack.empty() &&  opStack.top() != '(' )
					generate();
				opStack.push( c );
			}
			else if ( c == '*' || c == '?' || c == '*' )
			{
				if ( !opStack.empty() && ( opStack.top() == '*' || c == '?' || c == '+' ) )
					generate();
				opStack.push( c );
			}
		}
		// 生成根节点
		generate();
		int root = idx - 1;
		cout << root << endl;
	}

	return 0;
}
