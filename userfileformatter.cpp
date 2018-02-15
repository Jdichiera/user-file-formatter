#include "userfileformatter.h"



UserFileFormatter::UserFileFormatter()
{
}


UserFileFormatter::~UserFileFormatter()
{
}

void UserFileFormatter::setupFileHandler(std::string inputFile, std::string outputFile, 
											std::string organizationFile, std::string logFile, char delimiter)
{
	m_filehandler.setInputFile(inputFile);
	m_filehandler.setDelimiter(delimiter);
	m_filehandler.setOutputFile(outputFile);
	m_filehandler.setOrganizationFile(organizationFile);
	m_filehandler.setLogFile(logFile);
	//m_filehandler.readOrganizationFileIntoVector();
	m_filehandler.readOrganizationFileIntoKeyVector();
}

void UserFileFormatter::readCollectionFromFile()
{
	m_filehandler.openLogFile();
	m_filehandler.writeContentToLog("--==Reading file==--");
	
	Record tempRecord;
	int recordNumber = 1;

	m_filehandler.writeContentToLog("-Opening File: " + m_filehandler.getInputFile());
	m_filehandler.openReadFile();

	std::vector<std::vector<std::string>> fileData = m_filehandler.readFile();

	m_filehandler.writeContentToLog("-Creating record objects ...");
	for (auto record : fileData) {
		tempRecord.setRecordNumber(recordNumber);
		tempRecord.setInternalUsername(record[0]);
		tempRecord.setFirstname(record[1]);
		tempRecord.setLastname(record[2]);
		tempRecord.setExternalUsername(record[3]);
		tempRecord.setUserOrganization(record[4]);
		m_filehandler.vaidateFormatOrganizations(tempRecord.getUserOrganization(), recordNumber);
		m_recordCollection.push_back(tempRecord);
		tempRecord.clear();
		recordNumber++;
	}
	m_filehandler.writeContentToLog("-Created " + std::to_string(recordNumber) + " record objects");
	
	m_filehandler.writeContentToLog("-Closing File: " + m_filehandler.getInputFile());
	m_filehandler.closeReadFile();
	m_filehandler.writeContentToLog("--==Reading complete==--");
	m_filehandler.closeLogFile();
}


void UserFileFormatter::writeCollectionToFile()
{
	int recordNumber = 0;
	m_filehandler.openLogFile();
	m_filehandler.writeContentToLog("--==Writing file==--");

	m_filehandler.writeContentToLog("-Opening File: " + m_filehandler.getOutputFile());
	m_filehandler.openWriteFile();
	
	m_filehandler.writeContentToLog("-Writing records ...");
	for (auto record : m_recordCollection) {
		//std::cout << record.toString() << std::endl;
		m_filehandler.writeContentToFile(record.toString());
		recordNumber++;
	}
	m_filehandler.writeContentToLog("-Wrote " + std::to_string(recordNumber) + " records");

	m_filehandler.writeContentToLog("-Closing File: " + m_filehandler.getOutputFile());
	m_filehandler.closeWriteFile();
	m_filehandler.writeContentToLog("--==Writing complete==--");
	m_filehandler.closeLogFile();
}

//void UserFileFormatter::printCollection()
//{
//	for (auto record : m_recordCollection) {
//		record.print();
//	}
//}


// TODO : Do we need this?
void UserFileFormatter::readOrganizationfile()
{
	m_filehandler.readOrganizationFileIntoKeyVector();
}

std::string UserFileFormatter::getTimestamp()
{
	std::string timestamp;
	std::ostringstream stringStream;
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	stringStream << std::put_time(&localTime, "%c");
	timestamp = stringStream.str();
	std::cout << timestamp;
	return timestamp;
}


