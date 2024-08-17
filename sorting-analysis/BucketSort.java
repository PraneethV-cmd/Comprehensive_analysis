import java.util.LinkedList;

public class BucketSort {

  static void insertion_sort(LinkedList<Integer> buckets){
    int n = buckets.size();

    for(int i = 1 ; i < n ; i++){
      int key = buckets.get(i);
      int j = i - 1;

      while( j >= 0 && buckets.get(j) > key){
        buckets.set(j + 1, buckets.get(j));
        j = j - 1;
      }
      buckets.set(j + 1, key);
    }
  }

  static void bucket_sort(int[] arr){
    int arrLen = arr.length;

    if(arrLen <= 0) return;
    
    @SuppressWarnings("unchecked")
    LinkedList<Integer>[] buckets = new LinkedList[arrLen];

    int maxVal = arr[0];

    for(int i = 1 ; i < arrLen ; i++){
      if(arr[i] > maxVal){
        maxVal = arr[i];
      }
    }

    for(int i = 0 ; i < arrLen ; i++){
      buckets[i] = new LinkedList<>();
    }

    for(int i = 0 ; i < arrLen ; i++){
      int bucketIdx = (arrLen * arr[i])/(maxVal + 1);
      buckets[bucketIdx].add(arr[i]);
    }

    for(int i = 0 ; i < arrLen ; i++){
      insertion_sort(buckets[i]);
    }

    int index = 0 ;
    for(int i = 0 ; i < arrLen ; i++){
      for(int value : buckets[i]){
        arr[index] = value;
        index ++;
      }
    }
  }

  public static void main(String args[]){
    int[] arr = {19,23,44,322,122,1,34,63,57};
    System.out.println("Original array: " );
    for(int i = 0 ; i < arr.length ; i++){
      System.out.println(arr[i]);
    }

    System.out.println("After bucket sort: ");

    bucket_sort(arr);

    for(int i = 0 ; i < arr.length ; i++){
      System.out.println(arr[i]);
    }
  }

}
