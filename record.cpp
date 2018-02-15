#include "record.h"

Record::Record()
{
	m_recordNumber = 0;
	m_internalUsername;
	m_firstname;
	m_lastname;
	m_externalUsername;
	m_userOrganizations;
}

Record::~Record()
{
}


void Record::setRecordNumber(int recordNumber)
{
	m_recordNumber = recordNumber;
}

void Record::setInternalUsername(std::string internalUsername)
{
	m_internalUsername = internalUsername;
}

void Record::setFirstname(std::string firstname)
{
	m_firstname = firstname;
}

void Record::setLastname(std::string lastname)
{
	m_lastname = lastname;
}

void Record::setExternalUsername(std::string externalUsername)
{
	m_externalUsername = externalUsername;
}

void Record::setUserOrganization(std::string organization)
{
	/*
	 The user organization can either be a single organization or a formatted string.

	 If the organization passed in is over 9 characters then it must be a formatted 
	 string and it should be split before being added to the collection

	 The minimum number of characters present on a the current organization file is
	 6 characters. If the organization passed in is between 6 and 9 characters then
	 the leading zeroes were probably stripped off and it should be padded to 9 
	 characters before adding it to the list.
	*/
	if (organization.length() > 9) {
		splitUserOrganizationToString(organization);
	}
	else if ((organization.length() <= 9) && (organization.length() >=6)) {
		organization = addLeadingZeroesToOrganization(organization);
		m_userOrganizations.push_back(organization);
	}
}

int Record::getRecordNumber()
{
	return m_recordNumber;
}

std::string Record::getInternalUserame()
{
	return m_internalUsername;
}

std::string Record::getFirstname()
{
	return m_firstname;
}

std::string Record::getLastname()
{
	return m_lastname;
}

std::string Record::getExternalUsername()
{
	return m_externalUsername;
}

std::vector<std::string> Record::getUserOrganization()
{
	return m_userOrganizations;
}

std::string Record::getUserOrganizationString()
{
	// Returns the list of user organizations as a formatted string [org]:[org]:[org]
	std::string userOrganizationsString = "";
	for (int i = 0; i < m_userOrganizations.size(); i++) {
		userOrganizationsString += m_userOrganizations[i];
		if (i < m_userOrganizations.size() - 1) {
			userOrganizationsString += ":";
		}
	}
	return userOrganizationsString;
}

void Record::clear()
{
	// Initializes the record when we need to erase one
	m_recordNumber = -1;
	m_internalUsername.clear();
	m_firstname.clear();
	m_lastname.clear();
	m_externalUsername.clear();
	m_userOrganizations.clear();
}

void Record::splitUserOrganizationToString(std::string userOrganizationList)
{
	/*
	Splits a formatted string of user organizations into individual strings and
	adds them to the collection of user organizations.
	*/
	// TODO: Do we check for org lenght here? Dont we do it in another section?
	char delimiter = ':';
	std::string organization;
	std::string::size_type tokenBegin = 0;
	std::string::size_type tokenEnd = userOrganizationList.find(delimiter);

	while (tokenEnd != std::string::npos) {
		organization = userOrganizationList.substr(tokenBegin, tokenEnd - tokenBegin);
		if ((organization.length() < 9) && (organization.length() >= 6)) {
			organization = addLeadingZeroesToOrganization(organization);
		}
		setUserOrganization(organization);
		tokenBegin = ++tokenEnd;
		tokenEnd = userOrganizationList.find(delimiter, tokenEnd);

		if (tokenEnd == std::string::npos) {
			organization = userOrganizationList.substr(tokenBegin, userOrganizationList.length());
			if ((organization.length() < 9) && (organization.length() >= 6)) {
				organization = addLeadingZeroesToOrganization(organization);
			}
			setUserOrganization(organization);
		}
	}
}

std::string Record::toString()
{
	// Creates a formatted string of the record that can be written to the final csv file
	// TODO : Can we do this without calling functions?
	std::string record;
	record += getInternalUserame() + ",";
	record += getFirstname() + ",";
	record += getLastname() + ",";
	record += getExternalUsername() + ",";
	record += getUserOrganizationString();
	return record;
}

std::string Record::addLeadingZeroesToOrganization(std::string organization)
{
	std::string formattedOrganization;
	for (int i = 0; i < (9 - organization.size()); i++) {
		formattedOrganization += "0";
	}
	formattedOrganization += organization;
	return formattedOrganization;
}

