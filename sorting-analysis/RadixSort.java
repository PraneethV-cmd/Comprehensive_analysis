import java.time.Instant;
import java.time.Duration;
import java.util.Arrays;

public class RadixSort {

  static int comparisons = 0;
  static int swaps = 0;
  static int basicOperations = 0;

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

  static void countSort(int[] A, int n, int exp) {
    int output[] = new int[n]; 
    int count[] = new int[10];
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
    int[] A = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = A.length;
    Instant start = Instant.now();
    Runtime runtime = Runtime.getRuntime();
    long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();
    radixSort(A, n);
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
