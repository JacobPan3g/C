#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string str;
	//cin >> str;
	//int num;
	int n = 10000;
	stringstream ss(n);
	//ss << 10000;
	ss >> str;
	cout << str << endl;

	return 0;
}
