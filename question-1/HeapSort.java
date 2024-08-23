import java.util.Random;
import java.util.Scanner;

public class HeapSort {

  // Counters for tracking the operations of the algorithm 
  static int comparisons = 0;
  static int swaps = 0;
  static int basicOperations = 0;

  //Function that uses the heap property
  static void heapify(int[] A, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    comparisons++;
    if (left < n && A[left] > A[largest]) {
      largest = left;
    }

    comparisons++;
    if (right < n && A[right] > A[largest]) {
      largest = right;
    }

    if (largest != i) {
      int swap = A[i];
      A[i] = A[largest];
      A[largest] = swap;
      swaps++;

      // Recursively heapify the affected sub-tree
      heapify(A, n, largest);
    }
    basicOperations++;
  }

  //Function that performs the heapsort
  static void heapSort(int[] A) {
    int n = A.length;

    //Construction of max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapify(A, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
      int temp = A[0];
      A[0] = A[i];
      A[i] = temp;
      swaps++;

      heapify(A, i, 0);
    }
  }

  public static void main(String args[]) {
    Scanner scanIn = new Scanner(System.in);
    // Runtime and memory management
    Runtime runtime = Runtime.getRuntime();
    runtime.gc();
    long memoryBefore = runtime.totalMemory() - runtime.freeMemory();


    //Takes size of the array as an input from the user
    System.out.print("Enter the size of the array: ");
    int sizeOfArr = scanIn.nextInt();

    int[] A = new int[sizeOfArr];
    Random rand  = new Random();

    // Generating random elements in the array
    for(int i = 0 ; i < sizeOfArr ; i++){
      A[i] = rand.nextInt(sizeOfArr);
    }

    //Record the start time
    long startTime = System.nanoTime();
      
      //Performs heapsort
       heapSort(A);
    //Records the end time
    long endTime = System.nanoTime();

    //Calculate the duration of the sort
    long duration = endTime - startTime;

    //Calculation of the total memory used
    long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
    long memoryUsed = memoryAfter - memoryBefore;


    System.out.println(duration/1_000_000.0 + " ms is the time complexity of this code.");
    System.out.println(memoryUsed/1024 + " bytes is the memory used.");
    System.out.println(comparisons + " comparisons were made.");
    System.out.println(swaps + " swaps were performed.");
    System.out.println(basicOperations + " basic operations were executed.");

    //Display the sorted array
    for (int i = 0; i < A.length; i++) {
      System.out.print(A[i] + " ");
    }

    scanIn.close();
  }
}
