#include "EditMenu.h"

#include <vector>
#include <string>

#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"

#include "../Widgets/FileSlider.h"
#include "../Widgets/EditBox.h"

using namespace widgets;

namespace database
{
	// Static variables and functions, only accessible within this file
	static PushButton backButton;
	static bool runEditFileMenuFlag = false;

	/**
	 * @brief Initializes and configures the file buttons.
	 * This function sets up buttons for file selection and configures their visual appearance.
	 */
	static void initializeFileButtons()
	{
		fileSlider::createFilesButtons(36, 5);
		backButton = PushButton(20, 5, "BACK", 65, 21);
		backButton.setBackgroundColor(White);
		backButton.setForegroundColor(Black);
	}

	/**
	 * @brief Displays the message for file selection in the edit file menu.
	 * This function creates a window that prompts the user to select a file for editing.
	 */
	static void displayEditFileMessage()
	{
		Window msgFrame(25, 9, 63, 4);
		msgFrame.addWindowName("MSG", 9, 0);
		msgFrame.show();

		setcur(68, 6); std::cout << char(250) << ' ' << "SELECT THE";
		setcur(70, 8); std::cout << "FILE TO";
		setcur(70, 10); std::cout << "BE EDIT";
	}

	/**
	 * @brief Displays a message to instruct the user on how to exit the file edit menu.
	 * This function renders a message instructing the user to press "ESCAPE" to exit.
	 */
	static void displayExitMessage()
	{
		Window msgFrame(20, 9, 10, 4);
		msgFrame.addWindowName("MSG", 7, 0);
		msgFrame.show();

		setcur(14, 6); std::cout << char(250) << ' ' << "TO EXIT";
		setcur(16, 8); std::cout << "PRESS KEY";
		setcur(16, 10); std::cout << "ESCAPE";
	}

	/**
	 * @brief Renders the file editing menu interface.
	 * This function calls necessary methods to display the file editing menu,
	 * including file slider and back button.
	 */
	static void renderFileMenu()
	{
		displayEditFileMessage();
		fileSlider::renderFileSlider(35, 4);
		backButton.allowChanges();
		backButton.show();
	}

	/**
	 * @brief Handles file editing based on the selected file path.
	 * This function opens the selected file for editing and handles
	 * the save operation if the user confirms.
	 *
	 * @param path The path of the file to be edited.
	 */
	static void handleFile(const std::string& path)
	{
		if (path.empty()) return;

		Utils::paintOverBackground();
		setupInputHandling();

		displayExitMessage();
		editBox::setup(path);
		editBox::handleEditBox();

		if (Utils::confirmDialog("SAVE THE CHANGES?", 65, 9, 27, 10))
		{
			editBox::saveChanges("storage/" + path);
		}

		Utils::paintOverBackground();
		renderFileMenu();
		setupInputHandling();
	}

	/**
	 * @brief Connects button actions to their respective event handlers.
	 * This function sets up the interaction logic for each button, linking
	 * file navigation and selection buttons to their respective actions.
	 */
	static void connectFileButtons()
	{
		fileSlider::upFile.connect([&]() {
			fileSlider::moveSlidingFileWindowUp();
			fileSlider::updateFileButtonNames();
			});

		fileSlider::file1.connect([&]() {
			handleFile(fileSlider::getFileName(fileSlider::slidingFileWindow[0]));
			});

		fileSlider::file2.connect([&]() {
			handleFile(fileSlider::getFileName(fileSlider::slidingFileWindow[1]));
			});

		fileSlider::file3.connect([&]() {
			handleFile(fileSlider::getFileName(fileSlider::slidingFileWindow[2]));
			});

		fileSlider::file4.connect([&]() {
			handleFile(fileSlider::getFileName(fileSlider::slidingFileWindow[3]));
			});

		fileSlider::file5.connect([&]() {
			handleFile(fileSlider::getFileName(fileSlider::slidingFileWindow[4]));
			});

		fileSlider::downFile.connect([&]() {
			fileSlider::moveSlidingFileWindowDown();
			fileSlider::updateFileButtonNames();
			});

		backButton.connect([&]() {
			runEditFileMenuFlag = false;
			});
	}

	/**
	 * @brief Sets up the file editing menu.
	 * This function prepares the menu interface, initializes buttons, and
	 * connects button interactions before entering the main loop.
	 */
	static void setupEditFileMenu()
	{
		runEditFileMenuFlag = true;
		fileSlider::setupSlidingFileWindow();

		initializeFileButtons();
		connectFileButtons();
		fileSlider::setupFileButtons();
		renderFileMenu();

		setupInputHandling();
		invisibleCursor();
	}

	/**
	 * @brief Entry point to run the file editing menu.
	 * This function runs the main loop for the file editing menu, processing
	 * user interactions until the back button is pressed.
	 */
	void editFileMenu()
	{
		setupEditFileMenu();

		while (runEditFileMenuFlag)
		{
			mouseButtonInteraction(&fileSlider::upFile, &fileSlider::file1,
				&fileSlider::file2, &fileSlider::file3,
				&fileSlider::file4, &fileSlider::file5,
				&fileSlider::downFile, &backButton);
		}
	}

} // namespace database
