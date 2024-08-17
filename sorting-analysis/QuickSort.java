// NOTE: This following algorithm is for in-place quick sort.
// TODO: to add better comments
// TODO: to add in no of comparision operator
// TODO: to add in the leetcode space completixity calculator
// TODO: no of swaps calculator
// TODO: no of basic operations calculator
// TODO: For the size 100 or 200 or 400, create 5 testcases from 100, 200, 400, 600, 800, 1000, and then add in the values using the random generating function in the java's inbuilt library for tis.

import java.time.Instant;
import java.time.Duration;

public class QuickSort {

  static int partition(int[] A, int l, int h){
    int pivot = A[h];
    int i = l ; 
    int j= h ; 
    while(i <= j) {

      while(A[i] <= pivot){
        i += 1;
      }

      while(A[j] > pivot){
        j -= 1;
      }

      if(i < j){
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp ;
      }

    }

    int temp = A[j];
    A[j] = pivot;
    pivot = temp;
    return j;
  }

  static void quicksort(int[] A, int l , int h){
    if(l < h){
      int j = partition(A, l, h);
      quicksort(A, l, j-1);
      quicksort(A, j+1, h);
      int b[] = {1,2,3,4,5,5,6,6,7,7,8};
    }
  }

  public static void main(String args[]){
    int[] A = {7,5,4,4,7,8,8,8,1,11,3};
    int l = 0 ;
    int h = A.length - 1;

    Instant start = Instant.now();
    Runtime runtime = Runtime.getRuntime();
    long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();
    quicksort(A, l, h);
    Instant end = Instant.now();
    long usedMemoryAfter = runtime.totalMemory() - runtime.freeMemory();
    long userMemoryByFunction = usedMemoryAfter - usedMemoryBefore;


    Duration duration = Duration.between(start, end);
    long mils = duration.toMillis();
    System.out.println(mils + " is the time complexity of this code ");
    System.out.println(userMemoryByFunction + " is the memory used...");
    for(int i = 0 ; i < A.length-1 ; i++){
      System.out.println(A[i] + " ");
    }
  }
}
