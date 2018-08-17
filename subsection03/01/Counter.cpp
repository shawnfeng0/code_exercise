// Get the size of the specified directory
// and the number of files larger than 1M

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

long getDirSize(char const *dirPath, int *large_then1M);
unsigned long getFileSize(char const *filePath);

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cout << "Error: Please input a directory." << endl;
        exit(1);
    }
    
    // Get directory size
    int large_then1M = 0;
    long size = getDirSize(argv[1], &large_then1M);

    // Output result
    cout << "The total size of the $1 directory: " << size << "[byte]" << endl;
    cout << "The number of files larger than 1M: " << large_then1M << endl;

    return 0;
}

// Get the size of the specified directory
// and the number of files larger than 1M
long getDirSize(char const *dirPath, int *large_then1M) {

    DIR *dirp = opendir(dirPath);
    if (dirp == NULL) { // Output error message
        perror("Error");
        return 0;
    } else {
        dirent *subEntry = NULL; // Subentry under the directory
        long totalSize = 0; // Total size of the directory

        // Traversing each file
        while (subEntry = readdir(dirp)) {
            string fileName(subEntry->d_name);
            if (fileName == "." || fileName == "..") {
                continue;
            } else {
                string subFilePath = string(dirPath) + "/" + string(fileName); // Get the file path
                if (subEntry->d_type == DT_REG) { // A regular file
                    long fileSize = getFileSize(subFilePath.c_str());
                    totalSize += fileSize;
                    if (fileSize > 1024 * 1024) { // File size is large than 1M
                        ++(*large_then1M);
                    }
                } else if (subEntry->d_type == DT_DIR) { // A directory
                    totalSize += getDirSize(subFilePath.c_str(), large_then1M);
                }
            }
        }
        return totalSize;
    }
}

// Get the size of the file
unsigned long getFileSize(char const *filePath) {
    if (filePath == NULL) {
        return 0;
    } else {
        struct stat info;  
        stat(filePath, &info);
        return info.st_size;
    }
}