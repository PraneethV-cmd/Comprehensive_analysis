import java.io.*;
import java.util.*;

public class test {
    public static void main(String[] args) {
        Random rand = new Random();
        Scanner scanIt = new Scanner(System.in);

        System.out.print("Enter the number of random values to generate: ");
        int n = scanIt.nextInt(); // Corrected to `nextInt()`

        for (int i = 0; i < n; i++) {
            // Generate a random integer from 1 to n (inclusive)
            int randomValue = rand.nextInt(n) + 1;
            System.out.println(randomValue);
        }

        scanIt.close();
    }
}

