#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

struct DirectoryReport {
    int total_files = 0;
    int total_directories = 0;
    uintmax_t total_size = 0;
    std::pair<std::string, uintmax_t> largest_file;
    std::pair<std::string, int> most_common_extension;
};

void analyzeDirectory(const fs::path& directory, DirectoryReport& report) {
    std::map<std::string, int> extension_count;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        try {
            if (fs::is_regular_file(entry)) {
                report.total_files++;
                uintmax_t file_size = fs::file_size(entry);
                report.total_size += file_size;

                if (file_size > report.largest_file.second) {
                    report.largest_file = {entry.path().string(), file_size};
                }

                std::string extension = entry.path().extension().string();
                if (!extension.empty()) {
                    extension_count[extension]++;
                }
            } else if (fs::is_directory(entry)) {
                report.total_directories++;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error accessing " << entry.path() << ": " << e.what() << std::endl;
        }
    }

    if (!extension_count.empty()) {
        report.most_common_extension = *std::max_element(
            extension_count.begin(), extension_count.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });
    }
}

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage: ./main <file_path>" << std::endl;
        return 1;
    }
    fs::path directory = argv[1];
    DirectoryReport report;

    analyzeDirectory(directory, report);

    std::cout << "Total files: " << report.total_files << std::endl;
    std::cout << "Total directories: " << report.total_directories << std::endl;
    std::cout << "Total size: " << report.total_size << " bytes" << std::endl;
    std::cout << "Largest file: " << report.largest_file.first << " (" << report.largest_file.second << " bytes)" << std::endl;
    std::cout << "Most common extension: " << report.most_common_extension.first << " (" << report.most_common_extension.second << " files)" << std::endl;

    return 0;
}