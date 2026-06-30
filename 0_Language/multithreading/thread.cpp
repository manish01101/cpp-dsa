// note: if we ceate multiple thread at the same time it doesn't guarantee which one will start first
#include<iostream>
#include<thread>

// There are 5 diff types we can create threads in c++11 using callable obj

// type 1: function pointer -> as we only write fn name in thread

// void fun(int x) {
//   while (x --> 0){
//     std::cout << x << std::endl;
//   }
// }
// int main() {
//   std::thread t(fun, 5);
//   t.join();
//   return 0;
// }



// type 2: lambda fn
// we can directly inject lambda at thread creation time

// int main() {
//   // auto fun = [](int x) {
//   //   while(x --> 0) {
//   //     std::cout << x << std::endl;
//   //   }
//   // };
//   // std::thread t(fun, 10);
//   std::thread t([](int x) {
//     while(x --> 0) {
//       std::cout << x << std::endl;
//     }
//   }, 10);

//   t.join();
//   return 0;
// }



// 3. functor (function object)
/*
Functors, also known as function objects, are objects that can be invoked like functions.
*/
// class Base {
//   public:
//   void operator ()(int x) {
//     while (x-->0){
//       std::cout << x <<std::endl;
//     }
//   }
// };
// int main() {
//   std::thread t((Base()), 10);
//   t.join();
//   return 0;
// }


// 4. Non-static member fn

// class Base {
//   public:
//   void run(int x) {
//     while (x-->0){
//       std::cout << x <<std::endl;
//     }
//   }
// };
// int main() {
//   Base b;
//   // t(address of calling fn, address of obj of calling fn, parameter)
//   std::thread t(&Base::run, &b, 10);
//   t.join(); 
//   return 0;
// }




// 5. static member fn

class Base {
  public:
  static void run(int x) { // this is static fn
    while (x-- > 0) {
      std::cout << x << std::endl;
    }
  }
};
int main() {
  std::thread t(&Base::run, 10);
  t.join();
  return 0;
}
