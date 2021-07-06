
"""Bi Nguyen, 10 March 2019, ECS 32B Section: A05"""


#Question 1

#1.a T(n) = 2n - 2

#1.b
def pancakeSort(ls):
        length = len(ls)
        count = 0
        for j in range(0, length - 1):
            for i in range(0, length - j):
                if ls[i] > ls[count]:
                    count = i  # find max pos
            ls[:count + 1] = ls[:count + 1][::-1]  # flips the list
            ls[:length - j] = ls[:length - j][::-1]  # flips the list back
            count = 0  # repeats the process
        return ls


#Question 2
def bubblesort(ls):
    for i in range(len(ls)-1, 0, -1):
        for j in range(i):
            if ls[j] > ls[j+1]:
                ls[j], ls[j+1] = ls[j+1], ls[j]
    return ls


#Question 3
def mergeSort(ls):
    left = []
    right = []

    if len(ls) <= 1:
        return ls

    elif len(ls) > 1:
        mid = len(ls) // 2

        for i in range(0, mid):
            left.append(ls[i])


        for j in range(mid, len(ls)):
            right.append(ls[j])

        mergeSort(left)
        mergeSort(right)

        i = 0
        j = 0
        k = 0

        # Compare elements from  both list
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                ls[k] = left[i]
                i += 1
            else:
                ls[k] = right[j]
                j += 1
            k += 1

        # append the rest sorted elements from the left
        while i < len(left):
            ls[k] = left[i]
            i += 1
            k += 1

        # append the rest sorted elements from the right
        while j < len(right):
            ls[k] = right[j]
            j += 1
            k += 1
    return ls
