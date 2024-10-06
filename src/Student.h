#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

namespace database
{

	struct Student
	{
		std::string surname{};

		std::uint64_t groupNumber{};

		std::vector<std::uint16_t> phisicsScores{},
			mathScores{},
			informScores{};

		double averagePhisicsGrade{},
			averageMathGrade{},
			averageInformGrade{};

		double averageGrade{};
	};

	/**
	 * @brief Creates a new Student object by gathering input from the user.
	 * @return A Student object filled with user input.
	 */
	Student createStudent();

	/**
	 * @brief Writes a student's data to a specified output file.
	 * @param outFile Output file stream to write data to.
	 * @param student The student object containing data to write.
	 */
	void writeStudent(std::ofstream& outFile, const Student& student);

	/**
	 * @brief Reads student data from a file.
	 * @param filename Name of the file to read from.
	 * @return A vector containing Student objects read from the file.
	 */
	std::vector<Student> readStudents(const std::string& filename);

	/**
	 * @brief Calculates the average grade of a given student based on their scores.
	 * @param student Reference to the student object whose average grade is calculated.
	 */
	void calculateAverageGrade(Student& student);

	/**
	 * @brief Calculates the average value of a given set of marks.
	 * @param marks A vector of marks to calculate the average from.
	 * @return The average value of the marks.
	 */
	double calculateAverageValue(const std::vector<std::uint16_t>& marks);

	/**
	 * @brief Inputs grades for a specific subject into the provided vector.
	 * @param grade A reference to the vector where grades will be stored.
	 * @param length The number of grades to input.
	 */
	void inputAllGradesForSubject(std::vector<uint16_t>& grade, std::size_t length);

	/**
	 * @brief Checks if the given size is valid (non-negative).
	 * @param size The size to check.
	 * @return True if size is valid, false otherwise.
	 */
	bool checkArraySize(const int& size);

} // database

#endif // STUDENT_H
