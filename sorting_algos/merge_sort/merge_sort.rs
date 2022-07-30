

fn merge_sort(left: usize, right: usize, array: &Vec<i32>) -> Vec<usize> {

    if left == (right - 1) {
        return vec![left];
    }

    let mid = (left + right) / 2;

    let sorted_left = merge_sort(left, mid, &array);
    let sorted_right = merge_sort(mid, right, &array);

    let mut i: usize = 0;
    let mut j: usize = 0;

    let mut merged_array: Vec<usize> = vec!(0; right - left);

    for k in 0..(right - left) {

        if i < (mid - left) && j < (right - mid) {
            if array[sorted_left[i]] < array[sorted_right[j]] {
                merged_array[k] = sorted_left[i];
                i += 1;
            } else {
                merged_array[k] = sorted_right[j];
                j += 1;
            }
        } else if i < (mid - left) {
            merged_array[k] = sorted_left[i];
            i += 1;
        } else {
            merged_array[k] = sorted_right[j];
            j += 1;
        }
    }
    return merged_array;
}



fn main() {

    let unsorted_arrays: Vec<i32> = vec![3,4,1,7,3,6,2,5]; 

    println!("unsorted array : {:?}", unsorted_arrays);

    let sorted_indexes = merge_sort(0 as usize, unsorted_arrays.len(), &unsorted_arrays);

    println!("sorted array indexes : {:?}", sorted_indexes);

}