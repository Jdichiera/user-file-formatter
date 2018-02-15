#include "userfileformatter.h"
#include "timer.h"


int main() {
	std::string inputFile = "Z:\\Users\\udichje\\Repo\\user-file-formatter\\x64\\Debug\\input.csv";
	std::string outputFile = "Z:\\Users\\udichje\\Repo\\user-file-formatter\\x64\\Debug\\output.csv";
	std::string organizationFile = "Z:\\Users\\udichje\\Repo\\user-file-formatter\\x64\\Debug\\mnorgDataOutput.txt";
	std::string logFile = "Z:\\Users\\udichje\\Repo\\user-file-formatter\\x64\\Debug\\log.csv";
	char delimiter = ',';
	UserFileFormatter userFileFormatter;
	Timer timer;
	timer.startTime();
	userFileFormatter.setupFileHandler(inputFile, outputFile, organizationFile, logFile, delimiter);
	userFileFormatter.readCollectionFromFile();
	//userFileFormatter.printCollection();
	userFileFormatter.writeCollectionToFile();
	timer.endTime();
	timer.getDuration();
	system("PAUSE");
	return 0;
}