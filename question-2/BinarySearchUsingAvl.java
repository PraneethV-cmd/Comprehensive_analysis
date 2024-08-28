import java.util.*;
import java.time.Instant;
import java.time.Duration;

public class BinarySearchUsingAvl {

    static int comparisons = 0;
    static int basicOperations = 0;

    static class AVLTree {

        class Node {
            int value;
            int height;
            Node left, right;

            Node(int value) {
                this.value = value;
                this.height = 1;
                this.left = this.right = null;
            }
        }

        Node root;

        int height(Node node) {
            return node == null ? 0 : node.height;
        }

        int balance(Node node) {
            return node == null ? 0 : height(node.right) - height(node.left);
        }

        void updateHeight(Node node) {
            node.height = Math.max(height(node.left), height(node.right)) + 1;
        }

        Node rotateLeft(Node x) {
            Node y = x.right;
            Node z = y.left;
            y.left = x;
            x.right = z;
            updateHeight(x);
            updateHeight(y);
            return y;
        }

        Node rotateRight(Node y) {
            Node x = y.left;
            Node z = x.right;
            x.right = y;
            y.left = z;
            updateHeight(y);
            updateHeight(x);
            return x;
        }

        Node balanceTree(Node node) {
            updateHeight(node);
            int balance = balance(node);

            if (balance > 1) {
                if (balance(node.right) < 0) {
                    node.right = rotateRight(node.right);
                }
                return rotateLeft(node);
            }

            if (balance < -1) {
                if (balance(node.left) > 0) {
                    node.left = rotateLeft(node.left);
                }
                return rotateRight(node);
            }
            return node;
        }

        Node insert(Node node, int key) {
            if (node == null) return new Node(key);
            if (key < node.value) {
                node.left = insert(node.left, key);
            } else {
                node.right = insert(node.right, key);
            }
            return balanceTree(node);
        }

        Node binarySearch(Node node, int key) {
            comparisons++;  // Increment comparison count
            if (node == null || node.value == key) return node;
            basicOperations++;  // Increment basic operation count
            if (key < node.value) return binarySearch(node.left, key);
            return binarySearch(node.right, key);
        }
    }

    public static void main(String[] args) {
        Scanner scanIn = new Scanner(System.in);
        Runtime runtime = Runtime.getRuntime();
        runtime.gc();
        long memoryBefore = runtime.totalMemory() - runtime.freeMemory();

        // Takes the number of elements to be inserted into the AVL tree
        System.out.print("Enter the number of elements to insert into the AVL tree: ");
        int numOfElements = scanIn.nextInt();

        AVLTree avlTree = new AVLTree();
        Random rand = new Random();

        // Generating random elements and inserting into the AVL tree
        for (int i = 0; i < numOfElements; i++) {
            int val = scanIn.nextInt();
            avlTree.root = avlTree.insert(avlTree.root, val);
            basicOperations++;  // Tracking basic operation
        }


        // Perform binary search in the AVL tree
        System.out.print("Enter the element to search in the AVL tree: ");
        int searchValue = scanIn.nextInt();
        
        Instant start = Instant.now();
        long startTime = System.nanoTime();

        AVLTree.Node node = avlTree.binarySearch(avlTree.root, searchValue);

        // Record the end time for the search
        Instant end = Instant.now();
        long endTime = System.nanoTime();

        // Calculate the duration of the search
        Duration duration = Duration.between(start, end);
        long timeTaken = endTime - startTime;

        // Calculate the total memory used 
        long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
        long memoryUsed = memoryAfter - memoryBefore;

        // Output the metrics
        System.out.println("Time taken for binary search: " + timeTaken/1_000_000.0 + " ms");
        System.out.println("Memory used: " + memoryUsed / 1024 + " KB");
        System.out.println("Number of comparisons: " + comparisons);
        System.out.println("Number of basic operations: " + basicOperations);

        // Output the result of the search
        if (node != null) {
            System.out.println("Found: " + node.value);
        } else {
            System.out.println("Not Found");
        }

        scanIn.close();
    }
}

