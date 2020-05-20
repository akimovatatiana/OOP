#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

CHttpUrl::CHttpUrl(std::string const& url)
{
	if (url.empty())
	{
		throw CUrlParsingError("Empty URL!");
	}
	string protocol = ParseProtocol(url);
	m_protocol = GetProtocolFromString(protocol);
	
	string urlString(url);
	size_t position = urlString.find("://") + 3;
	
	urlString = urlString.substr(position);

	m_domain = ParseDomain(urlString);
	urlString = urlString.substr(m_domain.size());

	position = urlString.find(":");

	if (position != string::npos)
	{
		m_port = ParsePort(urlString.substr(position));
		urlString = urlString.substr(std::to_string(m_port).size() + 1);
	}
	else
	{
		m_port = GetDefaultPort(m_protocol);
	}

	m_document = ParseDocument(urlString);

	string portStr = "";
	if (m_port != HTTP_DEFAULT_PORT && m_port != HTTPS_DEFAULT_PORT)
	{
		portStr = ":" + to_string(m_port);
	}

	m_url = ProtocolToString(m_protocol) + "://" + m_domain + portStr + m_document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
{
	m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(ParseDomain(domain))
	, m_document(ParseDocument(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	string url = ProtocolToString(m_protocol) + "://" + m_domain;
	if (m_port != HTTP_DEFAULT_PORT && m_port != HTTPS_DEFAULT_PORT)
	{
		url += ":" + std::to_string(m_port);
	}
	return url + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ParseProtocol(const std::string& url)
{
	size_t endOfProtocol = url.find("://");
	if (endOfProtocol == string::npos)
	{
		throw CUrlParsingError("Invalid protocol. Usage: :// after protocol.");
	}
	string protocol = boost::to_lower_copy(url.substr(0, endOfProtocol));
	GetProtocolFromString(protocol);
	return protocol;
}

std::string CHttpUrl::ParseDomain(const std::string& url)
{
	size_t endOfDomain = url.find(":");
	if (endOfDomain == string::npos)
	{
		endOfDomain = url.find("/");
	}
	string domain = url.substr(0, endOfDomain);
	if (domain == "" || (domain.find(' ') != std::string::npos))
	{
		throw CUrlParsingError("Invalid domain");
	}
	return domain;
}

unsigned short CHttpUrl::ParsePort(const std::string& url)
{
	size_t endOfPort = url.find("/");
	string portString = url.substr(1, endOfPort - 1);

	int port = 0;
	try
	{
		port = boost::lexical_cast<int>(portString);
	}
	catch (boost::bad_lexical_cast&)
	{
		throw CUrlParsingError("Invalid port. Usage: :<port>");
	}

	if (port < MIN_PORT_NUMBER || port > MAX_PORT_NUMBER)
	{
		throw CUrlParsingError("Invalid port. Port must be in range [1, 65535]");
	}
	unsigned short us_port = (unsigned short)port;
	return us_port;
}

std::string CHttpUrl::ParseDocument(const std::string& url)
{
	string document = (url[0] != '/') ? '/' + url : url;
	if (document.empty() || document.find(' ') != string::npos)
	{
		throw CUrlParsingError("Invalid document");
	}
	return document;
}

Protocol CHttpUrl::GetProtocolFromString(const std::string& protocol)
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError("Invalid protocol type. Usage: http or https");
}

std::string CHttpUrl::ProtocolToString(const Protocol& protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
	return (protocol == Protocol::HTTP) ? HTTP_DEFAULT_PORT : HTTPS_DEFAULT_PORT;
}

std::string GetInfo(const CHttpUrl& url)
{
	ostringstream strm;
	strm << "URL: " << url.GetURL() << endl
		<< "\tProtocol: " << url.ProtocolToString(url.GetProtocol()) << endl
		<< "\tDomain: " << url.GetDomain() << endl
		<< "\tPort: " << url.GetPort() << endl
		<< "\tDocument: " << url.GetDocument() << endl;
	return strm.str();
}