#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int count_dividers(int num) {
    int count = 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            count++;
            while (num % i == 0) {
                num /= i;
            }
        }
    }
    if (num > 1) {
        count++;
    }
    return count;
}


int select_median(int arr[], int n, int k) {
    if (n <= 5) {
        sort(arr, arr + n);
        return arr[k];
    }

    int number = (n + 4) / 5;
    int medians[number];

    for (int i = 0; i < number; i++) {
        int begin = i * 5;
        int end = min(begin + 5, n);
        sort(arr + begin, arr + end);
        medians[i] = arr[begin + (end - begin) / 2];
    }

    int median_of_medians = select_median(medians, number, number / 2);

    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < median_of_medians) left_count++;
        if (arr[i] > median_of_medians) right_count++;
    }

    int left[left_count], right[right_count];
    left_count = 0;
    right_count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < median_of_medians) left[left_count++] = arr[i];
        else if (arr[i] > median_of_medians) right[right_count++] = arr[i];
    }

    if (k < left_count) {
        return select_median(left, left_count, k);
    } else if (k >= n - right_count) {
        return select_median(right, right_count, k - (n - right_count));
    } else {
        return median_of_medians;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n;

        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cin >> k;

        int stable_count = 0;
        int stable[n];

        for (int i = 0; i < n; i++) {
            if (count_dividers(arr[i]) % 2 == 0) {
                stable[stable_count++] = arr[i];
            }
        }

        if (stable_count <= k) {
            cout << "BRAK DANYCH\n";
        } else {
            cout << select_median(stable, stable_count, k) << "\n";
        }
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.