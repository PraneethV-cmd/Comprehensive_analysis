// Radix Sort in Java Programming

import java.util.Arrays;

class RadixSort {

  // Using counting sort to sort the elements in the basis of significant places
  void countingSort(int array[], int size, int place) {
    int[] output = new int[size + 1];
    int max = array[0];
    for (int i = 1; i < size; i++) {
      if (array[i] > max)
        max = array[i];
    }
    int[] count = new int[max + 1];

    for (int i = 0; i < max; ++i)
      count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < size; i++)
      count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < 10; i++)
      count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
      output[count[(array[i] / place) % 10] - 1] = array[i];
      count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
      array[i] = output[i];
  }

  // Function to get the largest element from an array
  int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++)
      if (array[i] > max)
        max = array[i];
    return max;
  }

  // Main function to implement radix sort
  void radixSort(int array[], int size) {
    // Get maximum element
    int max = getMax(array, size);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
      countingSort(array, size, place);
  }

  // Driver code
  public static void main(String args[]) {
    int[] data = { 121, 432, 564, 23, 1, 45, 788 };
    int size = data.length;
    RadixSort rs = new RadixSort();
    rs.radixSort(data, size);
    System.out.println("Sorted Array in Ascending Order: ");
    System.out.println(Arrays.toString(data));
  }
}

/*   
 *
 *
 * import java.time.Instant;
import java.time.Duration;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class RadixSort {

  // Counters for tracking the operations of the algorithm 
  static int comparisons = 0;
  static int swaps = 0;
  static int basicOperations = 0;

  // Function to get the maximum value in the array
  static int getMax(int[] A, int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
      comparisons++;
      if (A[i] > max) {
        max = A[i];
      }
      basicOperations++;
    }
    return max;
  }

  // Performs count sort
  static void countSort(int[] A, int n, int exp) {
    int[] output = new int[n];
    int[] count = new int[10];
    Arrays.fill(count, 0);

    for (int i = 0; i < n; i++) {
      count[(A[i] / exp) % 10]++;
      basicOperations++;
    }

    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
      basicOperations++;
    }

    for (int i = n - 1; i >= 0; i--) {
      output[count[(A[i] / exp) % 10] - 1] = A[i];
      count[(A[i] / exp) % 10]--;
      swaps++;
      basicOperations++;
    }

    for (int i = 0; i < n; i++) {
      A[i] = output[i];
      basicOperations++;
    }
  }

  static void radixSort(int[] A, int n) {
    int max = getMax(A, n);

    for (int exp = 1; max / exp > 0; exp *= 10) {
      countSort(A, n, exp);
    }
  }

  public static void main(String args[]) {
    Scanner scanIn = new Scanner(System.in);

    Runtime runtime = Runtime.getRuntime();
    runtime.gc();
    long memoryBefore = runtime.totalMemory() - runtime.freeMemory();
    //Takes size of the array as an input from the user
    System.out.print("Enter the size of the array: ");
    int sizeOfArr = scanIn.nextInt();

    int[] A = new int[sizeOfArr];
    Random rand = new Random();

    // Generating random elements in the array
    for (int i = 0; i < sizeOfArr; i++) {
      A[i] = rand.nextInt(sizeOfArr);
    }
    
    //Record the start time
    Instant start = Instant.now();
    //Performs the radix sort
    radixSort(A, sizeOfArr);
    //Record the end time
    Instant end = Instant.now();

    Duration duration = Duration.between(start, end);
    long timeTaken = duration.toMillis();

    //Calculate the memory used during the sort
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

 */

