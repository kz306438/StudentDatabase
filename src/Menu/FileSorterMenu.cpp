#include "FileSorterMenu.h"

#include <fstream>
#include <algorithm>

#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"
#include "../Student.h"
#include "../Widgets/FileSlider.h"

using namespace widgets;

namespace database
{
    // Static declarations
    static PushButton backButton;
    static SortingMethod currentSortingMethod;
    static std::vector<Student> students;

    bool isFileSorterMenuActive = false;

    /**
     * @brief Initializes buttons for file selection and navigation.
     * This function creates buttons for file interaction and a back button.
     */
    static void initializeFileButtons()
    {
        fileSlider::createFilesButtons(36, 5);
        backButton = PushButton(20, 5, "BACK", 65, 21);
    }

    /**
     * @brief Helper function to set the background and foreground colors of a button.
     *
     * @param button The button to which the colors will be applied.
     * @param bgColor The background color.
     * @param fgColor The foreground color.
     */
    static void configureButtonColors(PushButton& button, ConsoleColor bgColor, ConsoleColor fgColor)
    {
        button.setBackgroundColor(bgColor);
        button.setForegroundColor(fgColor);
    }

    /**
     * @brief Sets up colors for all file buttons and the back button.
     */
    static void setupFileButtons()
    {
        fileSlider::setupFileButtons();
        configureButtonColors(backButton, White, Black);
    }

    /**
     * @brief Displays a window for the user to select a sorting type.
     *
     * @return SortingType The sorting type selected by the user (ascending or descending).
     */
    [[nodiscard]] SortingType promptUserForSortingType()
    {
        bool isWindowActive = true;
        SortingType selectedSortingType{};

        Window selectionWindow(61, 9, 30, 10);
        selectionWindow.addWindowName("Select Sort Type", 1, 0);
        selectionWindow.show();

        setcur(53, 11); std::cout << "SELECT SORT TYPE";

        PushButton descendingButton(20, 3, "DESCENDING", 36, 15);
        PushButton ascendingButton(20, 3, "ASCENDING", 64, 15);

        descendingButton.connect([&]() {
            isWindowActive = false;
            selectedSortingType = Descending;
            });

        ascendingButton.connect([&]() {
            isWindowActive = false;
            selectedSortingType = Ascending;
            });

        configureButtonColors(descendingButton, White, Black);
        configureButtonColors(ascendingButton, White, Black);

        while (isWindowActive)
        {
            mouseButtonInteraction(&descendingButton, &ascendingButton);
        }

        return selectedSortingType;
    }

    /**
     * @brief Sorts the student list by the specified field and order.
     *
     * @param sortingType The sorting order (ascending or descending).
     */
    template <typename SortFunc>
    void sortByField(SortingType sortingType, SortFunc sortFunc)
    {
        switch (sortingType)
        {
        case Ascending:
            std::sort(students.begin(), students.end(), sortFunc);
            break;
        case Descending:
            std::sort(students.begin(), students.end(), [&sortFunc](const Student& a, const Student& b) {
                return sortFunc(b, a);
                });
            break;
        }
    }

    /**
     * @brief Sorts the student list based on the selected sorting method.
     *
     * @param sortingType The sorting order (ascending or descending).
     */
    void performSortByField(SortingType sortingType)
    {
        switch (currentSortingMethod)
        {
        case SortBySurname:
            sortByField(sortingType, [](const Student& a, const Student& b) { return a.surname < b.surname; });
            break;
        case SortByAverageGrade:
            sortByField(sortingType, [](const Student& a, const Student& b) { return a.averageGrade < b.averageGrade; });
            break;
        case SortByAveragePhisicsGrade:
            sortByField(sortingType, [](const Student& a, const Student& b) { return a.averagePhisicsGrade < b.averagePhisicsGrade; });
            break;
        case SortByAverageMathGrade:
            sortByField(sortingType, [](const Student& a, const Student& b) { return a.averageMathGrade < b.averageMathGrade; });
            break;
        case SortByAverageInformGrade:
            sortByField(sortingType, [](const Student& a, const Student& b) { return a.averageInformGrade < b.averageInformGrade; });
            break;
        }
    }

    /**
     * @brief Displays a message window instructing the user to select a file.
     */
    static void displayFileSelectionMessage()
    {
        Window messageWindow(25, 9, 63, 4);
        messageWindow.addWindowName("MSG", 9, 0);
        messageWindow.show();

        setcur(68, 6); std::cout << char(250) << ' ' << "SELECT THE";
        setcur(70, 8); std::cout << "FILE TO BE";
        setcur(70, 10); std::cout << "SORTED";
    }

    /**
     * @brief Renders the file sorter menu and its components.
     */
    static void renderFileSorterMenu()
    {
        Utils::paintOverBackground();
        displayFileSelectionMessage();
        fileSlider::renderFileSlider(35, 4);
        backButton.allowChanges();
        backButton.show();
        setupInputHandling();
    }

    /**
     * @brief Processes the file for sorting and updates the results.
     *
     * @param filePath The path to the file being worked on.
     */
    static void processFile(const std::string& filePath)
    {
        if (filePath.empty()) return;

        students = readStudents("storage/" + filePath);
        SortingType selectedSortingType = promptUserForSortingType();

        performSortByField(selectedSortingType);
        renderFileSorterMenu();

        std::ofstream outFile("storage/" + filePath);
        if (!outFile.is_open()) {
            Utils::notificationWindow("FILE OPENING ERROR", 61, 9, 30, 10);
            renderFileSorterMenu();
            return;
        }

        for (const auto& student : students)
            writeStudent(outFile, student);

        outFile.close();
        students.clear();
    }

    /**
     * @brief Connects all file-related buttons with corresponding actions.
     */
    static void connectFileButtons()
    {
        fileSlider::upFile.connect([&]() {
            fileSlider::moveSlidingFileWindowUp();
            fileSlider::updateFileButtonNames();
            });

        fileSlider::file1.connect([&]() { processFile(fileSlider::getFileName(fileSlider::slidingFileWindow[0])); });
        fileSlider::file2.connect([&]() { processFile(fileSlider::getFileName(fileSlider::slidingFileWindow[1])); });
        fileSlider::file3.connect([&]() { processFile(fileSlider::getFileName(fileSlider::slidingFileWindow[2])); });
        fileSlider::file4.connect([&]() { processFile(fileSlider::getFileName(fileSlider::slidingFileWindow[3])); });
        fileSlider::file5.connect([&]() { processFile(fileSlider::getFileName(fileSlider::slidingFileWindow[4])); });

        fileSlider::downFile.connect([&]() {
            fileSlider::moveSlidingFileWindowDown();
            fileSlider::updateFileButtonNames();
            });

        backButton.connect([&]() {
            isFileSorterMenuActive = false;
            });
    }

    /**
     * @brief Sets up and starts the file sorter menu.
     */
    void setupFileSorterMenu()
    {
        isFileSorterMenuActive = true;

        fileSlider::setupSlidingFileWindow();
        initializeFileButtons();
        setupFileButtons();
        connectFileButtons();
        renderFileSorterMenu();
        setupInputHandling();
    }

    /**
     * @brief Main function for running the file sorter menu.
     *
     * @param sortMethod The sorting method to be applied.
     */
    void fileSorterMenu(SortingMethod sortMethod)
    {
        currentSortingMethod = sortMethod;
        setupFileSorterMenu();

        while (isFileSorterMenuActive)
        {
            mouseButtonInteraction(&fileSlider::upFile,
                &fileSlider::file1, 
                &fileSlider::file2, 
                &fileSlider::file3, 
                &fileSlider::file4, 
                &fileSlider::file5, 
                &fileSlider::downFile, 
                &backButton);
        }
    }

} // namespace database
