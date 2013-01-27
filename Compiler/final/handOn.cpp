#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;

struct Node
{
	int id;
	char c;
	int left;
	int right;
	bool nullable;
	vector<int> firstpos;
	vector<int> lastpos;
};


class RegularToDFA
{
public:
	struct Node node[200];
	stack<int> nodeStack;
	stack<char> opStack;
	int idx;
	int num;
	vector<int> followpos[200];
	vector<int> Dstates[80];
	int Dtran[80][10];
	bool mapping[10][200];
	
	int root;
	int numOfStates;
	int accept;
	
	bool isCat( string str, int i )
	{
		if ( i == 0 )
			return false;
		else if ( ((str[i-1] >= 'a' && str[i-1] <= 'e') || (str[i-1] == '*' || str[i-1] == '?' || str[i-1] == '+' || str[i-1] == ')')) && ((str[i] >= 'a' && str[i] <= 'e') || str[i] == '(' || str[i] == '#' ) )
			return true;
		else
			return false;
	}

	void addItems( vector<int> &a, vector<int> b )
	{
		bool exist[80] = {false};
		for ( int i = 0; i < a.size(); i++ )
			exist[a[i]] = true;
		for ( int i = 0; i < b.size(); i++ )
		{
			if ( !exist[b[i]] )
				a.push_back( b[i] );
		}
		sort( a.begin(), a.end() );
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

	void makeMapping( char c, int num )
	{
		if ( c == '#' )
			mapping[5][num] = true;
		else
			mapping[c-'a'][num] = true;
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

		makeMapping( c, num );
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

	// 用来判断某个状态是否已存在
	// 如果存在了，把位置赋值给whichOne
	bool isExist( vector<int> tmpV, int tag, int &whichOne )
	{
		for ( int i = 0; i < tag; i++ )
		{
			if ( tmpV.size() != Dstates[i].size() )
				continue;
			else
			{		
				bool isSame = true;
				vector<int> v = Dstates[i];
				for ( int j = 0; j < v.size(); j++ )
				{
					if ( v[j] != tmpV[j] )
						isSame = false;
				}
				if ( isSame )
				{
					whichOne = i;
					return true;
				}
			}
		}
		return false;
	}

	int transform( int root )
	{
		queue<int> q;
		int tag = 0;
		bool isAdd = false;

		addItems( Dstates[tag], node[root].firstpos );
		tag++;
		q.push( 0 );
		while ( !q.empty() )
		{
			int front = q.front();
			q.pop();
			//对每一个字符
			for ( int i = 0; i < 6; i++ )
			{
				isAdd = false;
				vector<int> tmpV;
				vector<int> firstpos = Dstates[front];
				for ( int j = 0; j < firstpos.size(); j++ )
				{
					// 如果是表示同一个字符，则并上
					if ( mapping[i][ firstpos[j] ] )
					{
						addItems( tmpV, followpos[ firstpos[j] ] );
						isAdd = true;
						// 用来避免加入多一个状态#
						if ( i == 5 && tmpV.size() == 0 )
							isAdd = false;
					}
				}
				if ( isAdd )
				{
					int whichOne = tag;		//用来写转换表
					if( !isExist( tmpV, tag, whichOne ) )
					{
						addItems( Dstates[tag], tmpV );
						q.push( tag );
						tag++;
					}
					Dtran[front][i] = whichOne;
				}
			}
		}
		return tag;
	}
	
	int buildTree( string str )
	{
		idx = 0;
		num = 1;	// 用来设置叶子节点的id

		str = "(" + str + ")#";
		for ( int i = 0; i < str.size(); i++ )
		{
			char c = str[i];
			if ( (c >= 'a' && c <= 'e') || c == '(' || c == '#' )
			{
				// 判断是否该输入一个连接符
				// .具有最低的优先级
				if ( isCat( str, i ) )
				{
					while ( !opStack.empty() && ( opStack.top() != '(' && opStack.top() != '|' ) )
						generate();
					opStack.push( '.' );
				}

				if ( c == '(' )
					opStack.push( c );
				else
					generate( c );
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
				while ( !opStack.empty() &&  opStack.top() != '(' )
					generate();
				opStack.push( c );
			}
			else if ( c == '*' || c == '?' || c == '+' )
			{
				while ( !opStack.empty() && ( opStack.top() == '*' || opStack.top() == '?' || opStack.top() == '+' ) )
					generate();
				opStack.push( c );
			}
		}
		// 生成根节点
		generate();
		nodeStack.pop();
		int root = idx - 1;
		//cout << root << endl;

		calFollowpos();
		//cout << "done" << endl;
		
		return root;
	}
	
	void init()
	{
		for ( int i = 0; i < 10; i++ )
			for ( int j = 0; j < 200; j++ )
				mapping[i][j] = false;
		for ( int i = 0; i < 80; i++ )
			for ( int j = 0; j < 10; j++ )
				Dtran[i][j] = -1;	
	}
	
	RegularToDFA( string str )
	{
		init();
		root = buildTree( str );
		numOfStates = transform( root );
		//cout << numOfStates << endl;
	}
	
	int getNumOfStates()
	{
		return numOfStates;
	}
	
	void getDstates()
	{ 
		for ( int i = 0; i < numOfStates; i++ )
		{
			for ( int j = 0; j < Dstates[i].size(); j++ )
				cout << Dstates[i][j] << " ";
			cout << endl;
		}
	}
	
	string getDtran()
	{
		stringstream ss;
		for ( int i = 0; i < numOfStates; i++ )
		{
			for ( int j = 0; j < 6; j++ )
				ss << Dtran[i][j];
			ss << "|";
				//cout << Dtran[i][j] << " ";
			//cout << endl;
		}
		string res;
		ss >> res;
		return res;
	}
};

int main()
{
//freopen( "input.txt", "r", stdin );

	string str1;
	string str2;
	while ( cin >> str1 >> str2, str1 != "#" )
	{
		RegularToDFA dfa1( str1 );
		RegularToDFA dfa2( str2 );

		if ( dfa1.getNumOfStates() != dfa2.getNumOfStates() )
			cout << "NO" << endl;
		else if ( dfa1.getDtran() == dfa2.getDtran() )
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
