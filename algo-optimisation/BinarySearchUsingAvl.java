import java.util.Scanner;

class AVLTree {

  class Node{
    int value;
    int height;
    Node left;
    Node right;
  
    public Node(int value){
      this.value = value;
      this.height = 1;
      this.left = null;
      this.right = null;
    }
  }

  int Height(Node key){
    if (key == null) {
      return 0;
    } else {
      return key.height;
    }
  }

  int Balance(Node key){
    if (key == null) {
      return 0;
    } else {
      return Height(key.right) - Height(key.left);
    }
  }

  void updateHeight(Node key){
    int left = Height(key.left);
    int right = Height(key.right);

    key.height = Math.max(left, right) + 1;
  }

  Node rotateLeft(Node x){
    Node y = x.right;
    Node z = y.left;

    y.left = x;
    x.right = z;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  Node rotateRight(Node y){
    Node x = y.left;
    Node z = x.right;

    x.right = y;
    y.left = z;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  Node balanceTree(Node root){
    updateHeight(root);

    int balance = Balance(root);

    if (balance > 1){
      if (Balance(root.right) < 0){
        root.right = rotateRight(root.right);
        return rotateLeft(root);
      } else {
        return rotateLeft(root);
      }
    }

    if (balance < -1){
      if (Balance(root.left) > 0) {
        root.left = rotateLeft(root.left);
        return rotateRight(root);
      } else {
        return rotateRight(root);
      }
    }
    return root;
  }

  Node root;

  Node insert(Node root, int key){
    if (root == null) {
      return new Node(key);
    } else if (key < root.value){
      root.left = insert(root.left, key);
    } else {
      root.right = insert(root.right, key);
    }
    return balanceTree(root);
  }

  Node BinarySearch(Node root, int key){
    if (root == null || root.value == key){
      return root;
    }
    if (root.value < key && root.right != null){
      return BinarySearch(root.right, key);
    } else {
      return BinarySearch(root.left, key);
    }
  }
}

public class BinarySearchUsingAvl {
  public static void main(String args[]){
    Scanner scan = new Scanner(System.in);
    AVLTree avl_tree = new AVLTree();

    while(true){
      int val = scan.nextInt();
      if(val == -1){
        break;
      }
      avl_tree.root = avl_tree.insert(avl_tree.root, val);
    }

    scan.close();

    AVLTree.Node node = avl_tree.BinarySearch(avl_tree.root, 12);
    if (node != null) {
      System.out.println("Found: " + node.value);
    } else {
      System.out.println("Not Found");
    }
  }
}

