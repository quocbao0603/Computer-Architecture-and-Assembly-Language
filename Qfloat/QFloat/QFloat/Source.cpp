#include "QFloat.h"
#include "utils.h"

using namespace std;
int main() {
	
	//test chuyển từ thập phan sang nhị phân
	string t = "NaN";
	QFloat a(t);
	Print_QFloat(a);
	system("pause");
}