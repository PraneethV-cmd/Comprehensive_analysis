import java.util.Scanner;

public class ThreeWayMergeSort{

  public static void preMergeSort(Integer[] arr){
    if(arr == null){
      return;
    }

    Integer[] tempArr = new Integer[arr.length];

    for(int i = 0 ; i < arr.length ; i++){
      tempArr[i] = arr[i];
    }

    mergeSort(tempArr, 0, arr.length, arr);

    for(int i = 0 ; i < tempArr.length; i++){
      arr[i] = tempArr[i];
    }
  }

  public static void mergeSort(Integer[] arr, int low, int high, Integer[] destArr){
    if(high - low < 2){
      return ;
    }

    int mid1 = low + ((high - low) / 3);
    int mid2 = low + 2 * ((high - low) / 3) + 1;

    mergeSort(destArr, low, mid1, arr);
    mergeSort(destArr, mid1, mid2, arr);
    mergeSort(destArr, mid2, high, arr);

    merge(destArr, low, mid1, mid2, high, arr);
  }

  public static void merge(Integer[] arr, int low, int mid1, int mid2, int high, Integer[] destArr){
    int i = low;
    int j = mid1;
    int k = mid2;
    int l = low;

    while((i < mid1) && (j < mid2) && (k < high)){
      if(arr[i] < arr[j]){
        if(arr[i] < arr[k]){
          destArr[l] = arr[i];
          l = l + 1;
          i = i + 1;
        }else{
          destArr[l] = arr[k];
          l = l + 1;
          k = k + 1;
        }
      }else{
        if(arr[j] < arr[k]){
          destArr[l] = arr[j];
          l = l + 1;
          j = j + 1;
        }else{
          destArr[l] = arr[k];
          l = l + 1;
          k = k + 1;
        }
      } 
    }

    while((i < mid1) && (j < mid2)){
      if(arr[i] < arr[j]){
        destArr[l] = arr[i];
        l = l + 1;
        i = i + 1;
      }else{
        destArr[l] = arr[j];
        l = l + 1;
        j = j + 1;
      }
    }

    while((j < mid2) && (k < high)){
      if(arr[j] < arr[k]){
        destArr[l] = arr[j];
        l = l + 1;
        j = j + 1;
      }else{
        destArr[l] = arr[k];
        l = l + 1;
        k = k + 1;
      }
    }

    while(( i < mid1 ) && ( k < high )){
      if(arr[i] < arr[k]){
        destArr[l] = arr[i];
        l = l + 1;
        i = i + 1;
      }else{
        destArr[l] = arr[k];
        l = l + 1;
        k = k + 1;
      }
    }

    while ( i < mid1){
      destArr[l] = arr[i];
      l = l + 1;
      i = i + 1;
    }

    while( j < mid2){
      destArr[l] = arr[j];
      l = l + 1;
      j = j + 1;
    }

    while(k < high){
      destArr[l] = arr[k];
      k = k + 1;
      l = l + 1;
    }
  }

  public static void main(String[] args) {
    Scanner scanIn = new Scanner(System.in);
    int size = scanIn.nextInt();

    Integer[] arr = new Integer[size];

    for(int i = 0 ; i < size ; i++){
      arr[i] = scanIn.nextInt();
    }

    preMergeSort(arr);

    for( int i = 0 ; i < arr.length ; i++){
      System.out.println(arr[i]);
    }
    scanIn.close();
  }
}
