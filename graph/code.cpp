#include <stdlib.h>
#include <time.h>
int main() {
	srand(time(NULL));
	int n = 6;									// 1
	int *arr = new int[n];						// 2
	for (int i = 0; i < n; i++) {				// 3
		arr[i] = rand() % 21 - 10;				// 4
	}
	int min1 = arr[0];							// 5
	int min2 = arr[1];							// 6
	if (arr[1] < arr[0]) {						// 7
		min1 = arr[1];							// 8
		min2 = arr[0];							// 9
	}
	for (int i = 2; i < n; i++) {				// 10
		if (arr[i] < min1) {					// 11
			min2 = min1;						// 12
			min1 = arr[i];						// 13
		}
		else if (arr[i] < min2)					// 14
			min2 = arr[i];						// 15
	}
}