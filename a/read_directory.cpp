// #include <iostream>
// #include <filesystem>

// namespace fs = std::filesystem;

// int main() {
//     std::string path = ".";  // Specify the directory path

//     // Iterate over the contents of the directory
//     try {
//         for (const auto& entry : fs::directory_iterator(path)) {
//             std::cout << entry.path() << std::endl;  // Print the path of each file/directory
//         }
//     } catch (fs::filesystem_error& e) {
//         std::cerr << "Error reading directory: " << e.what() << std::endl;
//     }

//     return 0;
// }

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    std::string path = "./";  // Directory path
    std::string targetFile = ".env";  // Specify the file you want to read

    try {
        // List directory content
        for (const auto& entry : fs::directory_iterator(path)) {
            std::string fileName = entry.path().filename().string();
            
            // Check if it's the specific file
            if (fileName == targetFile) {
                std::cout << "Found file: " << entry.path() << std::endl;
                
                // Open and read the file
                std::ifstream file(entry.path());
                
                if (!file.is_open()) {
                    std::cerr << "Failed to open file: " << fileName << std::endl;
                    return 1;
                }

                // Read and output file content
                std::string line;
                while (std::getline(file, line)) {
                    std::cout << line << std::endl;
                }

                // Close the file after reading
                file.close();
            }
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }

    return 0;
}
