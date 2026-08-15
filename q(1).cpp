#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Movie {
    string title;
    float rating;
    int release_year;
    int popularity;

    void display() const {
        cout << title << " | Rating: " << rating
             << " | Year: " << release_year
             << " | Popularity: " << popularity << endl;
    }
};

// QuickSort with comparator
void quickSort(vector<Movie> &movies, int low, int high,
               bool (*compare)(const Movie &, const Movie &)) {

    if (low < high) {
        int pivotIndex = low;
        Movie pivot = movies[high];

        for (int i = low; i < high; i++) {
            if (compare(movies[i], pivot)) {
                swap(movies[i], movies[pivotIndex]);
                pivotIndex++;
            }
        }

        swap(movies[pivotIndex], movies[high]);

        quickSort(movies, low, pivotIndex - 1, compare);
        quickSort(movies, pivotIndex + 1, high, compare);
    }
}

// Comparators
bool compareByRating(const Movie &a, const Movie &b) {
    return a.rating < b.rating;
}

bool compareByYear(const Movie &a, const Movie &b) {
    return a.release_year < b.release_year;
}

bool compareByPopularity(const Movie &a, const Movie &b) {
    return a.popularity < b.popularity;
}

// Load movies from CSV
vector<Movie> loadMoviesFromCSV(const string &filename) {

    vector<Movie> movies;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return movies;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);

        string title;
        string ratingStr;
        string yearStr;
        string popStr;

        getline(ss, title, ',');
        getline(ss, ratingStr, ',');
        getline(ss, yearStr, ',');
        getline(ss, popStr, ',');

        if (!title.empty()) {

            Movie m;

            m.title = title;
            m.rating = stof(ratingStr);
            m.release_year = stoi(yearStr);
            m.popularity = stoi(popStr);

            movies.push_back(m);
        }
    }

    return movies;
}

int main() {

    string filename = "movies.csv";

    vector<Movie> movies = loadMoviesFromCSV(filename);

    if (movies.empty()) {
        cout << "No movies loaded.\n";
        return 1;
    }

    cout << "Sort movies by (rating/year/popularity): ";

    string sort_by;
    cin >> sort_by;

    bool (*compare)(const Movie &, const Movie &);

    if (sort_by == "rating") {
        compare = compareByRating;
    }
    else if (sort_by == "year") {
        compare = compareByYear;
    }
    else if (sort_by == "popularity") {
        compare = compareByPopularity;
    }
    else {
        cout << "Invalid choice. Defaulting to rating.\n";
        compare = compareByRating;
        sort_by = "rating";
    }

    // Start timer
    auto start = high_resolution_clock::now();

    // Apply Quick Sort
    quickSort(movies, 0, movies.size() - 1, compare);

    // End timer
    auto end = high_resolution_clock::now();

    duration<double> diff = end - start;

    cout << "\nTop 10 movies sorted by " << sort_by << ":\n";

    int count = min(10, static_cast<int>(movies.size()));

    for (int i = movies.size() - 1;
         i >= static_cast<int>(movies.size()) - count;
         --i) {

        movies[i].display();
    }

    cout << "\nSorted " << movies.size()
         << " movies in " << diff.count()
         << " seconds.\n";

    return 0;
}
