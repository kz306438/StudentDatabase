#include "SortMenu.h"
#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"
#include "FileSorterMenu.h"

namespace database
{
    static PushButton sortBySurnameButton,
        sortByAverageGradeButton,
        sortByAveragePhisicsGrade,
        sortByAverageMathGrade,
        sortByAverageInformGrade,
        back;

    bool runSortMenu = false;

    /** @brief Creates the sorting buttons. */
    static void createButtons()
    {
        sortBySurnameButton = PushButton(30, 3, "SORT BY SURNAME", 45, 4);
        sortByAverageGradeButton = PushButton(30, 3, "SORT BY GPA", 45, 8);
        sortByAveragePhisicsGrade = PushButton(30, 3, "SORT BY PHISICS GPA", 45, 12);
        sortByAverageMathGrade = PushButton(30, 3, "SORT BY MATH GPA", 45, 16);
        sortByAverageInformGrade = PushButton(30, 3, "SORT BY CS GPA", 45, 20);
        back = PushButton(30, 3, "BACK", 45, 24);
    }

    /** @brief Sets button colors.
      * @param button The button to set colors for.
      * @param bgColor The background color for the button.
      * @param fgColor The foreground color for the button.
      */
    static void setupButtonColors(PushButton& button, ConsoleColor bgColor, ConsoleColor fgColor)
    {
        button.setBackgroundColor(bgColor);
        button.setForegroundColor(fgColor);
    }

    /** @brief Configures colors for all sorting buttons. */
    static void setupButtons()
    {
        setupButtonColors(sortBySurnameButton, White, Black);
        setupButtonColors(sortByAverageGradeButton, White, Black);
        setupButtonColors(sortByAveragePhisicsGrade, White, Black);
        setupButtonColors(sortByAverageMathGrade, White, Black);
        setupButtonColors(sortByAverageInformGrade, White, Black);
        setupButtonColors(back, BrightRed, Black);
    }

    /** @brief Displays a message window for user instructions. */
    static void printMSG()
    {
        Window msg(20, 7, 80, 4);
        msg.addWindowName("msg", 1, 0);
        msg.show();

        setcur(87, 5); std::cout << "SELECT";
        setcur(88, 7); std::cout << "SORT";
        setcur(87, 9); std::cout << "METHOD!";
    }

    /** @brief Renders the sorting menu. */
    static void renderSortMenu()
    {
        Utils::paintOverBackground();
        printMSG();

        sortBySurnameButton.allowChanges();              sortBySurnameButton.show();
        sortByAverageGradeButton.allowChanges();         sortByAverageGradeButton.show();
        sortByAveragePhisicsGrade.allowChanges();       sortByAveragePhisicsGrade.show();
        sortByAverageMathGrade.allowChanges();           sortByAverageMathGrade.show();
        sortByAverageInformGrade.allowChanges();         sortByAverageInformGrade.show();
        back.allowChanges();                              back.show();
    }

    /** @brief Processes sorting based on the selected method.
      * @param sortingMethod The method used for sorting.
      */
    static void workWithSort(SortingMethod sortingMethod)
    {
        Utils::paintOverBackground();
        fileSorterMenu(sortingMethod);
        Utils::paintOverBackground();
        renderSortMenu();
        setupInputHandling();
    }

    /** @brief Connects button actions to their corresponding sorting methods. */
    static void connectButtons()
    {
        sortBySurnameButton.connect([&]() { workWithSort(SortBySurname); });
        sortByAverageGradeButton.connect([&]() { workWithSort(SortByAverageGrade); });
        sortByAveragePhisicsGrade.connect([&]() { workWithSort(SortByAveragePhisicsGrade); });
        sortByAverageMathGrade.connect([&]() { workWithSort(SortByAverageMathGrade); });
        sortByAverageInformGrade.connect([&]() { workWithSort(SortByAverageInformGrade); });
        back.connect([&]() { runSortMenu = false; });
    }

    /** @brief Initializes the sorting menu and its components. */
    static void setupSortMenu()
    {
        runSortMenu = true;
        printMSG();
        createButtons();
        setupButtons();
        connectButtons();
        setupInputHandling();
        invisibleCursor();
    }

    /** @brief Displays the sorting menu and handles user interaction. */
    void sortMenu()
    {
        setupSortMenu();

        while (runSortMenu)
        {
            mouseButtonInteraction(&sortBySurnameButton,
                &sortByAverageGradeButton,
                &sortByAveragePhisicsGrade,
                &sortByAverageMathGrade,
                &sortByAverageInformGrade,
                &back);
        }
    }

} // namespace database