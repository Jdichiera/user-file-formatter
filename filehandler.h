#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <string>

class FileHandler
{
public:
	FileHandler();
	~FileHandler();

	void setInputFile(std::string path);
	void setOutputFile(std::string path);
	void setLogFile(std::string path);
	void setOrganizationFile(std::string path);
	void addLogData(std::string logData, int rowNumber);

	void setDelimiter(char delimiter);

	std::string getInputFile();
	std::string getOutputFile();
	std::string getLogFile();
	std::string getOrganizationFile();

	void splitString(const std::string& string, std::vector<std::string>& vector);

	std::vector<std::vector<std::string>> readFile();

	void writeContentToFile(std::string content);
	void writeContentToLog(std::string content, int row = -1);
	void writeLogDataToLog();

	void openReadFile();
	void closeReadFile();

	void openWriteFile();
	void closeWriteFile();

	void openLogFile();
	void closeLogFile();

	void openOrganizationFile();
	void closeOrganizationFile();

	bool validateColumns(std::string line, int lineNumber);
	bool validateContent(std::vector<std::string> record, int lineNumber);
	void vaidateFormatOrganizations(std::vector<std::string>& orgList, int lineNumber);

	void readOrganizationFileIntoKeyVector();
	bool findOrganizationInKeyVector(std::string orginization);

	std::string getTimestamp();

	//void readOrganizationFileIntoString();
	// void readOrganizationFileIntoVector();

	//bool checkOrgInList(std::string org);
	//std::string addLeadingZeroes(std::string org);

	// Org Search Functions
	// bool findOrgInVector(std::string org);
	// Naive search
	//bool naiveOrgSearch(std::string org, std::string orgList);

private:
	std::string m_inputFile;
	std::string m_outputFile;
	std::string m_logFile;
	std::string m_organizationFile;

	std::vector<std::vector<std::string>> m_logData;

	char m_delimiter;

	std::ifstream m_inputFileReader;
	std::ifstream m_organizationFileReader;

	std::ofstream m_outputFileWriter;
	std::ofstream m_logFileWriter;
	std::vector<std::vector<std::string>> m_vectorKeyOrgList;

	//std::string m_stringOrglist;
	//std::vector<std::string> m_vectorOrglist;

};
#endif // !FILEHANDLER_H



