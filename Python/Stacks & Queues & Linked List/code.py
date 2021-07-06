


"""Bi Nguyen, 2 Feb 2019, ECS 32B Section: A05

Assuming the Node class and the Node2 class will be imported in order to run the code"""

#Question 1
class QueueX:
    """Implement the Queue ADT, using a list such that the rear of the queue is at the end of the list."""
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return len(self.items) == 0

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        self.items.pop(0)

    def size(self):
        return len(self.items)

#Question 2: Slice Method
class UnorderedList:

    def __init__(self):
        self.head = None

    def isEmpty(self):
        return self.head == None

    def add(self,item):
        temp = Node(item)
        temp.setNext(self.head)
        self.head = temp

    def size(self):
        current = self.head
        count = 0
        while current != None:
            count = count + 1
            current = current.getNext()
        return count

    def search(self, item):
        current = self.head
        found = False
        while current != None and not found:
            if current.getData() == item:
                found = True
            else:
                current = current.getNext()
        return found

    def remove(self,item):
        current = self.head
        previous = None
        found = False
        while not found:
            if current.getData() == item:
                found = True
            else:
                previous = current
                current = current.getNext()
        if previous == None:
            self.head = current.getNext()
        else:
            previous.setNext(current.getNext())

    def slice(self,start,stop):
        """Implement a slice method for the UnorderedList class. It should take two parameters, start and stop,
        and return a copy of the list starting at the start position and going up to but not including the stop position"""
        #count = 0
        copy = []
        curr = self.head
        while curr != None:
            copy.insert(0,curr.getData())
            curr = curr.getNext()
        newslice = UnorderedList()
        for i in range(start,stop):
            newslice.add(copy[i])
        return newslice
            # This is if the out put is the same way it was added it in
            # while count < stop - 1:
            #     current = current.getNext()
            #     count += 1
            #     if count >= start:
            #         copy.insert(0, current.getData())
            # newnode = UnorderedList()
            # for items in copy:
            #     newnode.add(items)

#Question 3 : Linked Stack
class Stack:
    """Implement a stack using linked lists."""
    def __init__(self):
        self.count = 0
        self.head = None

    def push(self, item):
        temp = Node(item)
        curr = self.head
        if self.count > 0:
            while curr != None:
                prev = curr
                curr = curr.getNext()
            prev.setNext(temp)
        else:
            self.head = temp
        self.count += 1

    def size(self):
        return self.count

    def isEmpty(self):
        return self.head == None

    def peek(self):
        return self.head.getData()

    def pop(self):
        count = 0
        curr = self.head
        while count < self.count - 1:
            prev = curr
            curr = curr.getNext()
            count += 1
        if self.count == 1:
            item = self.head.getData()
            self.head = self.head.getNext()
        elif (self.count > 1):
            item = prev.getNext().getData()
            prev.setNext(curr.getNext())
        return item


#Question 4: Linked Queue
class Queue:
    """Implement a queue using linked lists."""
    def __init__(self):
        self.head = None
        self.count = 0

    def enqueue(self,item):
        temp = Node(item)
        temp.setNext(self.head)
        self.head = temp
        self.count += 1

    def dequeue(self):
        count = 0
        curr = self.head
        while count < self.count - 1:
            prev = curr
            curr = curr.getNext()
            count += 1
        if self.count == 1:
            item = self.head.getData()
            self.head = self.head.getNext()
        else:
            item = prev.getNext().getData()
            prev.setNext(curr.getNext())
        return item

    def size(self):
        return self.count

    def isEmpty(self):
        return self.head == None

#Question 5: Linked Dequeue
class Dequeue:
    """Implement a deque using linked lists."""
    def __init__(self):
        self.head = None
        self.count = 0

    def addRear(self,item):
        temp = Node(item)
        temp.setNext(self.head)
        self.head = temp
        self.count += 1

    def addFront(self,item):
        temp = Node(item)
        if self.head == None:
            self.head = temp
        else:
            curr = self.head
            while curr != None:
                prev = curr
                curr = curr.getNext()
                if curr == None:
                    prev.setNext(temp)
        self.count += 1

    def size(self):
        return self.count

    def isEmpty(self):
        return self.head == None

    def removeFront(self):
        count = 0
        curr = self.head
        while count < self.count - 1:
            prev = curr
            curr = curr.getNext()
            count += 1
        if self.count == 1:
            item = self.head.getData()
            self.head = self.head.getNext()
        else:
            item = prev.getNext().getData()
            prev.setNext(curr.getNext())
        self.count -= 1
        return item

    def removeRear(self):
        item = self.head.getData()
        self.head = self.head.getNext()
        self.count -= 1
        return item

#Question 6: Dequeue -> Double Linked List
class Dequeue2:
    """Each node has a reference to the next node (commonly called next) as well as a reference to the preceding node (commonly called back).
    The head reference also contains two references, one to the first node in the linked list and one to the last"""

    def __init__(self):
        self.head = None
        self.count = 0

    def addFront(self, item):
        temp = Node2(item)
        if self.head == None:
            self.head = temp

        else:
            curr = self.head
            while curr != None:
                prev = curr
                curr = curr.getNext()
            prev.setNext(temp)
            prev.getNext().setPrev(prev)
        self.count += 1


    def addRear(self, item):
        temp = Node2(item)
        temp.setNext(self.head)
        if self.head !=None:
            temp.getNext().setPrev(temp)
        self.head = temp
        self.count += 1

    def removeFront(self):
        if self.count > 1:
            curr = self.head
            while curr != None:
                prev = curr
                curr = curr.getNext()
            item = prev.getData()
            prev.getPrev().setNext(curr) # -> Null
            prev.getPrev().setPrev(prev.getPrev().getPrev())
        else:
            item = self.head.getData()
            self.head = None
        self.count -=1
        return item

    def removeRear(self):
        item = self.head.getData()
        self.head = self.head.getNext()
        self.head.setPrev(None)
        self.count -= 1
        return item

    def isEmpty(self):
        return self.head == None

    def size(self):
        return self.count
