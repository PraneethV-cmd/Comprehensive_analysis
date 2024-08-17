public class ThreeWayMergeSort {

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
            if (array[i] <= array[j]) {
                if (array[i] <= array[k]) {
                    i++; // `array[i]` is in the correct place
                } else {
                    // `array[k]` is smaller, needs to be placed before `array[i]`
                    rotateRight(array, i, k);
                    i++;
                    firstMid++;
                    j++;
                    k++;
                }
            } else {
                if (array[j] <= array[k]) {
                    // `array[j]` is smaller, needs to be placed before `array[i]`
                    rotateRight(array, i, j);
                    i++;
                    firstMid++;
                    j++;
                } else {
                    // `array[k]` is smaller, needs to be placed before `array[i]`
                    rotateRight(array, i, k);
                    i++;
                    firstMid++;
                    j++;
                    k++;
                }
            }
        }

        // Merge any remaining elements between `i` and `firstMid`, `j` and `secondMid`, and `k` and `high`
        while (i <= firstMid && j <= secondMid) {
            if (array[i] <= array[j]) {
                i++;
            } else {
                rotateRight(array, i, j);
                i++;
                firstMid++;
                j++;
            }
        }

        while (j <= secondMid && k <= high) {
            if (array[j] <= array[k]) {
                j++;
            } else {
                rotateRight(array, j, k);
                j++;
                secondMid++;
                k++;
            }
        }

        while (i <= firstMid && k <= high) {
            if (array[i] <= array[k]) {
                i++;
            } else {
                rotateRight(array, i, k);
                i++;
                firstMid++;
                k++;
            }
        }
    }

    // Helper function to rotate elements between indices `start` and `end` in place
    static void rotateRight(int[] array, int start, int end) {
        int temp = array[end];
        for (int i = end; i > start; i--) {
            array[i] = array[i - 1];
        }
        array[start] = temp;
    }

    public static void main(String[] args) {
        int[] array = {12, 4, 78, 90, 45, 23, 56, 89, 15, 67};
        threeWayMergeSort(array, 0, array.length - 1);

        System.out.println("Sorted array:");
        for (int num : array) {
            System.out.print(num + " ");
        }
    }
}

