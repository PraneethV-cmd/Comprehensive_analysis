import java.util.*;

public class Graph {
    private int V; // Number of vertices
    private LinkedList<Edge>[] adj; // Adjacency List with weights

    // Complexity trackers
    private long comparisons = 0;
    private long swaps = 0;

    // Constructor
    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList<>();
    }

    // Method to add an edge into the graph
    void addEdge(int v, int w, int weight) {
        adj[v].add(new Edge(w, weight));
        // Counting swaps when adding edges
        swaps++;
    }

    // A recursive function to perform DFS
    void DFSUtil(int v, boolean[] visited, List<Integer> component) {
        visited[v] = true;
        component.add(v);
        // Counting comparisons while checking adjacency list
        for (Edge edge : adj[v]) {
            comparisons++;
            if (!visited[edge.target])
                DFSUtil(edge.target, visited, component);
        }
    }

    // Function that returns the transpose of the graph
    Graph getTranspose() {
        Graph g = new Graph(V);
        for (int v = 0; v < V; v++) {
            for (Edge edge : adj[v]) {
                g.addEdge(edge.target, v, edge.weight);
                // Counting swaps when adding edges
                swaps++;
            }
        }
        return g;
    }

    // The main function that finds and prints all SCCs
    List<List<Integer>> kosarajuSCC() {
        Stack<Integer> stack = new Stack<>();

        // Mark all vertices as not visited (for the first DFS)
        boolean[] visited = new boolean[V];
        Arrays.fill(visited, false);

        // Fill vertices in the stack according to their finishing times
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                fillOrder(i, visited, stack);
        }

        // Create a transposed graph
        Graph gr = getTranspose();

        // Mark all vertices as not visited (for the second DFS)
        Arrays.fill(visited, false);

        // Now process all vertices in order defined by the stack
        List<List<Integer>> sccList = new ArrayList<>();
        while (!stack.isEmpty()) {
            int v = stack.pop();
            if (!visited[v]) {
                List<Integer> component = new ArrayList<>();
                gr.DFSUtil(v, visited, component);
                sccList.add(component);
            }
        }

        return sccList;
    }

    // Fill the stack with vertices in the order of their finishing times
    void fillOrder(int v, boolean[] visited, Stack<Integer> stack) {
        visited[v] = true;
        for (Edge edge : adj[v]) {
            comparisons++;
            if (!visited[edge.target])
                fillOrder(edge.target, visited, stack);
        }
        stack.push(v);
        // Counting swaps when pushing to stack
        swaps++;
    }

    // Display time and space details
    void displayPerformance(long startTime, long endTime, long initialMemory, long finalMemory) {
        System.out.println("Time Taken: " + (endTime - startTime) + " ms");
        System.out.println("Memory Used: " + (finalMemory - initialMemory) / (1024.0 * 1024) + " MB");
    }

    // Class to store edges with weights
    static class Edge {
        int target;
        int weight;

        Edge(int target, int weight) {
            this.target = target;
            this.weight = weight;
        }
    }

    // Generate and test random graphs
    public static void generateAndTestGraphs() {
        final int RUN = 5;
        final int MAX_VERTICES = 20;
        final int MAX_EDGES = 200;
        final int MAX_WEIGHT = 200;

        Random rand = new Random();

        for (int i = 1; i <= RUN; i++) {
            int NUM = 1 + rand.nextInt(MAX_VERTICES);
            int NUMEDGE = 1 + rand.nextInt(MAX_EDGES);

            while (NUMEDGE > NUM * (NUM - 1)) // Adjust for directed graph
                NUMEDGE = 1 + rand.nextInt(MAX_EDGES);

            Graph g = new Graph(NUM);

            Set<Pair<Integer, Integer>> container = new HashSet<>();

            for (int j = 1; j <= NUMEDGE; j++) {
                int a = rand.nextInt(NUM);
                int b = rand.nextInt(NUM);
                Pair<Integer, Integer> p = new Pair<>(a, b);

                while (container.contains(p)) {
                    a = rand.nextInt(NUM);
                    b = rand.nextInt(NUM);
                    p = new Pair<>(a, b);
                }
                container.add(p);
                int weight = 1 + rand.nextInt(MAX_WEIGHT);
                g.addEdge(a, b, weight);
            }

            long startTime = System.currentTimeMillis();
            long initialMemory = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();

            List<List<Integer>> sccs = g.kosarajuSCC();

            long endTime = System.currentTimeMillis();
            long finalMemory = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();

            System.out.println("Test Case " + i + ":");
            System.out.println("Number of vertices: " + NUM);
            System.out.println("Number of edges: " + NUMEDGE);
            System.out.println("Edges and weights:");
            for (Pair<Integer, Integer> p : container) {
                System.out.println(p.getFirst() + " " + p.getSecond() + " "
                                   + (1 + rand.nextInt(MAX_WEIGHT)));
            }
            System.out.println("Strongly Connected Components:");
            for (List<Integer> component : sccs) {
                System.out.println(component);
            }

            g.displayPerformance(startTime, endTime, initialMemory, finalMemory);
            System.out.println();
        }
    }

    public static void main(String[] args) {
        generateAndTestGraphs();
    }

    // Pair class to store a pair of integers
    static class Pair<T, U> {
        private T first;
        private U second;

        public Pair(T first, U second) {
            this.first = first;
            this.second = second;
        }

        public T getFirst() { return first; }
        public U getSecond() { return second; }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair<?, ?> pair = (Pair<?, ?>) o;
            return first.equals(pair.first) && second.equals(pair.second);
        }

        @Override
        public int hashCode() {
            return Objects.hash(first, second);
        }
    }
}


