"""
Playing with functions, list, dictionaries, and random numbers.
Author: Chris Wong
"""
from random import randint

def new_random() -> int:
    """returns a random number and add a value to times_run each time new_random is run"""
    global times_run
    times_run += 1
    num = randint(1, up_num)
    return num

def check_repeat() -> (int, int):
    """ returns which num shown the most in a row and how many times it showed once all nums have shown at least once"""
    rep_num = 0
    num_times_rep = 0
    for i in range(0, len(lst_of_nums) - 1):
        count = 1
        while lst_of_nums[i] == lst_of_nums[i + count]:
            count += 1
            if num_times_rep < count:
                num_times_rep = count
                rep_num = lst_of_nums[i]
    return rep_num, num_times_rep

def check_nums() -> bool:
    """ checks to see if all numbers in the range inputted are there or not"""
    for e in range(1, up_num + 1):
        if e not in lst_of_nums:
            return False
    return True

lst_of_nums = []
times_run = 0
print("Creating all integers from 1 to n (inclusive) randomly.")
up_bound = input("Please enter the upper boundary, n = ")
if up_bound.isnumeric():
    up_num = int(up_bound)
else:
    print("That input is not numeric. Please enter a numeric input next time.")
    quit()
while True:
    number = new_random()
    if number not in lst_of_nums:
        lst_of_nums.append(number)
    else:
        lst_of_nums.append(number)
        new_random()
    if check_nums():
        break
repeated_num, repeats = check_repeat()
print(f"Creating a random sequence of all integers 1 .. {up_num} required {times_run} randint(1,{up_num}) calls")
print(f"The integer that was created last was {lst_of_nums[-1]}.")
if repeated_num != 0 and repeats != 0:
    print(f"The integer that was created the most times in a row, {repeats} times, was {repeated_num}.")
else:
    print("No like numbers appeared in a row.")
