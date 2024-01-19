#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
using namespace std;

namespace fs = std::filesystem;

vector<string> GetMazesFiles() {
    // Specify the path to the folder
    fs::path folderPath = "C:/Users/franc/Documents/GitHub/maze_algorithm/Maze_algorithm/Mazes";
    vector<string> fileList;
    try {
        fs::path path(folderPath);

        // Check if the path exists and is a directory
        if (fs::exists(path) && fs::is_directory(path)) {
            // Iterate over the files in the directory
            for (const auto& entry : fs::directory_iterator(path)) {
                // Add the file name to the vector
                fileList.push_back(entry.path().string());
            }
        }
        else {
            std::cerr << "Invalid folder path or not a directory." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return fileList;
}