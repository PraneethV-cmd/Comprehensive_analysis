import java.time.Instant;
import java.time.Duration;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class RadixSort {

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

  // Function to do counting sort of the array according to the digit represented by exp
  static void countSort(int[] A, int n, int exp) {
    int[] output = new int[n];
    int[] count = new int[10];
    Arrays.fill(count, 0);

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
      count[(A[i] / exp) % 10]++;
      basicOperations++;
    }

    // Change count[i] so that it contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
      basicOperations++;
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
      output[count[(A[i] / exp) % 10] - 1] = A[i];
      count[(A[i] / exp) % 10]--;
      swaps++;
      basicOperations++;
    }

    // Copy the output array to A[], so that A[] now contains sorted numbers according to the current digit
    for (int i = 0; i < n; i++) {
      A[i] = output[i];
      basicOperations++;
    }
  }

  // Main function to sort an array using Radix Sort
  static void radixSort(int[] A, int n) {
    int max = getMax(A, n);

    // Do counting sort for every digit. Note that exp is 10^i where i is the current digit number
    for (int exp = 1; max / exp > 0; exp *= 10) {
      countSort(A, n, exp);
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

    Instant start = Instant.now();
    radixSort(A, sizeOfArr);
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
