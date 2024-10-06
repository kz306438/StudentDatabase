#include "Student.h"

#include <fstream>
#include <sstream>

#include "Utils.h"
#include "../consoleGUI/GUI.h"

namespace database
{

	/**
	 * @brief Checks if the given size is valid (non-negative).
	 * @param size The size to check.
	 * @return True if size is valid, false otherwise.
	 */
	bool checkArraySize(const int& size)
	{
		if (size < 0)
		{
			std::cout << "THE NUMBER OF RATING CANNOT BE NEGATIVE!" << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}

	/**
	 * @brief Inputs grades for a specific subject into the provided vector.
	 * @param grade A reference to the vector where grades will be stored.
	 * @param length The number of grades to input.
	 */
	void inputAllGradesForSubject(std::vector<uint16_t>& grade, std::size_t length)
	{
		for (int i = 0; i < length; i++)
		{
			grade.push_back(0);

			std::string prompt = "ENTER " + std::to_string(i + 1) + "-GRADE:";
			Utils::inputValue(prompt, grade[i]);
		}
	}

	/**
	 * @brief Calculates the average value of a given set of marks.
	 * @param marks A vector of marks to calculate the average from.
	 * @return The average value of the marks.
	 */
	double calculateAverageValue(const std::vector<std::uint16_t>& marks)
	{
		std::size_t count = marks.size();
		std::uint16_t sum = 0;

		for (const auto& el : marks)
			sum += el;

		return sum / static_cast<double>(count);
	}

	/**
	 * @brief Calculates the average grade of a given student based on their scores.
	 * @param student Reference to the student object whose average grade is calculated.
	 */
	void calculateAverageGrade(Student& student)
	{
		int sumOfPhisicsGrades = 0;
		for (int i = 0; i < student.phisicsScores.size(); i++)
			sumOfPhisicsGrades += student.phisicsScores[i];

		int sumOfMathGrades = 0;
		for (int i = 0; i < student.mathScores.size(); i++)
			sumOfMathGrades += student.mathScores[i];

		int sumOfInformGrades = 0;
		for (int i = 0; i < student.informScores.size(); i++)
			sumOfInformGrades += student.informScores[i];

		double avgPhisics = static_cast<double>(sumOfPhisicsGrades) / student.phisicsScores.size();
		double avgMath = static_cast<double>(sumOfMathGrades) / student.mathScores.size();
		double avgInform = static_cast<double>(sumOfInformGrades) / student.informScores.size();

		student.averageGrade = (round(avgPhisics) + round(avgMath) + round(avgInform)) / 3;
	}

	/**
	 * @brief Writes a student's data to a specified output file.
	 * @param outFile Output file stream to write data to.
	 * @param student The student object containing data to write.
	 */
	void writeStudent(std::ofstream& outFile, const Student& student)
	{
		outFile << "STUDENT'S NAME: " << student.surname << std::endl;
		outFile << "GROUP NUMBER: " << student.groupNumber << std::endl;
		outFile << "PHYSICS SCORE: " << Utils::arrayToString(student.phisicsScores) << std::endl;
		outFile << "PHISICS GPA: " << student.averagePhisicsGrade << std::endl;
		outFile << "MATH SCORE: " << Utils::arrayToString(student.mathScores) << std::endl;
		outFile << "MATH GPA: " << student.averageMathGrade << std::endl;
		outFile << "CS SCORE: " << Utils::arrayToString(student.informScores) << std::endl;
		outFile << "CS GPA: " << student.averageInformGrade << std::endl;
		outFile << "GPA: " << student.averageGrade << std::endl;
	}

	/**
	 * @brief Creates a new Student object by gathering input from the user.
	 * @return A Student object filled with user input.
	 */
	Student createStudent()
	{
		Student student{};
		std::cout << "ENTER THE STUDENT'S LAST NAME:" << std::endl;
		getline(std::cin, student.surname);

		Utils::inputValue("ENTER THE STUDENT'S GROUP NUMBER:", student.groupNumber);

		int numOfPhisicsMarks{};
		Utils::inputValue("ENTER THE NUMBER OF MARKS IN PHYSICS:", numOfPhisicsMarks, checkArraySize);
		inputAllGradesForSubject(student.phisicsScores, numOfPhisicsMarks);
		student.averagePhisicsGrade = calculateAverageValue(student.phisicsScores);

		int numOfMathMarks{};
		Utils::inputValue("ENTER THE NUMBER OF MARKS IN MATH:", numOfMathMarks, checkArraySize);
		inputAllGradesForSubject(student.mathScores, numOfMathMarks);
		student.averageMathGrade = calculateAverageValue(student.mathScores);

		int numOfInformMarks{};
		Utils::inputValue("ENTER THE NUMBER OF MARKS IN COMPUTER SCIENCE:", numOfInformMarks, checkArraySize);
		inputAllGradesForSubject(student.informScores, numOfInformMarks);
		student.averageInformGrade = calculateAverageValue(student.informScores);

		calculateAverageGrade(student);

		Utils::eatline();

		return student;
	}

	/**
	 * @brief Parses a string into a vector of unsigned integers.
	 * @param str The string to parse.
	 * @return A vector containing the parsed unsigned integers.
	 */
	std::vector<uint16_t> parseArray(const std::string& str)
	{
		std::vector<uint16_t> array;
		std::stringstream ss(str);
		uint16_t number;

		while (ss >> number)
		{
			array.push_back(number);
		}
		return array;
	}

	/**
	 * @brief Reads a student's data from an input file stream.
	 * @param inFile Input file stream to read data from.
	 * @param student Reference to the student object to populate with data.
	 * @return True if the data was read successfully, false otherwise.
	 */
	bool readStudent(std::ifstream& inFile, Student& student)
	{
		std::string groupNumberStr, arrayStr, averageGradeStr, overallAverageGradeStr;

		if (getline(inFile, student.surname) &&
			getline(inFile, groupNumberStr) &&
			getline(inFile, arrayStr) &&
			getline(inFile, averageGradeStr)) {

			student.groupNumber = stoull(groupNumberStr);
			student.phisicsScores = parseArray(arrayStr);
			student.averagePhisicsGrade = stod(averageGradeStr);

			getline(inFile, arrayStr);
			getline(inFile, averageGradeStr);
			student.mathScores = parseArray(arrayStr);
			student.averageMathGrade = stod(averageGradeStr);

			getline(inFile, arrayStr);
			getline(inFile, averageGradeStr);
			student.informScores = parseArray(arrayStr);
			student.averageInformGrade = stod(averageGradeStr);

			getline(inFile, overallAverageGradeStr);
			student.averageGrade = stod(overallAverageGradeStr);

			return true;
		}
		return false;
	}

	/**
	 * @brief Reads multiple students' data from a specified file.
	 * @param filename Name of the file to read from.
	 * @return A vector of Student objects read from the file.
	 */
	std::vector<Student> readStudents(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
			Utils::applicationErrorWindow("ERROR OPENING FILE", 61, 9, 30, 10);

		std::vector<Student> students;
		std::string line;

		while (std::getline(file, line)) {
			if (line.find("STUDENT'S NAME:") != std::string::npos)
			{
				Student student;
				student.surname = line.substr(line.find(":") + 2);

				std::getline(file, line);
				student.groupNumber = std::stoull(line.substr(line.find(":") + 2));

				std::getline(file, line);
				std::istringstream phisicsStream(line.substr(line.find(":") + 2));
				std::uint16_t score;
				while (phisicsStream >> score) {
					student.phisicsScores.push_back(score);
				}

				std::getline(file, line);
				student.averagePhisicsGrade = std::stod(line.substr(line.find(":") + 2));

				std::getline(file, line);
				std::istringstream mathStream(line.substr(line.find(":") + 2));
				while (mathStream >> score) {
					student.mathScores.push_back(score);
				}

				std::getline(file, line);
				student.averageMathGrade = std::stod(line.substr(line.find(":") + 2));

				std::getline(file, line);
				std::istringstream informStream(line.substr(line.find(":") + 2));
				while (informStream >> score) {
					student.informScores.push_back(score);
				}

				std::getline(file, line);
				student.averageInformGrade = std::stod(line.substr(line.find(":") + 2));

				std::getline(file, line);
				student.averageGrade = std::stod(line.substr(line.find(":") + 2));

				students.push_back(student);
			}
		}

		return students;
	}

} // database
