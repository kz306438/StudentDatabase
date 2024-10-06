#include "FileSlider.h"

namespace widgets
{
    namespace fileSlider
    {
        PushButton upFile, file1, file2, file3, file4, file5, downFile;
        std::vector<int> slidingFileWindow(5);

        /** @brief Initializes the sliding file window with the first five file indices. */
        void setupSlidingFileWindow()
        {
            for (int i = 0; i < 5; ++i)
                slidingFileWindow[i] = i;
        }

        /** @brief Moves the sliding file window up by one index. */
        void moveSlidingFileWindowUp()
        {
            if (slidingFileWindow[0] > 0)
            {
                for (auto& element : slidingFileWindow)
                {
                    element--;
                }
            }
        }

        /** @brief Moves the sliding file window down by one index. */
        void moveSlidingFileWindowDown()
        {
            if (slidingFileWindow[4] < database::mainDirectory.size() - 1)
            {
                for (auto& element : slidingFileWindow)
                {
                    element++;
                }
            }
        }

        /** @brief Creates buttons for file navigation at specified coordinates.
          * @param posX The x-coordinate for button placement.
          * @param posY The y-coordinate for button placement.
          */
        void createFilesButtons(int posX, int posY)
        {
            const std::string sym_up(1, char(30));
            const std::string sym_down(1, char(31));

            upFile = PushButton(20, 3, sym_up, posX, posY);
            file1 = PushButton(20, 3, getFileName(slidingFileWindow[0]), posX, posY + 3);
            file2 = PushButton(20, 3, getFileName(slidingFileWindow[1]), posX, posY + 6);
            file3 = PushButton(20, 3, getFileName(slidingFileWindow[2]), posX, posY + 9);
            file4 = PushButton(20, 3, getFileName(slidingFileWindow[3]), posX, posY + 12);
            file5 = PushButton(20, 3, getFileName(slidingFileWindow[4]), posX, posY + 15);
            downFile = PushButton(20, 3, sym_down, posX, 23);
        }

        /** @brief Updates the names of the file buttons based on the current sliding window. */
        void updateFileButtonNames()
        {
            file1.setName(getFileName(slidingFileWindow[0]));
            file2.setName(getFileName(slidingFileWindow[1]));
            file3.setName(getFileName(slidingFileWindow[2]));
            file4.setName(getFileName(slidingFileWindow[3]));
            file5.setName(getFileName(slidingFileWindow[4]));
        }

        /** @brief Sets the background and foreground colors for a button.
          * @param button Reference to the button to set colors for.
          * @param bgColor Background color to set.
          * @param fgColor Foreground color to set.
          */
        static void setupFileButtonColors(PushButton& button, ConsoleColor bgColor, ConsoleColor fgColor) {
            button.setBackgroundColor(bgColor);
            button.setForegroundColor(fgColor);
        }

        /** @brief Sets up the appearance of all file buttons. */
        void setupFileButtons()
        {
            setupFileButtonColors(upFile, BrightRed, Black);
            setupFileButtonColors(file1, White, Black);
            setupFileButtonColors(file2, White, Black);
            setupFileButtonColors(file3, White, Black);
            setupFileButtonColors(file4, White, Black);
            setupFileButtonColors(file5, White, Black);
            setupFileButtonColors(downFile, BrightRed, Black);
        }

        /** @brief Renders the file slider at specified coordinates.
          * @param posX The x-coordinate for the file slider.
          * @param posY The y-coordinate for the file slider.
          */
        void renderFileSlider(int posX, int posY)
        {
            Window filesArea(22, 23, posX, posY);
            filesArea.addWindowName("FILES", 7, 0);
            filesArea.show();

            upFile.allowChanges(); upFile.show();
            file1.allowChanges(); file1.show();
            file2.allowChanges(); file2.show();
            file3.allowChanges(); file3.show();
            file4.allowChanges(); file4.show();
            file5.allowChanges(); file5.show();
            downFile.allowChanges(); downFile.show();
        }

    } // namespace fileSlider

} // namespace widgets