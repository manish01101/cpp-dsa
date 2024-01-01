#include<iostream>
#include<vector>
using namespace std;

int numberOfEnclaves(vector<vector<int>> &grid) {
        int r = grid.size();
        int c = grid[0].size();
        int arr[r][c];
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                arr[r][c]=0;
            }
        }
        
        int count = 0;
        
        for(int i=1; i<grid.size()-1; i++) {
            for(int j=1; j<grid[i].size()-1; j++) {
                bool isPossible = false;
                if(grid[i][j]==1) {
                    //left
                    if(grid[i][j-1]==1 && arr[i][j-1]==1){
                        count++;
                        isPossible = true;
                    }
                    //right
                    else if(grid[i][j+1]==1 && arr[i][j+1]){
                        count++;
                        isPossible = true;
                    }
                    //top
                    else if(grid[i-1][j]==1 && arr[i-1][j]){
                        count++;
                        isPossible = true;
                    }
                    //bottom
                    else if(grid[i+1][j]==1 && arr[i+1][j]){
                        count++;
                        isPossible = true;
                    }
                }
                if(isPossible) {
                    arr[i][j] = 1;
                }
            }
        }
        return count;
    }
int main() {
  vector<vector<int> > grid = {{0, 0, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}};
  int ans = numberOfEnclaves(grid);
  cout << ans << '\n'; 
}