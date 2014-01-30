#include <bits/stdc++.h>
using namespace std;

int merge(int a[],int left,int mid,int right){
	int i = left;
	int j = mid+1;
	
	int sum = 0;
	int b[right-left+1];
	int k = 0;
	while(i <= mid && j <= right){
		if (a[i] > a[j]){
			b[k] = a[j];
			sum += mid-i+1;
			k++; j++;	
		}
		else {
			b[k] = a[i];
			k++; i++;
		}
	}
	while(i <= mid){
		b[k] = a[i];
		k++;i++;
	}
	while (j <= right){
		b[k] = a[j];
		k++;j++;
	}

	for (int x = left; x<= right; x++)
		a[x] = b[x-left];

	return sum;
}

int mergesort(int a[],int i,int j){
	if (i >= j)
		return 0;
	int sum = 0;
	sum += mergesort(a,i,(i+j)/2);
	sum += mergesort(a,(i+j)/2+1,j);

	sum += merge(a,i,(i+j)/2,j);
	
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(0);
	int n;
	cout << "Enter the size of the array\n";
	cin >> n;
	int a[n];
	int b[n];

	int address[n],tmp[n];
	cout << "Enter the initial string\n";
	for (int i = 0; i < n; i++){
		cin >> a[i];
		tmp[a[i]] = i;
	}

	cout << "Enter the desired string\n";
	for (int i = 0; i < n; i++){
		cin >> b[i];
		address[i] = tmp[b[i]];
	}	
	cout << "inversions = " << mergesort(address,0,n-1) << endl;
	return 0;
}
