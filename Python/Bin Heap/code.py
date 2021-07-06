
"""Bi Nguyen, 15 March 2019, ECS 32B Section: A05"""


#Question 1
class BinHeap:
    def __init__(self):
        self.heapList = [0]
        self.currentSize = 0

    def percUp(self,i):
        while i // 2 > 0:
          if self.heapList[i] < self.heapList[i // 2]:
             tmp = self.heapList[i // 2]
             self.heapList[i // 2] = self.heapList[i]
             self.heapList[i] = tmp
          i = i // 2

    def insert(self,k):
      self.heapList.append(k)
      self.currentSize = self.currentSize + 1
      self.percUp(self.currentSize)

    def percDown(self,i):
      while (i * 2) <= self.currentSize:
          mc = self.minChild(i)
          if self.heapList[i] > self.heapList[mc]:
              tmp = self.heapList[i]
              self.heapList[i] = self.heapList[mc]
              self.heapList[mc] = tmp
          i = mc

    def minChild(self,i):
      if i * 2 + 1 > self.currentSize:
          return i * 2
      else:
          if self.heapList[i*2] < self.heapList[i*2+1]:
              return i * 2
          else:
              return i * 2 + 1

    def delMin(self):
      retval = self.heapList[1]
      self.heapList[1] = self.heapList[self.currentSize]
      self.currentSize = self.currentSize - 1
      self.heapList.pop()
      self.percDown(1)
      return retval

    def buildHeap(self,alist):
      i = len(alist) // 2
      self.currentSize = len(alist)
      self.heapList = [0] + alist[:]
      while (i > 0):
          self.percDown(i)
          i = i - 1

    def heapsort(self):
        for i in range(self.currentSize,-1,-1):
            self.maxHeapify(self.currentSize+1, i)

        for j in range(self.currentSize, 0, -1):
            self.heapList[j], self.heapList[0] = self.heapList[0], self.heapList[j]
            self.maxHeapify(j, 0)

    def maxHeapify(self, n, ind):
        largest = ind
        left = 2 * ind + 1
        right = 2 * ind + 2

        #Switch left child
        if left < n and self.heapList[ind] < self.heapList[left]:
            largest = left

        #Switch right child
        if right < n and self.heapList[largest] < self.heapList[right]:
            largest = right

        #Change parent
        if largest != ind:
            self.heapList[ind], self.heapList[largest] = self.heapList[largest], self.heapList[ind]
            self.maxHeapify(n, largest)


#Question 2

#a. Frankfurt, Mannheim, Wurzburg, Kassel, Karisruhe, Erfurt, Numberg, Munchen, Augsburg, Stuttgart

#b. Frankfurt, Mannheim, Wurzburg, Kassel, Karisruhe, Numberg, Erfurt, Munchen, Augsburg, Stuttgart

#c. Frankfurt, Mannheim, Karlsruhe, Augsburg, Munchen, Nurnberg, Stuttgart, Wurzburg, Erfurt, Kassel

#d. Frankfurt, Mannheim, Karlsruhe, Augsburg, Wurzburg, Nurnberg, Stuttgart, Erfurt, Kassel, Munchen

