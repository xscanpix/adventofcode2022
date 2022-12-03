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

# Part 2
total_sum = 0

def list_chunk(lst, chunk_size):
    for i in range(0, len(lst), chunk_size):
        yield lst[i:i + chunk_size]

for group in list_chunk(bags, 3):
    types_1 = set(group[0].rstrip())
    types_2 = set(group[1].rstrip())
    types_3 = set(group[2].rstrip())

    common = list(types_1.intersection(types_2.intersection(types_3)))[0]

    if common.isupper():
        total_sum += ord(common) - (ord('A') - 27)
    else:
        total_sum += ord(common) - (ord('a') - 1)

print("Day 3 Answer 2: {}".format(total_sum))
