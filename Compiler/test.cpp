#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

int main()
{
	string str;
	cin >> str;
	
	char *s = (char*)str.c_str();
	
	char *p;
	p = strtok(s,",");
	while(p)
	{
		stringstream stream;
		int num;
		stream << p;
		stream >> num;
		cout << num << endl;
		p = strtok(NULL, ",");
	}
	
	return 0;
}
