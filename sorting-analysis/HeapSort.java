import java.time.Instant;
import java.time.Duration;

public class HeapSort {

  static int comparisons = 0;
  static int swaps = 0;
  static int basicOperations = 0;

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

      heapify(A, n, largest);
    }
    basicOperations++;
  }

  static void heapSort(int[] A) {
    int n = A.length;

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
    int[] A = {7, 5, 4, 4, 7, 8, 8, 8, 1, 11, 3};

    Instant start = Instant.now();
    Runtime runtime = Runtime.getRuntime();
    long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();

    heapSort(A);

    Instant end = Instant.now();
    long usedMemoryAfter = runtime.totalMemory() - runtime.freeMemory();
    long userMemoryByFunction = usedMemoryAfter - usedMemoryBefore;

    Duration duration = Duration.between(start, end);
    long mils = duration.toMillis();
    System.out.println(mils + " ms is the time complexity of this code.");
    System.out.println(userMemoryByFunction + " bytes is the memory used.");
    System.out.println(comparisons + " comparisons were made.");
    System.out.println(swaps + " swaps were performed.");
    System.out.println(basicOperations + " basic operations were executed.");

    for (int i = 0; i < A.length; i++) {
      System.out.print(A[i] + " ");
    }
  }
}
