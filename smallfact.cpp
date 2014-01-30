#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int t ;
	cin >> t;
	for (int x = 0; x < t; x++) {
		vector<int> val(1,0);
		int n ;
		cin >> n;
		val[0] = 1;
		for (int i = 2; i <= n; i++){
			int carry = 0;
			for (int k = 0; k < val.size(); k++){
				int tmp = val[k]*i + carry;
				if (tmp >= 10){
					carry = tmp/10;
					val[k] = tmp%10;
				}	
				else {
					val[k] = tmp;
					carry = 0;
				}	
			}
			while (carry > 0) {
				val.push_back(carry%10);
				carry /=10;
			}
		}
		for (int i = val.size()-1 ; i >= 0; i--)
			cout << val[i];
		cout << endl;	
	}
	return 0;	
}
