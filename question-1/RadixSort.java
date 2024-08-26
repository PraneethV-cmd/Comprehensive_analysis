import java.util.Scanner;
import java.util.LinkedList;

public class RadixSort {

  void radixSort(int arr[], int size, int place){
    int[] binCount = new int[10];
    for(int i = 0 ;i < 10; i++){
      binCount[i] = 0;
    }

    for(int i = 0 ; i < size; i ++){
      int x = arr[i]/place;
      x = x%10;
      binCount[x] ++;
    }

    int[] output = new int[size];
    for(int i = 1 ; i < size; i ++){
      binCount[i] += binCount[i-1];
    }

    for(int i = size-1; i > 0; i--){
      int x = arr[i]/place;
      x %= 10;
      output[binCount[x] - 1] = arr[i];
      binCount[x]--;
    }

    for(int i = 0 ; i < size ; i ++){
      arr[i] = output[i];
    }
  }

  void countingSort(int arr[], int size){
    int max = arr[0];

    for(int i = 0 ; i < size; i++){
      if(arr[i] > max){
        max = arr[i];
      }
    }
    
    for(int place = 1 ; max/place > 0 ; place *= 10){
      radixSort(arr, size, place);
    }
  }

 public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter the number of elements: ");
    int n = scanner.nextInt();
    int[] arr = new int[n];

    System.out.println("Enter the elements:");
    for (int i = 0; i < n; i++) {
      arr[i] = scanner.nextInt();
    }

    RadixSort sorter = new RadixSort();
    sorter.countingSort(arr, n);

    System.out.println("Sorted array:");
    for (int num : arr) {
      System.out.print(num + " ");
    }
    System.out.println();

    scanner.close();
  }
}
