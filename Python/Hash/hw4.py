
"""Bi Nguyen, 23 Feb 2019, ECS 32B Section: A05"""

#Question 1
def ternarySearch(ls, item):
    first = 0
    last = len(ls) - 1
    #if i do len(ls) - 1; then it won't account when i go out of bound to the right
    found = False
    while not found and first <= last:
        mid1 = first + (last-first)//3
        mid2 = last - (last-first)//3

        if ls[mid1] == item or ls[mid2] == item:
            found = True
        elif item < ls[mid1]: #move to the next largest val
            last = mid1-1
        else:#inbetween
            if item < ls[mid2]:
                last = mid2 - 1
                first = mid1 + 1
            else:#move to the next smallest value
                first = mid2 + 1
    return found

#Question 2
def ternarySearchRec(ls,item):
    first = 0
    last = len(ls) - 1
    mid1 = first + (last - first) // 3
    mid2 = last - (last - first) // 3
    if first >= last:
        return False
    elif ls[mid1] == item or ls[mid2] == item:
        return True
    elif item < ls[mid1]:
        return ternarySearchRec(ls[:mid1], item)
    else:
        if item < ls[mid2]:
            return ternarySearchRec(ls[mid1:mid2], item)
        else:
            return ternarySearchRec(ls[mid2:], item)

#Question 3
def nextMultPrime(n):
    n = n*2
    for i in range(n, n*2):
        for j in range(2,i):
            #prime only can multiple itself or 1 and since we start at 2 it
            #only reach to the "end"
            if i % j == 0:
                break
        else:
            return i

class HashTable:
    def __init__(self):
        self.size = 11
        self.slots = [None] * self.size
        self.data = [None] * self.size

    def put(self, key, data):
        hashvalue = self.hashfunction(key, len(self.slots))
        #------------------Answer To Question 3------------------------------------------
        if None not in self.data:
            copy_data = self.data
            copy_slots = self.slots
            prev_size = self.size
            self.size = nextMultPrime(self.size)
            self.slots =copy_slots + [None] * (self.size-prev_size)
            self.data = copy_data + [None] * (self.size-prev_size)
        #--------------------------------------------------------------------------------
        if self.slots[hashvalue] == None:
            self.slots[hashvalue] = key
            self.data[hashvalue] = data
        else:
            if self.slots[hashvalue] == key:
                self.data[hashvalue] = data  # replace
            else:
                nextslot = self.rehash(hashvalue, len(self.slots))
                while self.slots[nextslot] != None: #and \
                        #self.slots[nextslot] != key:
                    nextslot = self.rehash(nextslot, len(self.slots))

                if self.slots[nextslot] == None:
                    self.slots[nextslot] = key
                    self.data[nextslot] = data
                else:
                    self.data[nextslot] = data  # replace

    def hashfunction(self, key, size):
        return key % size

    def rehash(self, oldhash, size):
        return (oldhash + 1) % size

    def get(self, key):
        startslot = self.hashfunction(key, len(self.slots))
        data = None
        stop = False
        found = False
        position = startslot
        while self.slots[position] != None and \
                not found and not stop:
            if self.slots[position] == key:
                found = True
                data = self.data[position]
            else:
                position = self.rehash(position, len(self.slots))
                if position == startslot:
                    stop = True
        return data

    def __getitem__(self, key):
        return self.get(key)

    def __setitem__(self, key, data):
        self.put(key, data)

H = HashTable()
H[54] = 'cat'
H[54] = 3
H[10] = 'dog'
H[12] = 'C'
H[13] = 'D'
H[23] = 'F'
print(H.data)