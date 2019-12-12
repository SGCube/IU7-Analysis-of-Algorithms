int n = 6;											// 1
int arr[] = { 4, 7, 1, 3, 0, 2};					// 2
for (int left = 0, right = n - 1; left < right) {	// 3
	for (int i = left; i < right; i++) {			// 4
		if (arr[i + 1] < arr[i]) {					// 5
			int temp = arr[i];						// 6
			arr[i] = arr[i + 1];					// 7
			arr[i + 1] = temp;						// 8
		}
	}
	right--;										// 9

	for (int i = right; i > left; i--){				// 10
		if (arr[i - 1] > arr[i]) {					// 11
			int temp = arr[i];						// 12
			arr[i] = arr[i - 1];					// 13
			arr[i - 1] = temp;						// 14
		}
	}
	left++;											// 15
}