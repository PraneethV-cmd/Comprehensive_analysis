import java.time.Instant;
import java.time.Duration;
import java.util.Random;
import java.util.Scanner;

public class NormalBinarySearch {

    // Counters for tracking the operations of the algorithm
    static int comparisons = 0;

    int BinarySearch(int arr[], int key) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            comparisons++;

            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }

    public static void main(String args[]) {
        Scanner scanIn = new Scanner(System.in);
        Runtime runtime = Runtime.getRuntime();
        runtime.gc();
        long memoryBefore = runtime.totalMemory() - runtime.freeMemory();

        // Takes the size of the array as input from the user
        System.out.print("Enter the size of the array: ");
        int sizeOfArr = scanIn.nextInt();

        int[] arr = new int[sizeOfArr];
        Random rand = new Random();

        // Generating random sorted elements in the array
        System.out.println("Enter the elements of the array in sorted order:");
        for (int i = 0; i < sizeOfArr; i++) {
            arr[i] = scanIn.nextInt();
        }

        // Takes the key to be searched as input from the user
        System.out.print("Enter the key to search: ");
        int key = scanIn.nextInt();

        // Print the original array
        System.out.println("Original array:");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        // Record the start time
        Instant start = Instant.now();
        long startTime = System.nanoTime();

        // Perform binary search
        NormalBinarySearch search = new NormalBinarySearch();
        int result = search.BinarySearch(arr, key);

        // Record the end time
        Instant end = Instant.now();
        long endTime = System.nanoTime();

        // Calculate the duration of the search
        Duration duration = Duration.between(start, end);
        long timeTaken = endTime - startTime;

        // Calculate memory usage
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;

        // Display results
        System.out.println("Time complexity: " + timeTaken/1_000_000.0 + " ms");
        System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
        System.out.println("Number of comparisons: " + comparisons);

        // Display search result
        if (result != -1) {
            System.out.println("Key found at index: " + result);
        } else {
            System.out.println("Key not found.");
        }

        scanIn.close();
    }
}
