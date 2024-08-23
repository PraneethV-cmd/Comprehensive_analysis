import java.util.LinkedList;
import java.time.Instant;
import java.time.Duration;
import java.util.Random;
import java.util.Scanner;

public class BucketSort {

    // Counters for tracking the operations of the algorithm 
    static int comparisons = 0;
    static int swaps = 0;
    static int basicOperations = 0;

    //Function that performs sort
    static void insertion_sort(LinkedList<Integer> buckets) {
        int n = buckets.size();
        
        
        for (int i = 1; i < n; i++) {
            int key = buckets.get(i);
            int j = i - 1;
            
            
            while (j >= 0 && buckets.get(j) > key) {
                comparisons++;
                buckets.set(j + 1, buckets.get(j));
                j = j - 1;
                swaps++;
                basicOperations++;
            }
            buckets.set(j + 1, key);
            basicOperations++;
        }
    }

    //Function to perform bucket sort on an array
    static void bucket_sort(int[] arr) {
        int arrLen = arr.length;

        if (arrLen <= 0) return;

        @SuppressWarnings("unchecked")
        LinkedList<Integer>[] buckets = new LinkedList[arrLen];

        int maxVal = arr[0];
        for (int i = 1; i < arrLen; i++) {
            comparisons++;
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
            basicOperations++;
        }
        
        for (int i = 0; i < arrLen; i++) {
            buckets[i] = new LinkedList<>();
        }

        
        for (int i = 0; i < arrLen; i++) {
            int bucketIdx = (arrLen * arr[i]) / (maxVal + 1);
            buckets[bucketIdx].add(arr[i]);
            basicOperations++;
        }

        
        for (int i = 0; i < arrLen; i++) {
            insertion_sort(buckets[i]);
        }

        
        int index = 0;
        for (int i = 0; i < arrLen; i++) {
            for (int value : buckets[i]) {
                arr[index] = value;
                index++;
                basicOperations++;
            }
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

        int[] arr = new int[sizeOfArr];
        Random rand = new Random();

        // Generating random elements in the array
        for (int i = 0; i < sizeOfArr; i++) {
            arr[i] = scanIn.nextInt();
        }

        //Print the original array
        System.out.println("Original array:");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        //Record the start time
        Instant start = Instant.now();
        long startTime = System.nanoTime();
        //Perform bucket sort
        bucket_sort(arr);
        //Record the end time
        Instant end = Instant.now();
        long endTime = System.nanoTime();

        //Calculate the duration of the sort
        Duration duration = Duration.between(start, end);
        long timeTaken = endTime - startTime;

        //the below snippet will calculate the total memory used by finding the free memeory and the used memeory duiring runtime 
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;

        System.out.println("Time complexity: " + timeTaken/1_000_000.0+ " ms");
        System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
        System.out.println("Number of comparisons: " + comparisons);
        System.out.println("Number of swaps: " + swaps);
        System.out.println("Number of basic operations: " + basicOperations);

        //the below snippet will display the sorted array
        System.out.println("Sorted array:");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }

        scanIn.close();
    }
}
