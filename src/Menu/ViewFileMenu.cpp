#include "ViewFileMenu.h"

#include <fstream>
#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"
#include "../Widgets/ScrollableTextBox.h"
#include "../Widgets/FileSlider.h"

using namespace widgets;

namespace database
{
    static PushButton back; ///< Button to navigate back in the menu

    bool runViewFilesMenu; ///< Flag to control the menu state

    /** @brief Handles file selection and displays its content.
      * @param index The index of the selected file.
      */
    static void workWithFile(int index) {
        activeFile = fileSlider::getFileName(fileSlider::slidingFileWindow[index]);

        if (activeFile.empty())
            return;

        scrollableTextBox::setupCurrentOpenFile(activeFile);
        scrollableTextBox::showFileContent();
    }

    /** @brief Creates buttons for file navigation and display.
      */
    static void createButtons()
    {
        fileSlider::createFilesButtons(10, 5);
        scrollableTextBox::create(37, 5);
        back = PushButton(20, 5, "BACK", 90, 21);
    }

    /** @brief Sets up colors for all file buttons.
      */
    static void setupButtons()
    {
        fileSlider::setupFileButtons();
        scrollableTextBox::setup();

        back.setBackgroundColor(White);
        back.setForegroundColor(Black);
    }

    /** @brief Connects button actions to their respective functions.
      */
    static void connectFilesButtons() {
        fileSlider::upFile.connect([&]() {
            fileSlider::moveSlidingFileWindowUp();
            fileSlider::updateFileButtonNames();
            });

        fileSlider::file1.connect([&]() {
            workWithFile(0);
            });

        fileSlider::file2.connect([&]() {
            workWithFile(1);
            });

        fileSlider::file3.connect([&]() {
            workWithFile(2);
            });

        fileSlider::file4.connect([&]() {
            workWithFile(3);
            });

        fileSlider::file5.connect([&]() {
            workWithFile(4);
            });


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

        back.connect([&]() {
            runViewFilesMenu = false;
            });
    }

    /** @brief Renders the view files menu components.
      */
    void renderViewFilesMenu()
    {
        fileSlider::renderFileSlider(9, 4);
        scrollableTextBox::render();
        back.allowChanges();
        back.show();
    }

    /** @brief Sets up the view file menu and initializes its components.
      */
    void setupViewFileMenu() {
        runViewFilesMenu = true;

        fileSlider::setupSlidingFileWindow();
        createButtons();
        setupButtons();
        renderViewFilesMenu();
        connectFilesButtons();
    }

    /** @brief Main loop for handling the view file menu interactions.
      */
    void viewFileMenu() {
        setupViewFileMenu();
        setupInputHandling();
        invisibleCursor();

        while (runViewFilesMenu) {
            mouseButtonInteraction(&fileSlider::upFile,
                &fileSlider::file1,
                &fileSlider::file2,
                &fileSlider::file3,
                &fileSlider::file4,
                &fileSlider::file5,
                &fileSlider::downFile,
                &scrollableTextBox::upFileContent,
                &scrollableTextBox::downFileContent,
                &back);
        }
    }

} // namespace database