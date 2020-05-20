#pragma once

const unsigned short HTTP_DEFAULT_PORT = 80;
const unsigned short HTTPS_DEFAULT_PORT = 443;
const unsigned short MAX_PORT_NUMBER = 65535;
const unsigned short MIN_PORT_NUMBER = 1;

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	static std::string ProtocolToString(const Protocol& protocol);

private:
	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	static std::string ParseProtocol(const std::string& url);
	static std::string ParseDomain(const std::string& url);
	static unsigned short ParsePort(const std::string& url);
	static std::string ParseDocument(const std::string& url);
	static Protocol GetProtocolFromString(const std::string& protocol);
	static unsigned short GetDefaultPort(Protocol protocol);
};

std::string GetInfo(const CHttpUrl& url);