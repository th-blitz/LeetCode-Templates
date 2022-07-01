


def merge_sort(array):

    def sort_recur(left, right):

        if left == right - 1:
            return [left]

        mid = (left + right) // 2

        sorted_left = sort_recur(left, mid)
        sorted_right = sort_recur(mid, right)

        i = 0 # mid - left 
        j = 0 # right - mid
        k = 0 # right - left 
        merged_array = [0] * (right - left)

        for k in range(right - left):

            if i < mid - left and j < right - mid:
                if array[sorted_left[i]] < array[sorted_right[j]]:
                    merged_array[k] = sorted_left[i]
                    i += 1
                else:
                    merged_array[k] = sorted_right[j]
                    j += 1
            elif i < mid - left:
                merged_array[k] = sorted_left[i]
                i += 1
            else:
                merged_array[k] = sorted_right[j]
                j += 1

        return merged_array

    return sort_recur(0, len(array))

import random
from tqdm import tqdm

array_len = 100
num_range = (-100, 100)
randomlist = [0] * array_len
for i in tqdm(range(array_len)):
    randomlist[i] = random.randint(num_range[0],num_range[1])
    

sorted_index = merge_sort(randomlist)
print([randomlist[i] for i in sorted_index])

