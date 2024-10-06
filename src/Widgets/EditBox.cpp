#include "EditBox.h"
#include "../../consoleGUI/GUI.h"
#include <fstream>
#include "../Utils.h"

namespace widgets
{
    namespace editBox
    {
        // Global variables
        std::vector<std::string> currentContent;
        std::vector<int> slidingWindow;

        const int editBoxHeight = 21;
        const int editBoxWidth = 60;
        const int editBoxPositionX = 40;
        const int editBoxPositionY = 5;

        /**
         * Renders the edit box frame on the console.
         *
         * Creates a bordered frame where the edit box content will be displayed.
         */
        void render() {
            // Creating a bordered window to display the content
            Window editBoxFrame(1 + editBoxWidth + 1, 1 + editBoxHeight + 1, editBoxPositionX - 1, editBoxPositionY - 1);
            editBoxFrame.addWindowName("edit box", 1, 0);
            editBoxFrame.show();
        }

        /**
         * Loads file content into the edit box and initializes the sliding window.
         */
        void setup(const std::string& path) {
            currentContent.clear();  // Clear previous content
            getFileContent(path);    // Load content from file
            render();                // Render the edit box frame
            initializeSlidingWindow(); // Set up the sliding window for scrolling
        }

        /**
         * Reads the file content and adjusts it to fit the edit box dimensions.
         */
        void getFileContent(const std::string& path) {
            currentContent.clear();
            std::ifstream file("storage/" + path);

            if (!file.is_open()) {
                // File open error handling
                Utils::applicationErrorWindow("FILE OPENING ERROR", 61, 9, 30, 10);
                return;
            }

            std::string line;
            // Reading each line and adding it to currentContent
            while (getline(file, line)) {
                currentContent.push_back(line);
            }

            // Padding the content to match the height of the edit box
            while (currentContent.size() < editBoxHeight) {
                currentContent.push_back("");
            }

            // Ensuring each line fits within the width of the edit box
            for (auto& line : currentContent) {
                while (line.size() < editBoxWidth) {
                    line += " ";
                }
                if (line.size() > editBoxWidth) {
                    line.resize(editBoxWidth);
                }
            }

            file.close();
        }

        /**
         * Initializes the sliding window for scrolling.
         *
         * The sliding window keeps track of which lines are currently visible in the edit box.
         */
        void initializeSlidingWindow() {
            slidingWindow.resize(editBoxHeight);
            // Set up the initial visible lines (up to the height of the edit box)
            for (int i = 0; i < (std::min)(static_cast<int>(currentContent.size()), editBoxHeight); ++i) {
                slidingWindow[i] = i;
            }
        }

        /**
         * Displays the text content currently visible in the edit box.
         *
         * This method loops over the sliding window and displays the appropriate lines from currentContent.
         */
        void displayText(int curPosX, int curPosY) {
            for (int i = 0; i < slidingWindow.size(); ++i) {
                setcur(editBoxPositionX, editBoxPositionY + i);
                std::string out = "";
                for (int j = 0; j < editBoxWidth; ++j)
                    out += currentContent[slidingWindow[i]][j];
                std::cout << out;
            }
        }

        /**
         * Displays the cursor at the specified position.
         */
        void displayCursor(int curPosX, int curPosY) {
            saveConsoleAttributes();
            setColorBackground(White);
            setColorForeground(Black);
            setcur(editBoxPositionX + curPosX, editBoxPositionY + curPosY);
            std::cout << currentContent[slidingWindow[curPosY]][curPosX];
            restoreConsoleAttributes();
        }

        /**
         * Handles the backspace key press, removing characters from the edit box.
         */
        void handleBackspace(int& cursorX, int& cursorY) {
            if (cursorX > 0) {
                // Remove character and shift the rest of the line
                currentContent[slidingWindow[cursorY]].erase(cursorX - 1, 1);
                currentContent[slidingWindow[cursorY]] += ' ';
                cursorX--;
            }
        }

        /**
         * Handles the insertion of characters at the cursor position.
         */
        void handleInsert(int& cursorX, int& cursorY, char ch) {
            if (cursorY >= 0 && cursorY < currentContent.size()) {
                // Insert character and move the cursor forward
                currentContent[slidingWindow[cursorY]].insert(cursorX, 1, ch);
                if (cursorX < editBoxWidth - 1)
                    cursorX++;
            }
        }

        /**
         * Saves the current content of the edit box into a file.
         */
        void saveChanges(const std::string& path) {
            std::ofstream file(path);
            if (!file.is_open()) {
                // Error handling when the file can't be opened
                Utils::applicationErrorWindow("ERROR OPENING FILE", 61, 9, 30, 10);
                return;
            }
            for (const auto& line : currentContent) {
                file << line << std::endl;
            }
        }

        /**
         * Scrolls the content of the edit box up.
         */
        void scrollFileContentsUp() {
            if (!slidingWindow.empty() && slidingWindow[0] > 0) {
                // Move the sliding window up by one line
                for (auto& element : slidingWindow) {
                    element--;
                }
            }
        }

        /**
         * Scrolls the content of the edit box down.
         */
        void scrollFileContentsDown() {
            if (!slidingWindow.empty() && slidingWindow[editBoxHeight - 1] < currentContent.size() - 1) {
                // Move the sliding window down by one line
                for (auto& element : slidingWindow) {
                    element++;
                }
            }
        }


        /**
         * Processes user input and moves the cursor or edits the content accordingly.
         */
        void processInput(int ch, int& cursorX, int& cursorY) {
            if (ch == 224) { // Arrow keys
                ch = _getch();
                switch (ch) {
                case 72: // Up arrow
                    if (cursorY > 0)
                        cursorY--;
                    else
                        scrollFileContentsUp();
                    break;
                case 80: // Down arrow
                    if (cursorY < editBoxHeight - 1)
                        cursorY++;
                    else
                        scrollFileContentsDown();
                    break;
                case 75: // Left arrow
                    if (cursorX > 0) cursorX--;
                    break;
                case 77: // Right arrow
                    if (cursorX < editBoxWidth - 1) cursorX++;
                    break;
                }
            }
            else if (ch == 8) { // Backspace
                handleBackspace(cursorX, cursorY);
            }
            else if (ch >= 32 && ch <= 126) { // Printable characters
                handleInsert(cursorX, cursorY, ch);
            }
        }

        /**
         * Main loop that handles user input for editing the content.
         */
        void handleEditBox() {
            int cursorX = 0, cursorY = 0;
            displayText(cursorX, cursorY);
            displayCursor(cursorX, cursorY);

            while (true) {
                int ch = _getch();
                if (ch == 27) { // Escape key to exit
                    break;
                }
                processInput(ch, cursorX, cursorY);
                displayText(cursorX, cursorY);
                displayCursor(cursorX, cursorY);
            }
        }

    } // namespace editBox

} // namespace widgets
