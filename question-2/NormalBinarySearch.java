<<<<<<< HEAD
import java.time.Instant;
import java.time.Duration;
import java.util.Random;
import java.util.Scanner;

public class NormalBinarySearch {

    // Counters for tracking the operations of the algorithm
    static int comparisons = 0;

    int BinarySearch(int arr[], int key) {
=======
import java.util.Scanner; 
import java.time.Instant;
import java.util.Arrays;
import java.time.Duration;

public class NormalBinarySearch {

    static int comparisons = 0; 
    static int swaps = 0;
    static int basicOperations = 0;

    static int binarySearch(int arr[], int key) {
>>>>>>> 2bc5684 (#)
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
<<<<<<< HEAD
            int mid = (low + high) / 2;
=======
            int mid = low + (high-low)  / 2;
>>>>>>> 2bc5684 (#)
            comparisons++;

            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
<<<<<<< HEAD
=======
            basicOperations++;
>>>>>>> 2bc5684 (#)
        }
        return -1;
    }

    public static void main(String args[]) {
<<<<<<< HEAD
        Scanner scanIn = new Scanner(System.in);
=======

        Scanner scanIn = new Scanner(System.in);

>>>>>>> 2bc5684 (#)
        Runtime runtime = Runtime.getRuntime();
        runtime.gc();
        long memoryBefore = runtime.totalMemory() - runtime.freeMemory();

<<<<<<< HEAD
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

=======
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

>>>>>>> 2bc5684 (#)
        // Record the start time
        Instant start = Instant.now();
        long startTime = System.nanoTime();

<<<<<<< HEAD
        // Perform binary search
        NormalBinarySearch search = new NormalBinarySearch();
        int result = search.BinarySearch(arr, key);
=======
        int result = binarySearch(A, key);
>>>>>>> 2bc5684 (#)

        // Record the end time
        Instant end = Instant.now();
        long endTime = System.nanoTime();

<<<<<<< HEAD
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
=======
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
>>>>>>> 2bc5684 (#)
        }

        scanIn.close();
    }
}

