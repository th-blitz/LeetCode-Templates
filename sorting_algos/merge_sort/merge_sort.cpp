#include <vector>
#include <iostream>
using namespace std;


void stdout_array(vector<int> &array) {
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}


vector<int> merge_sort(int left, int right, vector<int> &array) {

    if (left == (right - 1)) {
        return vector<int>(1, left);
    }
    
    int mid = (left + right) / 2;

    vector<int> sorted_left = merge_sort(left, mid, array);
    vector<int> sorted_right = merge_sort(mid, right, array);

    int i = 0;
    int j = 0;

    vector<int> merged_array((right - left), 0);

    for (int k = 0; k < (right - left); k++) {

        if ((i < (mid - left)) && (j < (right - mid))) {
            if (array[sorted_left[i]] < array[sorted_right[j]]) {
                merged_array[k] = sorted_left[i];
                i++;
            } else {
                merged_array[k] = sorted_right[j];
                j++;
            }
        } else if(i < (mid - left)) {
            merged_array[k] = sorted_left[i];
            i++;
        } else {
            merged_array[k] = sorted_right[j];
            j++;
        }
    }

    return merged_array;
}



int main() {

    vector<int> unsorted_array = {3,4,1,7,3,6,2,5};

    stdout_array(unsorted_array);

    vector<int> sorted_indexes = merge_sort(0 , unsorted_array.size(), unsorted_array);

    for (auto const& i : sorted_indexes) {
        cout << unsorted_array[i] << " ";
    }
    cout << endl;

    return 0;
}