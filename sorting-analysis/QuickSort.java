import java.util.Random;
import java.util.Scanner;
import java.time.Instant;
import java.time.Duration;

public class QuickSort {

  static int comparisons = 0;
  static int swaps = 0;
  static int basicOperations = 0;

  // Partition function that returns the index of the pivot
  static int partition(int[] A, int l, int h) {
    int pivot = A[h];
    int i = l - 1; // Index of the smaller element

    for (int j = l; j < h; j++) {
      comparisons++;
      if (A[j] <= pivot) {
        i++;
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        swaps++;
      }
      basicOperations++;
    }

    int temp = A[i + 1];
    A[i + 1] = A[h];
    A[h] = temp;
    swaps++;

    basicOperations++;
    return i + 1;
  }

  // Quick Sort function
  static void quicksort(int[] A, int l, int h) {
    if (l < h) {
      int pi = partition(A, l, h);
      quicksort(A, l, pi - 1);
      quicksort(A, pi + 1, h);
      basicOperations++;
    }
  }

  public static void main(String args[]) {
    Scanner scanIn = new Scanner(System.in);

    Runtime runtime = Runtime.getRuntime();
    runtime.gc();
    long memoryBefore = runtime.totalMemory() - runtime.freeMemory();

    System.out.print("Enter the size of the array: ");
    int sizeOfArr = scanIn.nextInt();

    int[] A = new int[sizeOfArr];
    Random rand = new Random();

    // Generating random elements in the array
    for (int i = 0; i < sizeOfArr; i++) {
      A[i] = rand.nextInt(sizeOfArr);
    }

    int l = 0;
    int h = A.length - 1;

    Instant start = Instant.now();
    quicksort(A, l, h);
    Instant end = Instant.now();

    Duration duration = Duration.between(start, end);
    long timeTaken = duration.toMillis();

    long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
    long memoryUsed = memoryAfter - memoryBefore;

    System.out.println("Time complexity: " + timeTaken + " ms");
    System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
    System.out.println("Number of comparisons: " + comparisons);
    System.out.println("Number of swaps: " + swaps);
    System.out.println("Number of basic operations: " + basicOperations);

    // Printing sorted array
    System.out.println("Sorted array:");
    for (int i = 0; i < A.length; i++) {
      System.out.print(A[i] + " ");
    }

    scanIn.close();
  }
}
