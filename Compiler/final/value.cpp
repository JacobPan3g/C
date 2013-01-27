#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
#include <vector>
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
	bool nullable;
	vector<int> firstpos;
	vector<int> lastpos;
} node[200];
vector<int> followpos[200];

bool isCat( string str, int i )
{
	if ( i == 0 )
		return false;
	else if ( ((str[i-1] >= 'a' && str[i-1] <= 'e') || (str[i-1] == '*' || str[i-1] == '?' || str[i-1] == '+')) && ((str[i] >= 'a' && str[i] <= 'b') || str[i] == '#' ) )
		return true;
	else
		return false;
}

void addItems( vector<int> &a, vector<int> b )
{
	for ( int i = 0; i < b.size(); i++ )
		a.push_back( b[i] );
}

// 计算nullaple，firstpos和lastpos
void calculate( int x )
{
	if ( node[x].c == 'e' )
	{
		node[x].nullable = true;
	}
	else if ( (node[x].c >= 'a' && node[x].c <= 'd') || node[x].c == '#' )
	{
		node[x].nullable = false;
		node[x].firstpos.push_back( node[x].id );
		node[x].lastpos.push_back( node[x].id );
	}
	else if ( node[x].c == '|' )
	{
		node[x].nullable = node[ node[x].left ].nullable || node[ node[x].right ].nullable;
		// firstpos
		addItems( node[x].firstpos, node[ node[x].left ].firstpos );
		addItems( node[x].firstpos, node[ node[x].right ].firstpos );
		// lastpos
		addItems( node[x].lastpos, node[ node[x].left ].lastpos );
		addItems( node[x].lastpos, node[ node[x].right ].lastpos );
	}
	else if ( node[x].c == '.' )
	{
		node[x].nullable = node[ node[x].left ].nullable && node[ node[x].right ].nullable;
		// firstpos
		if ( node[ node[x].left ].nullable )
		{
			addItems( node[x].firstpos, node[ node[x].left ].firstpos );
			addItems( node[x].firstpos, node[ node[x].right ].firstpos );
		}
		else
			addItems( node[x].firstpos, node[ node[x].left ].firstpos );
		// lastpos
		if ( node[ node[x].right ].nullable )
		{
			addItems( node[x].lastpos, node[ node[x].left ].lastpos );
			addItems( node[x].lastpos, node[ node[x].right ].lastpos );
		}
		else
			addItems( node[x].lastpos, node[ node[x].right ].lastpos );
	}
	else
	{
		if ( node[x].c == '*' || node[x].c == '?' )
			node[x].nullable = true;
		else if ( node[x].c == '+' )
			node[x].nullable = false;

		addItems( node[x].firstpos, node[ node[x].right ].firstpos );
		addItems( node[x].lastpos, node[ node[x].right ].lastpos );
	}
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

	calculate( idx );
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

	calculate( idx );
	nodeStack.push( idx );
	num++;
	idx++;
}

void setEachFollow( vector<int> a, vector<int> b )
{
	for ( int i = 0; i < a.size(); i++ )
		addItems( followpos[a[i]], b );
}

void calFollowpos()
{
	for ( int i = 0; i < idx; i++ )
	{
		if ( node[i].id == 0 )
		{
			if ( node[i].c == '.' )
				setEachFollow( node[ node[i].left ].lastpos, node[ node[i].right ].firstpos );
			else if ( node[i].c == '*' )
				setEachFollow( node[i].lastpos, node[i].firstpos );
		}
	}
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

		calFollowpos();
		cout << "done" << endl;
		
	}

	return 0;
}
