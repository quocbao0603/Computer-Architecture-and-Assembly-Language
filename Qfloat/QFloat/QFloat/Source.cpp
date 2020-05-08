#include "QFloat.h"
#include "utils.h"

using namespace std;
int main() {
	
	//test chuyển từ thập phan sang nhị phân
	//string t = "-23.40625";
	//QFloat a(t);
	//Print_QFloat(a);
	//Bin -> Dec
	string s = "10111.01101"; //s2 = t10
	QFloat b_s;
	b_s.Scan_QFloat(s, 2);
	Print_QFloat(b_s);
	system("pause");
}