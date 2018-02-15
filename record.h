#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <vector>
class Record
{
public:
	Record();
	~Record();

	void setRecordNumber(int recordNumber);
	void setInternalUsername(std::string internalUsername);
	void setFirstname(std::string firstname);
	void setLastname(std::string lastname);
	void setExternalUsername(std::string externalUsername);
	void setUserOrganization(std::string organization);

	int getRecordNumber();
	std::string getInternalUserame();
	std::string getFirstname();
	std::string getLastname();
	std::string getExternalUsername();
	std::string getUserOrganizationString();
	std::vector<std::string> getUserOrganization();

	void clear();
	void splitUserOrganizationToString(std::string userOrganizations);
	std::string toString();
	std::string addLeadingZeroesToOrganization(std::string organization);

private:
	int m_recordNumber;
	std::string m_internalUsername;
	std::string m_firstname;
	std::string m_lastname;
	std::string m_externalUsername;
	std::vector<std::string> m_userOrganizations;
};

#endif // !RECORD_H


