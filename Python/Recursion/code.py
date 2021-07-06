def kleinfeldt(n):
    if n == 1:
        return 1
    else:
        return 1.0/(n**2) + kleinfeldt(n - 1)

def ladder(n):
    if n <= 3:
        return n
    else:
        return ladder(n-1) + ladder(n-2)

def findLargest(ls):
    if len(ls) == 1:
        return ls[0]
    else:
        if ls[0] > findLargest(ls[1:]):
            return ls[0]
        else:
            return findLargest(ls[1:])

#Question 4
def isInRange(val, rightBound):
    """Check to see if index is out of bound"""
    return val < rightBound

def findPossibilities(ls):
    ls2 = []
    for i in range(0,len(ls), 2):
        if isInRange(i+1, len(ls)):
            if ls[i] == ls[i+1]:
                ls2.append(ls[i])
    if len(ls) % 2 == 1:
        ls2.append(ls[len(ls)-1])
    if len(ls2) < 3:
        return ls2
    else:
        return findPossibilities(ls2)

def verifyPossibilities(orig, new):
    for i in range(len(new)):
        count = 0
        for j in range(len(orig)):
            if new[i] == orig[j]:
                count += 1
                if count > len(orig)//2:
                    return new[i]
    return None

#Question 5
def findValue(val, linkedlist):
    if val == linkedlist.getData():
        return True
    elif linkedlist.getNext() == None:
        return False
    else:
        return findValue(val, linkedlist.getNext())

#Question 6
def findLastValue(linkedlist):
    if linkedlist.getNext() == None:
        return linkedlist.getData()
    else:
        return findLastValue(linkedlist.getNext())

