#include "filehandler.h"

FileHandler::FileHandler()
{
}

FileHandler::~FileHandler()
{
}

void FileHandler::setInputFile(std::string path)
{
	m_inputFile = path;
}

void FileHandler::setOrganizationFile(std::string path)
{
	m_organizationFile = path;
}

void FileHandler::setOutputFile(std::string path)
{
	m_outputFile = path;
}

void FileHandler::setLogFile(std::string path)
{
	m_logFile = path;
}

void FileHandler::setDelimiter(char delimiter)
{
	m_delimiter = delimiter;
}

void FileHandler::addLogData(std::string logData, int rowNumber)
{
	// TODO : Maybe we can push in a type for the error so we can format correctly
	std::string formattedLogData = getTimestamp() + logData;
	formattedLogData += getTimestamp();
	if (rowNumber != -1) {
		formattedLogData += "[ROW : " + std::to_string(rowNumber) + "] ";
	}
	formattedLogData += logData;
	//m_logData.push_back(formattedLogData);
}

std::string FileHandler::getInputFile()
{
	return m_inputFile;
}

std::string FileHandler::getOutputFile()
{
	return m_outputFile;
}

std::string FileHandler::getLogFile()
{
	return m_logFile;
}

std::string FileHandler::getOrganizationFile()
{
	return m_organizationFile;
}

void FileHandler::splitString(const std::string & string, std::vector<std::string>& vector)
{
	/*
	 This method will break a string into separate tokens and save them to a vector.
	 Tokens are identified by two markers. The token begins at marker 'tokenBegin' 
	 and ends at marker 'tokenEnd' When the ending token, j, is at the end of the 
	 line ( == npos) then the remainder of the text in the string is pushed into the vector
	*/
	
	vector.clear();

	// Token begin position marker is set to 0 initially
	std::string::size_type tokenBegin = 0;

	// Token end position marker is set to the first instance of the delimiter
	std::string::size_type tokenEnd = string.find(m_delimiter);

	// While the token end iterator is not npos
	while (tokenEnd != std::string::npos) {
		// Push the current token onto the vector. In the first pass this would be 
		// the token at position 0 through the position of the delimiter - 1.
		vector.push_back(string.substr(tokenBegin, tokenEnd - tokenBegin));

		// Set the token begin position marker to the character immediately after 
		// the current token end position marker
		tokenBegin = ++tokenEnd;

		// Find the next delimiter and set the token end position marker to that position
		tokenEnd = string.find(m_delimiter, tokenEnd);

		// If the token end position marker is at npos (there are no more delimiters)
		// then we push any remaining text to the vector
		if (tokenEnd == std::string::npos) {
			vector.push_back(string.substr(tokenBegin, string.length()));
		}
	}
}

std::vector<std::vector<std::string>> FileHandler::readFile()
{
	/*
		This method reads the data in the CSV file. Each line in the file is read 
		separately and split into a collection of substrings. Each collection of 
		substrings is stored in another vector of 
	*/
	int recordsRead = 1;
	int recordsProcessed = 0;
	int recordsError = 0;
	writeContentToLog("-Reading records ...");
	std::vector<std::vector<std::string>> fileData;
	std::string line;
	std::vector<std::string> lineData;

	while (getline(m_inputFileReader, line)) {
		if (validateColumns(line, recordsRead)) {
			splitString(line, lineData);
			if (validateContent(lineData, recordsRead)) {
				//lineData[4] = validateFormatOrgs(lineData[4], recordsRead);
				fileData.push_back(lineData);
				recordsProcessed++;
			}
			else {
				recordsError++;
			}
		}
		else {
			recordsError++;
		}
		recordsRead++;
	}
	writeContentToLog("-Reading complete! Read: " + std::to_string(recordsRead) + " records || " + std::to_string(recordsProcessed) + " records processed. " + std::to_string(recordsError) + " records had errors and were skipped");
	return fileData;
}

std::string FileHandler::getTimestamp()
{
	std::string timestamp;
	std::ostringstream stringStream;
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	stringStream << "[" << std::put_time(&localTime, "%c") << "] ";
	timestamp = stringStream.str();
	return timestamp;
}

void FileHandler::writeContentToFile(std::string content)
{
	m_outputFileWriter << content << std::endl;
}

void FileHandler::writeContentToLog(std::string content, int row)
{
	// TODO : Make list of errors so they are not generated from working function
	// TODO : Instad of calling the log file multiple times, can we just make a vector of 
	// strings and write it all at once?

	std::string contentToWrite;
	contentToWrite += getTimestamp();
	if (row != -1) {
		contentToWrite += "[ROW : " + std::to_string(row) + "] ";
	}
	contentToWrite += content;
	m_logFileWriter << contentToWrite << std::endl;
}

void FileHandler::writeLogDataToLog(){
	//m_logFileWriter.open();
	openLogFile();
	for(auto line : m_logData){
		//m_logFileWriter << line << std::endl;
	}
	closeLogFile();
	//m_logFileWriter.close();
}

void FileHandler::openReadFile()
{
	m_inputFileReader.open(m_inputFile);
	if (!m_inputFileReader) {
		writeContentToLog("-could not open file" + m_inputFile);
	}
	else {
		writeContentToLog("-file opened");

	}
}

void FileHandler::closeReadFile()
{
	m_inputFileReader.close();
}

void FileHandler::openWriteFile()
{
	m_outputFileWriter.open(m_outputFile);
	if (!m_outputFileWriter) {
		writeContentToLog("-could not open file" + m_outputFile);
	}
	else {
		writeContentToLog("-file opened");
	}
}

void FileHandler::closeWriteFile()
{
	m_outputFileWriter.close();
}

void FileHandler::openLogFile()
{
	m_logFileWriter.open(m_logFile, std::ios_base::app);
}

void FileHandler::closeLogFile()
{
	m_logFileWriter.close();
}

void FileHandler::openOrganizationFile()
{
	m_organizationFileReader.open(m_organizationFile);
	if (!m_organizationFileReader) {
		writeContentToLog("-could not open file" + m_organizationFile);
	}
	else {
		writeContentToLog("-file opened");

	}
}

void FileHandler::closeOrganizationFile()
{
	m_organizationFileReader.close();
}

void FileHandler::readOrganizationFileIntoKeyVector()
{
	// TODO : Set up vector of keys move this to its own function or init
	std::vector<std::string> tempVectorEntry(NULL);
	for (int i = 0; i < 10; i++) {
		m_vectorKeyOrgList.push_back(tempVectorEntry);
	}
	std::string line;
	int key;
	openOrganizationFile();
	while (getline(m_organizationFileReader, line)) {
		key = std::stoi(line.substr(0,1));
		m_vectorKeyOrgList[key].push_back(line);
	}
	closeOrganizationFile();
}

bool FileHandler::validateColumns(std::string line, int lineNumber)
{
	bool validColumns = false;
	size_t columnCount = std::count(line.begin(), line.end(), m_delimiter);

	if (columnCount == 4) {
		validColumns = true;
	}
	else{
		writeContentToLog("---[ERROR]--- Invalid number of columns - Columns [" + std::to_string(columnCount) + "] - record skipped", lineNumber);
	}

	return validColumns;
}

bool FileHandler::validateContent(std::vector<std::string> record, int lineNumber)
{
	bool validContent = true;
	int column = 1;
	for (auto string : record) {
		if (string.empty()) {
			writeContentToLog("---[ERROR]--- No data in column Column [" + std::to_string(column) + "] - record skipped", lineNumber );
			validContent = false;
		}
		column++;
	}
	return validContent;
}

void FileHandler::vaidateFormatOrganizations(std::vector<std::string>& orgList, int lineNumber)
{
	std::cout << "\nvalidateFormatOrganizations" << std::endl;
	// TODO : Try to match the org to an org on the list. If the org cannot be found, note and reject. Also
	// I think we are checking for org length and stuff here too so we should move that to a central location.
	for (int i = 0; i < orgList.size(); i++) {
		if (orgList[i].empty()) {
			//writeContentToLog("[ERROR] - empty org - removing from list" - lineNumber);
			orgList[i] = "DEL";
		}
		else if (orgList[i] == "0") {
			//writeContentToLog("[ERROR] - org listed as '0' - removing from list", lineNumber);
			orgList[i] = "DEL";
		}
		else if (orgList[i].length() != 9 && orgList[i] != "0") {
			// The smallest org I see on the ORG list would be 6 characters long if all leading zeroes were dropped
			// If an org is under 5 digits long we can assume that it is an error and will need to be manually adjusted
			if (orgList[i].length() <= 5) {
				//writeContentToLog("[ERROR] - Org digit length 5 or less - please verify org and manually update. Org: " + orgList[i], lineNumber);
			}
			else {
				// The org is 6 digits long and may have had the leading zeroes stripped
				// Add the leading zeroes and continue.
				//writeContentToLog("[ERROR] - Org digit length 6 or more - leading zeroes may have been stripped - Adding zeroes - Org: " + orgList[i], lineNumber);
				//orgList[i] = addLeadingZeroes(orgList[i]);
			}
			//}
			//else {
			//writeContentToLog("[ERROR] - Adding leading zeroes - org updated from " + orgList[i] + " to : " + addLeadingZeroes(orgList[i]), lineNumber);
				//orgList[i] = addLeadingZeroes(orgList[i]);
			//}
		}
		else {
			// org is fine, make sure the org appears in the vector
			//std::cout << "ORG is not blank, '0', or short. Searching for org is vector." << std::endl;
			//std::cout << "\t\tORG: " << orgList[i] << std::endl;
			//findOrgInVector(orgList[i]);
			findOrganizationInKeyVector(orgList[i]);
		}
		orgList.erase(remove(orgList.begin(), orgList.end(), "DEL"), orgList.end());
	}
}

bool FileHandler::findOrganizationInKeyVector(std::string orginization)
{
	bool organizationFound = false;
	int key;
	key = std::stoi(orginization.substr(0, 1));
	//std::vector<std::string> subVector = m_vector
	for (auto entry : m_vectorKeyOrgList[key]) {
		if (orginization == entry) {
			organizationFound = true;
			break;
		}
	}
	return organizationFound;
}