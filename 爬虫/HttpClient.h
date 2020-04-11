#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include "HttpFile.h"

class HttpClient
{
	typedef std::list<std::pair<std::string, std::string>> HttpHeader;
	typedef std::map<std::string, std::string> HttpResponseHeader;
public:
	HttpClient();
	~HttpClient();

	bool request(const std::string& url);
	void addHeader(const std::string& key, const std::string& value);
	bool save(const std::string& filename) const;

	const std::string& getData() const;

	enum STATUS
	{
		S_INIT = 1, //init
		S_Chunked = 2,
		S_Content = 3,

		S_Complete,
	};
private:
	bool parseHost();
	std::vector<std::string> getHostList();
	std::string build(const HttpHeader& header);
	const std::string& header(const std::string& key);
private:
	void init();
	void chunked();
	void content();
private:
	std::string host;
	std::string path;
	std::string protocol;
	int port;
	std::string url;
	int status;
	HttpHeader         reqHeaders;
	HttpResponseHeader resHeaders;
	HttpFile    httpFile;
	int chunkedLen;
	int contentLen;
	std::string data;
};

