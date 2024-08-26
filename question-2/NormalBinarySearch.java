import java.util.Scanner; 
import java.time.Instant;
import java.util.Arrays;
import java.time.Duration;

public class NormalBinarySearch {

    static int comparisons = 0; 
    static int swaps = 0;
    static int basicOperations = 0;

    static int binarySearch(int arr[], int key) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high-low)  / 2;
            comparisons++;

            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
            basicOperations++;
        }
        return -1;
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

        // Generating random elements in the array
        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < sizeOfArr; i++) {
            A[i] = scanIn.nextInt();
        }

        Arrays.sort(A);

        System.out.print("Enter the element to search for: ");
        int key = scanIn.nextInt();

        // Record the start time
        Instant start = Instant.now();
        long startTime = System.nanoTime();

        int result = binarySearch(A, key);

        // Record the end time
        Instant end = Instant.now();
        long endTime = System.nanoTime();

        Duration duration = Duration.between(start, end);
        long timeTaken = endTime - startTime;

        // Calculate the total memory used during the search
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;

        System.out.println("Time taken: " + timeTaken / 1_000_000.0 + " ms");
        System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
        System.out.println("Number of comparisons: " + comparisons);
        System.out.println("Number of basic operations: " + basicOperations);

        if (result != -1) {
            System.out.println("Element found at index: " + result);
        } else {
            System.out.println("Element not found in the array.");
        }

        scanIn.close();
    }
}

