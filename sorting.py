

def merge_sort(array):

    def sort_recur(left, right):

        if left == right - 1:
            return [left]

        mid = (left + right) // 2

        sorted_left = sort_recur(left, mid)
        sorted_right = sort_recur(mid, right)

        i = 0 # mid - left 
        j = 0 # right - mid
        k = 0 # left - right 
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

array = [1, 3, -4]

sorted_index = merge_sort(array)
print(sorted_index)
sorted_array = [array[i] for i in sorted_index]
print(sorted_array)
