#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

// Function to read input file and return 2D vector of integers
std::vector<std::vector<int> > readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int> > data;  // Stores all sequences
    std::string line;
    
    // Read file line by line
    while (std::getline(file, line)) {
        std::vector<int> row;  // Store numbers from current line
        std::istringstream ss(line);
        int num;
        
        // Parse space-separated numbers from line
        while (ss >> num) {
            row.push_back(num);
        }
        data.push_back(row);
    }
    return data;
}

// Check if sequence is valid (all increasing or decreasing by 1-3)
bool isValidSequence(const std::vector<int>& sequence) {
    if (sequence.size() < 2) return false;
    
    // Determine if sequence should increase based on first two numbers
    bool shouldIncrease = sequence[1] > sequence[0];
    
    // Check each adjacent pair of numbers
    for (size_t i = 1; i < sequence.size(); i++) {
        int diff = sequence[i] - sequence[i-1];
        
        // Check rules: difference must be 1-3, and maintain same direction
        if (abs(diff) < 1 || abs(diff) > 3) return false;
        if (shouldIncrease && diff < 0) return false;
        if (!shouldIncrease && diff > 0) return false;
    }
    return true;
}

// Check if sequence is valid with Problem Dampener (can remove one number)
bool isValidWithDampener(const std::vector<int>& sequence) {
    if (isValidSequence(sequence)) return true;
    
    // Try removing each number and check if resulting sequence is valid
    for (size_t i = 0; i < sequence.size(); i++) {
        std::vector<int> modified = sequence;
        modified.erase(modified.begin() + i);  // Remove number at position i
        if (isValidSequence(modified)) return true;
    }
    return false;
}

int main() {
    std::cout << "advent of code day 2 output:\n";
    auto numbers = readFile("input.txt");
    
    // Count sequences that are valid normally and with dampener
    int safeCount = 0;
    int safeWithDampenerCount = 0;
    
    for (const auto& sequence : numbers) {
        if (isValidSequence(sequence)) safeCount++;
        if (isValidWithDampener(sequence)) safeWithDampenerCount++;
    }
    
    // Output results
    std::cout << "Part 1 - Safe reports: " << safeCount << "\n";
    std::cout << "Part 2 - Safe reports with dampener: " << safeWithDampenerCount << "\n";
    return 0;
}
