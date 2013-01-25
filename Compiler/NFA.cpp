#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

// 定义一个状态类型
typedef int STATUS;

int idx;
string str;
vector<STATUS> states[50][27];	//状态转换表
bool target[50];				//目标状态
// 用于每一步状态转移时避免重复的数据结构
// 在每接受一个字符c时，当前状态全部放在oldStates中
// 通过吧c传进函数moveOneAndclosure( char )函数中，来得到新的状态集合
// 该函数保证了新状态集合没有重复
// 至于moveOneClosure( char )的工作原理请看该函数的详细解释
stack<STATUS> oldStates;		//旧一步的所有状态集		
stack<STATUS> newStates;		//新一步的所有状态集
bool alreadyOn[50];				//用来检查相应的状态是否已经在newStates中，以避免重复

char nextChar()
{
	return str[idx++];
}

// 由当前状态s，向前移动c
// 注意，该函数只是返回前一步的状态，而不该状态的空闭包
vector<STATUS> move( STATUS s, char c )
{
	if ( c == 'E' )
		return states[s][0];
	else
		return states[s][c-'a'+1];
}

// 查看是否到达目标状态
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

// 解析字符串{1,2}，并转化成vector
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

// 把s添加到newStates里
// 并把s的空闭包也添加到newStates里
// 使用了递归实现
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

// 本程序的核心函数
// 该函数有两个功能：
// 1.当输入的c是'E'时，该函数会根据当前oldStates里的状态集合，找到该状态集合的空闭包
// 2.当输入的c不是'E'时，该函数会根据当前oldStates里的状态集合，使用c转移到下一状态的状态集合及其空闭包
// 最后，该函数把找到的状态集合先用newStates缓存，最后清空newStates，并把这些状态集合放在压进oldStates，为下一次转移做好准备
void moveOneStepAndClosure( char c )
{
	while ( !oldStates.empty() )
	{
		STATUS top = oldStates.top();
		oldStates.pop();
		//如果c==‘E’求的是空闭包，要包含该状态本身
		if ( c == 'E' )
			addState( top );
		//包含下一步
		//实质上，当c==E时可以完全不执行这一步
		vector<STATUS> tmpV = move( top, c );
		for ( int i = 0; i < tmpV.size(); i++ )
		{
			if ( !alreadyOn[ tmpV[i] ] )
				addState( tmpV[i] );		
		}
	}
	//把newStates的状态集合转移到oldStates中
	while ( !newStates.empty() )
	{
		STATUS top = newStates.top();
		newStates.pop();
		oldStates.push( top );
		alreadyOn[ top ] = false;
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
		
		// 读取转化表
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

			// 把开始状态压进oldStates中，开始搜索
			oldStates.push( 0 );
			moveOneStepAndClosure( 'E' );

			char c = nextChar();
			while( idx != str.length()+1 )
			{
				// 实现：S = e_closure( move( S, c ) );
				moveOneStepAndClosure( c );
				
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
