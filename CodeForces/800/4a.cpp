#include <iostream>
using namespace std;

int main() {
int num;
cin >> num;
cout << ((num % 2==0 && num!=2) ? "YES" : "NO");
return 0;
}