#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <stdexcept>

// Class to encapsulate item tracking functionality.
class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies; // Stores item frequencies
    std::string inputFileName;   // Name of the input data file
    std::string outputFileName;  // Name of the backup output file

    // Loads item data from the input file into itemFrequencies map.
    void loadItemsFromFile() {
        std::ifstream inputFile(inputFileName);

        if (!inputFile.is_open()) {
            throw std::runtime_error("Error: Could not open input file " + inputFileName);
        }

        std::string item;
        while (inputFile >> item) {
            itemFrequencies[item]++;
        }
        inputFile.close();
    }

    // Backs up item frequency data to the output file (frequency.dat).
    void backupFrequenciesToFile() const {
        std::ofstream outputFile(outputFileName);

        if (!outputFile.is_open()) {
            std::cerr << "Error: Could not create/open backup file " << outputFileName << std::endl;
            return;
        }

        for (const auto& pair : itemFrequencies) {
            outputFile << pair.first << " " << pair.second << std::endl;
        }
        outputFile.close();
    }

    // Clears the input buffer to prevent issues with subsequent inputs.
    void clearInputBuffer() const {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    // Constructor: Initializes files and loads data.
    ItemTracker(const std::string& input_file, const std::string& output_file)
        : inputFileName(input_file), outputFileName(output_file) {
        try {
            loadItemsFromFile();
            backupFrequenciesToFile(); // Create backup file at program start
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Returns the frequency of a specific item (Menu Option One).
    int getItemFrequency(const std::string& item) const {
        auto it = itemFrequencies.find(item);
        if (it != itemFrequencies.end()) {
            return it->second;
        } else {
            return 0;
        }
    }

    // Prints the list of all items with their frequencies (Menu Option Two).
    void printAllFrequencies() const {
        std::cout << "\n--- Item Frequencies ---" << std::endl;
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
        std::cout << "------------------------\n" << std::endl;
    }

    // Prints the frequency information as a histogram (Menu Option Three).
    void printHistogram() const {
        std::cout << "\n--- Item Frequency Histogram ---" << std::endl;
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
        std::cout << "--------------------------------\n" << std::endl;
    }

    // Displays the main menu options.
    void displayMenu() const {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "           Corner Grocer Menu           " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. Look up an item's frequency" << std::endl;
        std::cout << "2. Print all item frequencies" << std::endl;
        std::cout << "3. Print item frequencies as a histogram" << std::endl;
        std::cout << "4. Exit program" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
    }

    // Runs the main program loop.
    void runProgram() {
        int choice;
        std::string searchItem;
        int frequency;

        do {
            displayMenu();

            while (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter a number (1-4): ";
                clearInputBuffer();
            }
            clearInputBuffer(); // Clear remaining newline character

            switch (choice) {
                case 1:
                    std::cout << "\nEnter the item you wish to look for: ";
                    std::getline(std::cin, searchItem);
                    frequency = getItemFrequency(searchItem);
                    std::cout << searchItem << " appeared " << frequency << " time(s)." << std::endl;
                    break;
                case 2:
                    printAllFrequencies();
                    break;
                case 3:
                    printHistogram();
                    break;
                case 4:
                    std::cout << "Exiting program. Goodbye!\n" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please enter a number between 1 and 4.\n" << std::endl;
                    break;
            }
            std::cout << std::endl;
        } while (choice != 4);
    }
};

// Main function where program execution begins.
int main() {
    // Create ItemTracker instance, providing input and output file names.
    // Ensure 'input.txt' exists in the same directory as your executable.
    ItemTracker tracker("input.txt", "frequency.dat");

    tracker.runProgram();

    return 0; // Indicate successful execution.
}