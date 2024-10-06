#include "RemoveMenu.h"
#include <cstdio>

#include "../../consoleGUI/GUI.h"
#include "../global.h"
#include "../Utils.h"
#include "../Widgets/FileSlider.h"

using namespace widgets;

namespace database
{
	/** @brief Renders the remove file menu. */
	static void renderRemoveFileMenu();

	// Static button declarations
	static PushButton back;

	static bool runEditFileMenu = false;

	/** @brief Creates the file selection buttons. */
	static void createFilesButtons()
	{
		fileSlider::createFilesButtons(36, 5);
		back = PushButton(20, 5, "BACK", 65, 21);
	}

	/** @brief Sets up colors for the file buttons. */
	static void setupFilesButton()
	{
		fileSlider::setupFileButtons();

		back.setBackgroundColor(White);
		back.setForegroundColor(Black);
	}

	/** @brief Deletes a specified file after user confirmation.
	 *  @param path The path of the file to delete.
	 */
	static void workWithFile(const std::string& path)
	{
		if (path.empty())
			return;

		std::string prompt = "DO YOU DEFINITELY WANT TO DELETE THE FILE " + path + "?";
		if (Utils::confirmDialog(prompt, 61, 9, 30, 10))
		{
			auto it = std::find(mainDirectory.begin(), mainDirectory.end(), path);
			if (it != mainDirectory.end())
			{
				std::string pathCopy = path;

				mainDirectory.erase(it);

				std::string filename = "storage/" + pathCopy;
				if (std::remove(filename.c_str()) == 0) {
					Utils::notificationWindow("FILE SUCCESSFULLY DELETED", 61, 9, 30, 10);
				}
				else {
					Utils::applicationErrorWindow("ERROR DELETING FILE", 61, 9, 30, 10);
				}
			}
		}

		Utils::saveFiles(pathToFileStorage, mainDirectory);
		fileSlider::setupSlidingFileWindow();
		fileSlider::updateFileButtonNames();
		Utils::paintOverBackground();
		renderRemoveFileMenu();
		setupInputHandling();
	}

	/** @brief Connects the button actions for file operations. */
	static void connectFilesButtons()
	{
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

		back.connect([&]() {
			runEditFileMenu = false;
			});
	}

	/** @brief Renders the message for the remove file menu. */
	static void renderRemoveFileMenuMessage()
	{
		Window msgFrame(25, 9, 63, 4);
		msgFrame.addWindowName("MSG", 9, 0);
		msgFrame.show();

		setcur(68, 6); std::cout << char(250) << ' ' << "SELECT THE";
		setcur(70, 8); std::cout << "FILE TO BE";
		setcur(70, 10); std::cout << "DELETED";
	}

	/** @brief Renders the entire remove file menu interface. */
	static void renderRemoveFileMenu()
	{
		renderRemoveFileMenuMessage();

		fileSlider::renderFileSlider(35, 4);
		back.allowChanges(); back.show();
	}

	/** @brief Sets up the remove file menu and initializes the state. */
	static void setupRemoveFileMenu()
	{
		runEditFileMenu = true;

		fileSlider::setupSlidingFileWindow();

		createFilesButtons();
		setupFilesButton();
		connectFilesButtons();

		renderRemoveFileMenu();

		setupInputHandling();
		invisibleCursor();
	}

	/** @brief Main function to display the remove file menu. */
	void removeFileMenu()
	{
		setupRemoveFileMenu();

		while (runEditFileMenu)
		{
			mouseButtonInteraction(&fileSlider::upFile, &fileSlider::file1,
				&fileSlider::file2, &fileSlider::file3,
				&fileSlider::file4, &fileSlider::file5,
				&fileSlider::downFile, &back);
		}
	}

} // namespace database
