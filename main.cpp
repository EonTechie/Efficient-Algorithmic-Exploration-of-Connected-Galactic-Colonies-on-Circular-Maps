/**
 * Developed by EonTechie
 * Repository: https://github.com/EonTechie
 */

#include <iostream>         
#include <vector>
#include <fstream>
#include <sstream>       
#include <stack>
#include <queue>
#include <chrono>       // For time measurement

/* INCLUDE ANY OTHER NECESSARY LIBRARIES HERE */
/* START YOUR CODE HERE */
#include <algorithm>
/* END YOUR CODE HERE */

using namespace std;
using namespace std::chrono;

/* USE HERE IF YOU NEED TO DEFINE EXTRA FUNCTIONS */
/* START YOUR CODE HERE */
typedef pair<int, int>  pii;

bool    customComparator(const pii  &a, const pii   &b)
{
    if (a.first != b.first)
        return a.first > b.first;
    return a.second < b.second;
}
void    fix_row_col(vector<vector<int>> &map, int &row, int &col)
{
    int rows = static_cast<int>(map.size());
    int cols = static_cast<int>(map[0].size());

    row = (row + rows) % rows;
    col = (col + cols) % cols;
}
/* END YOUR CODE HERE */

/**
 * Perform Depth-First Search (DFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the DFS traversal.
 * @param col The starting column index for the DFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the DFS traversal.
 */
int dfs(vector<vector<int>>& map, int row, int col, int resource){

    /* START YOUR CODE HERE */
   stack<pii> stk;
    fix_row_col(map, row, col); // Adjust row and col to ensure they are within map bounds

    if (map[row][col] != resource || map[row][col] < 0) {
        return 0; // Return immediately if the starting cell is not of the desired resource or already visited
    }

    // Initialize size of the colony and push the starting cell onto the stack
    int size = 0;
    stk.push({row, col});

    while (!stk.empty()) {
        pii current = stk.top();
        stk.pop();

        int currentRow = current.first;
        int currentCol = current.second;
        fix_row_col(map, currentRow, currentCol);

        // Check if the current cell is already visited or not of the desired resource
        if (map[currentRow][currentCol] != resource ) continue;

        // Mark the cell as visited by setting it to a negative value
        map[currentRow][currentCol] = -1*map[currentRow][currentCol];
        size++; // Increment the size of the colony

        // Push the four neighboring cells onto the stack
        vector<pii> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& dir : directions) {
            int newRow = currentRow + dir.first;
            int newCol = currentCol + dir.second;
            fix_row_col(map, newRow, newCol);
            // Check boundaries and if the cell is already visited in fix_row_col function
            if (map[newRow][newCol] == resource) {
                stk.push({newRow, newCol});
            }
        }
    }
    return size; // Return the total size of the colony

    /* END YOUR CODE HERE */
}

/**
 * Perform Breadth-First Search (BFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the BFS traversal.
 * @param col The starting column index for the BFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the BFS traversal.
 */
int bfs(vector<vector<int>>& map, int row, int col, int resource) {
  /* START YOUR CODE HERE */

    queue<pii> q; // Kullanılacak kuyruk veri yapısı
    fix_row_col(map, row, col); // Harita sınırlarını düzelt

    // Eğer başlangıç noktası aranan kaynak değilse veya ziyaret edilmişse 0 dön
    if (map[row][col] != resource || map[row][col] < 0)
        return 0;

    // Başlangıç noktasını ziyaret edilmiş olarak işaretle ve kuyruğa ekle
    map[row][col] = -1 * map[row][col];
    q.push({row, col});
    int size = 1; // Koloni boyutunu başlat

    // BFS döngüsü
    while (!q.empty()) {
        pii current = q.front(); // Kuyruktan bir düğüm al
        q.pop();

        // Dört ana yönü tanımla
        vector<pii> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto dir : directions) {
            int newRow = current.first + dir.first;
            int newCol = current.second + dir.second;
            fix_row_col(map, newRow, newCol); // Harita sınırlarını tekrar düzelt

            // Eğer komşu hücre kaynak tipine uygunsa ve daha önce ziyaret edilmemişse
            if (map[newRow][newCol] == resource && map[newRow][newCol] > 0) {
                map[newRow][newCol] = -1 * map[newRow][newCol]; // Komşuyu ziyaret edilmiş olarak işaretle
                q.push({newRow, newCol}); // Kuyruğa ekle
                size++; // Koloni boyutunu arttır
            }
        }
    }

    return size; // Toplam koloni boyutunu dön

      /* END YOUR CODE HERE */
}



/**
 * Finds the top-k largest colonies in a given map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param useDFS A boolean flag indicating whether to use Depth-First Search (DFS) or Breadth-First Search (BFS) algorithm.
 * @param k The number of top colonies to find.
 * @return A vector of pairs representing the size and resource type of the top-k largest colonies.
 */
vector<pair<int, int>> top_k_largest_colonies(vector<vector<int>>& map, bool useDFS, unsigned int k)
{

    auto start = high_resolution_clock::now();      // Start measuring time
    
    /* START YOUR CODE HERE */
    vector<pair<int, int>>  colonySizes;

    if (!map.size())
        return (vector<pair<int, int> >());
    for (size_t i = 0, r = map.size(); i < r; i++)
    {
        for (size_t j = 0, c = map[0].size(); j < c; j++)
        {
            int resource = map[i][j];
            if (resource < 0)
                continue ;
            pair<int, int>     p
            {
                useDFS ? dfs(map, i, j, resource) : bfs(map, i, j, resource),
                resource
            };
            colonySizes.push_back(p);
        }
    }
    /* END YOUR CODE HERE */

    auto stop = high_resolution_clock::now();                       // Stop measuring time
    auto duration = duration_cast<nanoseconds>(stop - start);       // Calculate the duration
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

    /* START YOUR CODE HERE */
    sort(colonySizes.begin(), colonySizes.end(), customComparator);
    size_t  colony = min(static_cast<size_t>(k), colonySizes.size());
    vector<pair<int, int>>  top_k(colonySizes.begin(), colonySizes.begin() + colony);
    return (top_k);
    /* END YOUR CODE HERE */
}

// Main function
int main(int argc, char* argv[]){

    // Check the command line arguments
    if (argc != 4) {

        // It should be: <1 or 0> <k> <filename.txt>
        cerr << "Usage: " << argv[0] << " <1 or 0> <k> <filename.txt>" << endl;
        return 1;
    }

    // Get the arguments
    bool useDFS = (atoi(argv[1]) == 1);
    int k = atoi(argv[2]);

    // Read the map from the text file
    string filename = argv[3];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<vector<int>> sector_map;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;
        while (iss >> num) {
            row.push_back(num);
        }
        sector_map.push_back(row);
    }
    file.close();   

    // Find the largest colony
    vector<pair<int, int>> result = top_k_largest_colonies(sector_map, useDFS, k);

    // Print the result
    cout << "Algorithm: " << (useDFS ? "DFS" : "BFS") << endl;
    cout << "Map: " << filename << endl;

    // If no colonies are found
    if (result.empty()) {
        cout << "No colonies found." << endl;
        return 0;
    }

    // Print the top-k colonies
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "Colony " << i + 1 << ": Size = " << result[i].first << ", Resource Type = " << result[i].second << endl;
    }

    return 0;
}
