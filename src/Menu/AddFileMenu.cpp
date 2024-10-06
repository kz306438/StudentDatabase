#include "AddFileMenu.h"
#include <fstream>
#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"
#include "../Student.h"
#include "../Widgets/FileSlider.h"

using namespace widgets;

namespace database {

    static void renderAddFileMenu();

    /**
     * @brief PushButton for going back in the menu
     */
    static PushButton backButton;

    /**
     * @brief Flag to control the main menu loop
     */
    static bool runAddMenu = true;

    /**
     * @brief Creates buttons for file-related actions and back navigation.
     * Initializes the buttons for files and a button to go back to the previous menu.
     */
    static void createFilesButtons() {
        fileSlider::createFilesButtons(36, 5);
        backButton = PushButton(20, 5, "BACK", 65, 21);
    }

    /**
     * @brief Configures the appearance (background and foreground colors) of the buttons.
     * Sets up the visual properties of the file buttons and the back button.
     */
    static void setupFilesButton() {
        fileSlider::setupFileButtons();
        backButton.setBackgroundColor(White);
        backButton.setForegroundColor(Black);
    }

    /**
     * @brief Adds a student to a specified file.
     * Opens a file, creates a new student, and appends the student information to the file.
     *
     * @param path The path to the file where the student will be added.
     */
    static void addStudentToFile(const std::string& path) {
        Student student = createStudent();
        std::ofstream file("storage/" + path, std::ios::app);

        if (!file.is_open()) {
            Utils::applicationErrorWindow("ERROR OPENING FILE", 61, 9, 30, 10);
            return;
        }

        writeStudent(file, student);
        file.close();
    }

    /**
     * @brief Handles file interaction by adding a student to the file.
     * If the path is valid, the function will add the student to the file and re-render the menu.
     *
     * @param path The path to the file being processed.
     */
    static void workWithFile(const std::string& path) {
        if (path.empty())
            return;

        Utils::paintOverBackground();
        addStudentToFile(path);
        Utils::paintOverBackground();
        renderAddFileMenu();

        setupInputHandling();
    }

    /**
     * @brief Connects file buttons to their corresponding actions.
     * Sets up the event handling for buttons related to file operations, such as selecting and navigating files.
     */
    static void connectFilesButtons() {
        fileSlider::upFile.connect([&]() {
            fileSlider::moveSlidingFileWindowUp();
            fileSlider::updateFileButtonNames();
            });

        fileSlider::file1.connect([&]() {
            workWithFile(fileSlider::getFileName(fileSlider::slidingFileWindow[0]));
            });

        fileSlider::file2.connect([&]() {
            workWithFile(fileSlider::getFileName(fileSlider::slidingFileWindow[1]));
            });

        fileSlider::file3.connect([&]() {
            workWithFile(fileSlider::getFileName(fileSlider::slidingFileWindow[2]));
            });

        fileSlider::file4.connect([&]() {
            workWithFile(fileSlider::getFileName(fileSlider::slidingFileWindow[3]));
            });

        fileSlider::file5.connect([&]() {
            workWithFile(fileSlider::getFileName(fileSlider::slidingFileWindow[4]));
            });

        fileSlider::downFile.connect([&]() {
            fileSlider::moveSlidingFileWindowDown();
            fileSlider::updateFileButtonNames();
            });

        backButton.connect([&]() {
            runAddMenu = false;
            });
    }



    /**
     * @brief Displays the message in the add file menu.
     * Shows a window with a prompt for the user to select a file for adding student information.
     */
    static void showAddFileMenuMessage() {
        Window msgFrame(25, 9, 63, 4);
        msgFrame.addWindowName("MSG", 9, 0);
        msgFrame.show();

        setcur(66, 5); std::cout << char(250) << ' ' << "SELECT THE FILE";
        setcur(68, 7); std::cout << "WHICH YOU WANT";
        setcur(68, 9); std::cout << "TO ADD STUDENT";
        setcur(68, 11); std::cout << "INFORMATION";
    }

    /**
     * @brief Renders the add file menu interface.
     * Displays the file slider and the back button, allowing the user to interact with the menu.
     */
    static void renderAddFileMenu() {
        showAddFileMenuMessage();
        fileSlider::renderFileSlider(35, 4);
        backButton.allowChanges();
        backButton.show();
    }

    /**
     * @brief Sets up the add file menu.
     * Initializes the sliding window, buttons, and event handlers for file-related actions.
     */
    void setupAddFileMenu() {
        runAddMenu = true;
        fileSlider::setupSlidingFileWindow();
        createFilesButtons();
        setupFilesButton();
        renderAddFileMenu();
        connectFilesButtons();
    }

    /**
     * @brief Main loop for the Add File Menu.
     * Manages the user input and interaction with the file slider and buttons.
     */
    void addFileMenu() {
        setupAddFileMenu();
        setupInputHandling();
        invisibleCursor();

        while (runAddMenu) {
            mouseButtonInteraction(
                &fileSlider::upFile,
                &fileSlider::file1,
                &fileSlider::file2,
                &fileSlider::file3,
                &fileSlider::file4,
                &fileSlider::file5,
                &fileSlider::downFile,
                &backButton
            );
        }
    }

} // namespace database
