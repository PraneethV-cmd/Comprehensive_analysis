public class ThreeWayMergeSort {
  
  static void mergeSort(int[] A, int low, int high){
    int mid1 = (low + (high - low)) / 3 ;
    int mid2 = (low + 2*(high-low)) / 3 + 1;

    mergeSort(A, low, mid1);
    mergeSort(A, mid1, mid2);
    mergeSort(A, mid2, high);

    merging(A, low, mid1, mid2, high);
  }

  static void merging(int[] A, int low, int mid1, int mid2, int high){
    int i = 0 ;
    int j = mid1 + 1;
    int k = mid2 + 1;

    while(i < mid1 && j < mid2 && k < high){
      if(A[i] < A[j]){
        i += 1;
        if(A[j] < A[k]){
          j += 1;
        }else{
          int temp = A[k];
          int idx = k;
          while(idx != j){
            A[idx] = A[idx-1];
            idx -= 1;
          }
          A[j] = temp;
          i += 1;
          j += 1;
          k += 1;
        }
      }else{
        
      }
    }
  }
  public static void main(String args[]){
  
  }
}
