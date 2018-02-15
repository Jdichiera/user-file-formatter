#ifndef USERFILEFORMATTER_H
#define USERFILEFORMATTER_H
#include "record.h"
#include "filehandler.h"

class UserFileFormatter
{
public:
	UserFileFormatter();
	~UserFileFormatter();
	void setupFileHandler(std::string inputFile, std::string outputFile, std::string organizationFile, std::string logFile, char delimiter);
	void readCollectionFromFile();
	void writeCollectionToFile();
	void readOrganizationfile();
	std::string getTimestamp();

	
private:
	std::vector<Record> m_recordCollection;
	FileHandler m_filehandler;
};


#endif // !USERFILEFORMATTER



