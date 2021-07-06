// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"

void InsertionSort(std::vector<int>* numbers) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap
   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
          ++numCompareIS; //(*numbers)[j] < (*numbers)[j - 1])
          numMemAccessIS+= 2;

          // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         (*numbers)[j] = (*numbers)[j - 1];
         (*numbers)[j - 1] = temp;
          numMemAccessIS += 4;
         --j;
      }
      if (j > 0){// if the first condition doesn't meet, it won't access memory or compare
          numMemAccessIS+=2;//accessed at the end of each while;
          ++numCompareIS;
      }
   }
   
   return;
}