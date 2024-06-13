#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
using namespace std;

int main() {
  int n;
  cin >> n;
  // for(int i=0; i<n; i++) {
  //   for(int j=0; j<n-1-i; j++) {
  //     cout << " ";
  //   }
  //   for(int j=0; j<i+1; j++) {
  //     cout << "* ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;
  // for(int i=0; i<n; i++) {
  //   for(int j=0; j<i; j++) {
  //     cout << " ";
  //   }
  //   for(int j=0; j<n-i; j++) {
  //     cout << "* ";
  //   }
  //   cout << endl;
  // }

  /*: output
    * 
   * * 
  * * * 
 * * * * 
* * * * * 

* * * * * 
 * * * * 
  * * * 
   * * 
    * 
  */

  // for(int i=0; i<n; i++) {
  //   for(int j=0; j<n-i-1; j++) {
  //     cout << " ";
  //   }
  //   for(int j=0; j<2*i+1; j++) {
  //     if(j==0 || j==2*i) {
  //       cout << "*";
  //     }else {
  //       cout << " ";
  //     }
  //   }cout << endl;
  // }
  /* output:
      *
     * *
    *   *
   *     *
  *       *
  */

 
  return 0;
}