import java.util.Scanner 

// TODO: add normal main fnction stuff;

public class NormalBinarySearch{

  int BinarySearch(int arr[], int key){
    int low = 0;
    int high = arr.length - 1;
    int mid = (low + high)/2;

    while(low <= high){
      if(arr[mid] == key){
        return mid;
      }else if(arr[mid] > key){
        high--;
        mid = (low + high)/2;
      }else{
        low++;
        mid = (low + high)/2;
      }
    }
    return -1;
  } 

  public static void main(String args[]){
    
  }
}
