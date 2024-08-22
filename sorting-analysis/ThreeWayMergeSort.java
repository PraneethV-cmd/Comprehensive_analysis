import java.time.Instant;
import java.time.Duration;
import java.util.Random;
import java.util.Scanner;

public class ThreeWayMergeSort {

    // Counters for tracking the operations of the algorithm 
    static int comparisons = 0;
    static int swaps = 0;
    static int basicOperations = 0;

    // Main function to start the three-way merge sort process
    static void threeWayMergeSort(int[] array, int low, int high) {
        // Base case: if the array has one or zero elements, it is already sorted
        if (low >= high) {
            return;
        }

        // Calculate the first and second midpoints to divide the array into three parts
        int firstMid = low + (high - low) / 3;
        int secondMid = low + 2 * (high - low) / 3 + 1;

        // Recursively sort the three parts
        threeWayMergeSort(array, low, firstMid);
        threeWayMergeSort(array, firstMid + 1, secondMid);
        threeWayMergeSort(array, secondMid + 1, high);

        // Merge the three sorted parts in place
        mergeInPlace(array, low, firstMid, secondMid, high);
    }

    // Function to merge three sorted segments of the array in place
    static void mergeInPlace(int[] array, int low, int firstMid, int secondMid, int high) {
        int i = low;
        int j = firstMid + 1;
        int k = secondMid + 1;

        while (i <= firstMid && j <= secondMid && k <= high) {
            comparisons += 2;
            if (array[i] <= array[j]) {
                if (array[i] <= array[k]) {
                    i++; // `array[i]` is in the correct place
                } else {
                    rotateRight(array, i, k);
                    swaps++;
                    i++;
                    firstMid++;
                    j++;
                    k++;
                }
            } else {
                if (array[j] <= array[k]) {
                    rotateRight(array, i, j);
                    swaps++;
                    i++;
                    firstMid++;
                    j++;
                } else {
                    rotateRight(array, i, k);
                    swaps++;
                    i++;
                    firstMid++;
                    j++;
                    k++;
                }
            }
            basicOperations++;
        }

        // Merge any remaining elements between `i` and `firstMid`, `j` and `secondMid`, and `k` and `high`
        while (i <= firstMid && j <= secondMid) {
            comparisons++;
            if (array[i] <= array[j]) {
                i++;
            } else {
                rotateRight(array, i, j);
                swaps++;
                i++;
                firstMid++;
                j++;
            }
            basicOperations++;
        }

        while (j <= secondMid && k <= high) {
            comparisons++;
            if (array[j] <= array[k]) {
                j++;
            } else {
                rotateRight(array, j, k);
                swaps++;
                j++;
                secondMid++;
                k++;
            }
            basicOperations++;
        }

        while (i <= firstMid && k <= high) {
            comparisons++;
            if (array[i] <= array[k]) {
                i++;
            } else {
                rotateRight(array, i, k);
                swaps++;
                i++;
                firstMid++;
                k++;
            }
            basicOperations++;
        }
    }

    // Helper function to rotate elements between indices `start` and `end` in place
    static void rotateRight(int[] array, int start, int end) {
        int temp = array[end];
        for (int i = end; i > start; i--) {
            array[i] = array[i - 1];
        }
        array[start] = temp;
        swaps++;
        basicOperations++;
    }

    public static void main(String[] args) {
        Scanner scanIn = new Scanner(System.in);

        Runtime runtime = Runtime.getRuntime();
        runtime.gc();
        long memoryBefore = runtime.totalMemory() - runtime.freeMemory();

        //Takes size of the array as an input from the user
        System.out.print("Enter the size of the array: ");
        int sizeOfArr = scanIn.nextInt();

        int[] array = new int[sizeOfArr];
        Random rand = new Random();

        // Generating random elements in the array
        for (int i = 0; i < sizeOfArr; i++) {
            array[i] = rand.nextInt(sizeOfArr);
        }

        //Record the start time
        Instant start = Instant.now();
        //Performs threeWayMergeSort
        threeWayMergeSort(array, 0, array.length - 1);
        Instant end = Instant.now();

        Duration duration = Duration.between(start, end);
        long timeTaken = duration.toMillis();

        //Calculate the total memory used during the sort
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;

        System.out.println("Time complexity: " + timeTaken + " ms");
        System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
        System.out.println("Number of comparisons: " + comparisons);
        System.out.println("Number of swaps: " + swaps);
        System.out.println("Number of basic operations: " + basicOperations);

        // Printing sorted array
        System.out.println("Sorted array:");
        for (int num : array) {
            System.out.print(num + " ");
        }

        scanIn.close();
    }
}
