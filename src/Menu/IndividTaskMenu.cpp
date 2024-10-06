#include "IndividTaskMenu.h"

#include <vector>
#include <sstream>
#include <fstream>

#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"
#include "../Widgets/ScrollableTextBox.h"
#include "../Widgets/FileSlider.h"

using namespace widgets;

namespace database
{
    // Static button declarations
    static PushButton backButton;  // Back button for navigation

    bool runIndividualTaskMenu; // Flag to control the menu loop

    /**
     * @brief Processes a line from the file to extract student data.
     *
     * @param line The line of text to process.
     * @param studentData Vector to hold the data of the current student.
     * @param addStudent Flag indicating whether to add the current student.
     */
    static void processLine(const std::string& line, std::vector<std::string>& studentData, bool& addStudent) {
        // Check for a new student's name
        if (line.find("STUDENT'S NAME:") != std::string::npos && !studentData.empty()) {
            if (addStudent) {
                scrollableTextBox::currentContent.insert(scrollableTextBox::currentContent.end(), studentData.begin(), studentData.end());
            }
            studentData.clear();
            addStudent = true;
        }

        studentData.push_back(line); // Add the current line to the student's data

        // Check for scores and set the flag accordingly
        if (line.find("MATH SCORE:") != std::string::npos || line.find("CS SCORE:") != std::string::npos) {
            std::istringstream iss(line.substr(line.find(":") + 1));
            int score;
            while (iss >> score) {
                if (score < 4) {
                    addStudent = false; // Set flag to false if score is below threshold
                }
            }
        }
    }

    /**
     * @brief Adjusts the content of the scrollable text box to fit its size.
     */
    static void adjustFileContent() {
        // Fill empty lines if current content is less than text box height
        while (scrollableTextBox::currentContent.size() < scrollableTextBox::textBoxHeight) {
            scrollableTextBox::currentContent.push_back("");
        }

        // Adjust each line to fit the width of the text box
        for (auto& line : scrollableTextBox::currentContent) {
            while (line.size() < scrollableTextBox::textBoxWidth) {
                line += " "; // Pad line with spaces
            }
            if (line.size() > scrollableTextBox::textBoxWidth) {
                line.resize(scrollableTextBox::textBoxWidth); // Resize if too long
            }
        }
    }

    /**
     * @brief Reads the content of a specified file and processes it.
     *
     * @param path The path of the file to read.
     */
    static void getFileContent(const std::string& path) {
        scrollableTextBox::currentContent.clear();
        std::ifstream file("storage/" + path);

        if (!file.is_open()) {
            Utils::applicationErrorWindow("ERROR DELETING FILE", 61, 9, 30, 10);
            return; // Exit if file cannot be opened
        }

        std::string line;
        std::vector<std::string> studentData;
        bool addStudent = true;

        // Process each line of the file
        while (getline(file, line)) {
            processLine(line, studentData, addStudent);
        }

        // Add the last student's data if applicable
        if (addStudent && !studentData.empty()) {
            scrollableTextBox::currentContent.insert(scrollableTextBox::currentContent.end(), studentData.begin(), studentData.end());
        }

        adjustFileContent(); // Adjust the content for display
        file.close();
    }

    /**
     * @brief Sets up the currently open file's content for display.
     *
     * @param path The path of the file to be displayed.
     */
    static void setupCurrentOpenFile(const std::string& path) {
        getFileContent(path); // Load content from the file
        scrollableTextBox::slidingWindow.resize(scrollableTextBox::textBoxHeight);

        // Initialize sliding window
        for (int i = 0; i < (std::min)(static_cast<int>(scrollableTextBox::currentContent.size()), scrollableTextBox::textBoxHeight); ++i) {
            scrollableTextBox::slidingWindow[i] = i;
        }
    }

    /**
     * @brief Handles the selection of a file and displays its content.
     *
     * @param index The index of the selected file.
     */
    static void workWithFile(int index) {
        activeFile = fileSlider::getFileName(fileSlider::slidingFileWindow[index]);

        if (activeFile.empty())
            return; // Exit if no file selected

        setupCurrentOpenFile(activeFile); // Set up and display the selected file's content
        scrollableTextBox::showFileContent();
    }

    /**
     * @brief Creates buttons for file selection and scrolling.
     */
    static void createFilesButtons()
    {
        fileSlider::createFilesButtons(10, 5);
        scrollableTextBox::create(37, 5);
        backButton = PushButton(20, 5, "BACK", 90, 21); // Create back button
    }

    /**
     * @brief Sets up colors for all buttons in the menu.
     */
    static void setupFilesButton()
    {
        fileSlider::setupFileButtons();
        scrollableTextBox::setup();
        backButton.setBackgroundColor(White);
        backButton.setForegroundColor(Black);
    }

    /**
     * @brief Connects actions to the buttons in the file selection menu.
     */
    static void connectFilesButtons()
    {
        fileSlider::upFile.connect([&]() {
            fileSlider::moveSlidingFileWindowUp();
            fileSlider::updateFileButtonNames();
            });

        fileSlider::file1.connect([&]() { workWithFile(0); });
        fileSlider::file2.connect([&]() { workWithFile(1); });
        fileSlider::file3.connect([&]() { workWithFile(2); });
        fileSlider::file4.connect([&]() { workWithFile(3); });
        fileSlider::file5.connect([&]() { workWithFile(4); });

        fileSlider::downFile.connect([&]() {
            fileSlider::moveSlidingFileWindowDown();
            fileSlider::updateFileButtonNames();
            });

        scrollableTextBox::upFileContent.connect([&]() {
            scrollableTextBox::scrollFileContentsUp();
            scrollableTextBox::showFileContent();
            });

        scrollableTextBox::downFileContent.connect([&]() {
            scrollableTextBox::scrollFileContentsDown();
            scrollableTextBox::showFileContent();
            });

        backButton.connect([&]() {
            runIndividualTaskMenu = false;
            });
    }

    /**
     * @brief Renders the individual task menu components.
     */
    void renderIndividualTaskMenu()
    {
        fileSlider::renderFileSlider(9, 4);
        scrollableTextBox::render();
        backButton.allowChanges();
        backButton.show();
    }

    /**
     * @brief Sets up the individual task menu for user interaction.
     */
    void setupIndividualTaskMenu() {
        runIndividualTaskMenu = true; // Enable the menu loop

        fileSlider::setupSlidingFileWindow(); // Set up the file slider
        createFilesButtons(); // Create file selection buttons
        setupFilesButton(); // Set up button colors

        renderIndividualTaskMenu(); // Render the menu

        connectFilesButtons(); // Connect button actions
        setupInputHandling(); // Set up input handling for user interaction
    }

    /**
     * @brief Main function to run the individual task menu.
     */
    void individualTaskMenu()
    {
        setupIndividualTaskMenu(); // Initialize the menu setup

        // Main loop to keep the menu active
        while (runIndividualTaskMenu)
        {
            mouseButtonInteraction(
                &fileSlider::upFile,
                &fileSlider::file1,
                &fileSlider::file2,
                &fileSlider::file3,
                &fileSlider::file4,
                &fileSlider::file5,
                &fileSlider::downFile,
                &backButton,
                &scrollableTextBox::upFileContent,
                &scrollableTextBox::downFileContent
            );
        }
    }

} // namespace database
