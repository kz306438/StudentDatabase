#include "ScrollableTextBox.h"

namespace widgets
{
    namespace scrollableTextBox
    {
        PushButton upFileContent;
        PushButton downFileContent;
        std::vector<std::string> currentContent;
        std::vector<int> slidingWindow;

        // Constants for text box dimensions and position
        const int textBoxHeight = 13; ///< Height of the text box
        const int textBoxWidth = 47; ///< Width of the text box
        const int textBoxPositionX = 38; ///< X-coordinate of the text box position
        const int textBoxPositionY = 9; ///< Y-coordinate of the text box position

        /** @brief Creates the up and down buttons for scrolling.
          * @param posX The x-coordinate for button placement.
          * @param posY The y-coordinate for button placement.
          */
        void create(int posX, int posY)
        {
            const std::string sym_up(1, char(30));
            const std::string sym_down(1, char(31));

            upFileContent = PushButton(48, 3, sym_up, posX, posY);
            downFileContent = PushButton(48, 3, sym_down, posX, posY + 18);
        }

        /** @brief Sets up the appearance of the buttons. */
        void setup()
        {
            upFileContent.setBackgroundColor(BrightRed);
            upFileContent.setForegroundColor(Black);

            downFileContent.setBackgroundColor(BrightRed);
            downFileContent.setForegroundColor(Black);
        }

        /** @brief Renders the text box and its buttons on the screen. */
        void render()
        {
            Window mainFrame(50, 23, 36, 4);
            mainFrame.addWindowName("FILE CONTENT", 15, 0);
            mainFrame.show();

            Window textBox(50, 15, 36, 8);
            textBox.show();

            upFileContent.allowChanges(); upFileContent.show();
            downFileContent.allowChanges(); downFileContent.show();
        }

        /** @brief Reads the file content into the currentContent vector.
          * @param path The path of the file to read.
          */
        void getFileContent(const std::string& path) {
            currentContent.clear();
            std::ifstream file("storage/" + path);

            if (!file.is_open()) {
                setcur(0, 0);
                std::cout << "Failed to open file!" << std::endl;
                return;
            }

            std::string line;
            while (getline(file, line)) {
                currentContent.push_back(line);
            }

            // Ensure the file content fits the text box dimensions
            while (currentContent.size() < textBoxHeight) {
                currentContent.push_back("");
            }

            for (auto& line : currentContent) {
                while (line.size() < textBoxWidth) {
                    line += " ";
                }
                if (line.size() > textBoxWidth) {
                    line.resize(textBoxWidth);
                }
            }

            file.close();
        }

        /** @brief Scrolls the content up by one line. */
        void scrollFileContentsUp() {
            if (!slidingWindow.empty() && slidingWindow[0] > 0) {
                for (auto& element : slidingWindow) {
                    element--;
                }
            }
        }

        /** @brief Scrolls the content down by one line. */
        void scrollFileContentsDown() {
            if (!slidingWindow.empty() && slidingWindow[textBoxHeight - 1] < currentContent.size() - 1) {
                for (auto& element : slidingWindow) {
                    element++;
                }
            }
        }

        /** @brief Sets up the current open file and initializes the sliding window.
          * @param path The path of the file to open.
          */
        void setupCurrentOpenFile(const std::string& path) {
            getFileContent(path);
            slidingWindow.resize(textBoxHeight);

            for (int i = 0; i < (std::min)(static_cast<int>(currentContent.size()), textBoxHeight); ++i) {
                slidingWindow[i] = i;
            }
        }

        /** @brief Displays the current content of the file on the screen. */
        void showFileContent() {
            for (int i = 0; i < slidingWindow.size(); ++i) {
                setcur(textBoxPositionX, textBoxPositionY + i);
                std::cout << currentContent[slidingWindow[i]];
            }
        }

    } // namespace scrollableTextBox 

} // namespace widgets