#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

int knapsack(vector<Item>& items, int capacity) {
    int n = items.size();

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            // Do not take the item
            dp[i][w] = dp[i - 1][w];

            // Take the item if it fits
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    items[i - 1].value +
                    dp[i - 1][w - items[i - 1].weight]
                );
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "\nItem " << i + 1 << endl;

        cout << "Enter weight: ";
        cin >> items[i].weight;

        cout << "Enter value: ";
        cin >> items[i].value;
    }

    int capacity;

    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    int maximumValue = knapsack(items, capacity);

    cout << "\n============================\n";
    cout << "Maximum value = " << maximumValue << endl;
    cout << "============================\n";

    return 0;
}
