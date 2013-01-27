#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
	stringstream ss;
	int num = -1;
	int i = 2;
	ss << -1;
	ss << "|";
	ss << 2;

	string str;
	ss >> str;

	cout << str << endl;

	return 0;
}
