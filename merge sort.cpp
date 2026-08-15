#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct Order {
    int orderId;
    long long timestamp;

    void display() const {
        cout << "Order ID: " << orderId
             << " | Timestamp: " << timestamp << endl;
    }
};

// Merge two sorted parts
void merge(vector<Order>& orders, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> L(n1);
    vector<Order> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = orders[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge in ascending timestamp order
    while (i < n1 && j < n2) {

        if (L[i].timestamp <= R[j].timestamp) {
            orders[k] = L[i];
            i++;
        }
        else {
            orders[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        orders[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        orders[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(vector<Order>& orders, int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(orders, left, mid);
        mergeSort(orders, mid + 1, right);

        merge(orders, left, mid, right);
    }
}

// Generate large dataset
vector<Order> generateOrders(int n) {

    vector<Order> orders;
    orders.reserve(n);

    for (int i = 0; i < n; i++) {

        Order order;

        order.orderId = i + 1;

        // Generate random timestamp
        order.timestamp =
            1609459200LL + rand() % 126144000;

        orders.push_back(order);
    }

    return orders;
}

int main() {

    srand(time(0));

    // Dataset of 1 million orders
    int n = 1000000;

    vector<Order> orders = generateOrders(n);

    cout << "Total orders: " << n << endl;

    // Start timer
    auto start = high_resolution_clock::now();

    // Apply Merge Sort
    mergeSort(orders, 0, n - 1);

    // End timer
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    // Display first 10 sorted orders
    cout << "\nFirst 10 orders after sorting:\n";

    for (int i = 0; i < 10; i++) {
        orders[i].display();
    }

    cout << "\nMerge Sort completed successfully.";
    cout << "\nTime taken: " << elapsed.count()
         << " seconds" << endl;

    return 0;
}
