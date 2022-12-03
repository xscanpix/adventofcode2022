bags = open("input", "r").readlines()

total_sum = 0

for bag in bags:
    bag = bag.rstrip()
    length = len(bag)

    compartment_1 = set(bag[0:int(length/2)])
    compartment_2 = set(bag[int(length/2):])

    common_types = compartment_1.intersection(compartment_2)

    for type in common_types:
        if type.isupper():
            total_sum += ord(type) - (ord('A') - 27)
        else:
            total_sum += ord(type) - (ord('a') - 1)

print("Day 3 Answer 1: {}".format(total_sum))
