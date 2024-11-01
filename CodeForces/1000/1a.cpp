#include <iostream>
using namespace std;

int main() {
long long n,m,a;
cin >> n >> m >> a;
long long width = (n+a-1)/a;
long long hieght = (m+a-1)/a;
cout << width * hieght << endl;
return 0;
}