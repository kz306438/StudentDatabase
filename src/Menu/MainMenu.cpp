#include "MainMenu.h"

#include "../../consoleGUI/GUI.h"
#include "../Utils.h"
#include "../global.h"

#include "CreateFileMenu.h"
#include "AddFileMenu.h"
#include "ViewFileMenu.h"
#include "SortMenu.h"
#include "RemoveMenu.h"
#include "IndividTaskMenu.h"
#include "EditMenu.h"

namespace database
{
	// Struct to hold all buttons in the main menu
	struct Buttons
	{
		PushButton createFile;      // Button to create a file
		PushButton viewFile;        // Button to view a file
		PushButton addToFile;       // Button to add to a file
		PushButton individualTask;   // Button for individual tasks
		PushButton editFile;        // Button to edit a file
		PushButton removeFile;      // Button to remove a file
		PushButton sort;            // Button to sort files
		PushButton quit;            // Button to quit the application
	};

	/**
	 * @brief Renders all buttons in the main menu.
	 *
	 * @param buttons Reference to the Buttons struct containing all menu buttons.
	 */
	void render(Buttons& buttons)
	{
		Utils::printLogo(22, 3); // Print application logo

		// Allow changes and show each button
		buttons.createFile.allowChanges(); buttons.createFile.show();
		buttons.viewFile.allowChanges(); buttons.viewFile.show();
		buttons.addToFile.allowChanges(); buttons.addToFile.show();
		buttons.individualTask.allowChanges(); buttons.individualTask.show();
		buttons.editFile.allowChanges(); buttons.editFile.show();
		buttons.removeFile.allowChanges(); buttons.removeFile.show();
		buttons.sort.allowChanges(); buttons.sort.show();
		buttons.quit.allowChanges(); buttons.quit.show();
	}

	/**
	 * @brief Creates and initializes all buttons in the main menu.
	 *
	 * @param buttons Reference to the Buttons struct to populate with button instances.
	 */
	void createButtons(Buttons& buttons)
	{
		// Initialize each button with its position and label
		buttons.createFile = PushButton(20, 5, "CREATE FILE", 10, 15);
		buttons.viewFile = PushButton(20, 5, "VIEW FILE", 35, 15);
		buttons.addToFile = PushButton(20, 5, "ADD TO FILE", 60, 15);
		buttons.individualTask = PushButton(20, 5, "INDIVIDUAL TASK", 85, 15);
		buttons.editFile = PushButton(20, 5, "EDIT FILE", 10, 22);
		buttons.removeFile = PushButton(20, 5, "REMOVE FILE", 35, 22);
		buttons.sort = PushButton(20, 5, "SORT", 60, 22);
		buttons.quit = PushButton(20, 5, "QUIT", 85, 22);
	}

	/**
	 * @brief Sets up the background and foreground colors for all buttons.
	 *
	 * @param buttons Reference to the Buttons struct to configure button colors.
	 */
	void setupButtonsColors(Buttons& buttons)
	{
		// Set background and foreground colors for each button
		buttons.createFile.setBackgroundColor(White);
		buttons.createFile.setForegroundColor(Black);
		buttons.viewFile.setBackgroundColor(White);
		buttons.viewFile.setForegroundColor(Black);
		buttons.addToFile.setBackgroundColor(White);
		buttons.addToFile.setForegroundColor(Black);
		buttons.individualTask.setBackgroundColor(White);
		buttons.individualTask.setForegroundColor(Black);
		buttons.editFile.setBackgroundColor(White);
		buttons.editFile.setForegroundColor(Black);
		buttons.removeFile.setBackgroundColor(White);
		buttons.removeFile.setForegroundColor(Black);
		buttons.sort.setBackgroundColor(White);
		buttons.sort.setForegroundColor(Black);
		buttons.quit.setBackgroundColor(White);
		buttons.quit.setForegroundColor(Black);
	}

	/**
	 * @brief Connects each button to its respective action.
	 *
	 * @param buttons Reference to the Buttons struct to set up button actions.
	 */
	void connectButtons(Buttons& buttons)
	{
		// Connect actions for creating a file
		buttons.createFile.connect([&]() {
			Utils::paintOverBackground();
			createFileMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for viewing a file
		buttons.viewFile.connect([&]() {
			Utils::paintOverBackground();
			viewFileMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for adding to a file
		buttons.addToFile.connect([&]() {
			Utils::paintOverBackground();
			addFileMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for individual tasks
		buttons.individualTask.connect([&]() {
			Utils::paintOverBackground();
			individualTaskMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for editing a file
		buttons.editFile.connect([&]() {
			Utils::paintOverBackground();
			editFileMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for removing a file
		buttons.removeFile.connect([&]() {
			Utils::paintOverBackground();
			removeFileMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for sorting files
		buttons.sort.connect([&]() {
			Utils::paintOverBackground();
			sortMenu();
			Utils::paintOverBackground();
			setupInputHandling();
			render(buttons);
			});

		// Connect actions for quitting the application
		buttons.quit.connect([&]() {
			if (Utils::confirmDialog("ARE YOU SURE YOU WANT EXIT?", 61, 9, 30, 10)) {
				Utils::saveFiles(pathToFileStorage, mainDirectory);
				exit(0); // Exit the application
			}
			else
			{
				Utils::paintOverBackground();
				setupInputHandling();
				render(buttons);
			}
			});
	}

	/**
	 * @brief Main function that sets up and displays the main menu.
	 */
	void mainMenu()
	{
		Buttons buttons; // Create buttons struct

		createButtons(buttons); // Initialize buttons
		connectButtons(buttons); // Connect button actions
		setupButtonsColors(buttons); // Set button colors

		Utils::paintOverBackground(); // Clear background
		render(buttons); // Render the buttons

		invisibleCursor(); // Hide cursor for better UI experience
		setupInputHandling(); // Prepare input handling

		// Main loop for menu interaction
		while (true)
		{
			mouseButtonInteraction(
				&buttons.createFile,
				&buttons.viewFile,
				&buttons.addToFile,
				&buttons.individualTask,
				&buttons.editFile,
				&buttons.removeFile,
				&buttons.sort,
				&buttons.quit
			);
		}
	}

} // namespace database
