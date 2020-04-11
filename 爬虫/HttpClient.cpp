#include "stdafx.h"
#include "HttpClient.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Ws2tcpip.h>
using namespace std;

HttpClient::HttpClient()
{
	addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3");
	addHeader("Accept-Encoding", "deflate");
	addHeader("Accept-Language", "zh-CN,zh;q=0.9");
	addHeader("Connection", "keep-alive");
	addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36");
	addHeader("Cache-Control", "max-age=0");
	addHeader("Referer", "http://www.nlegs.com");
}


HttpClient::~HttpClient()
{
}

bool HttpClient::request(const std::string & url)
{
	this->url = url;
	parseHost();
	std::vector<std::string> hostList = getHostList();
	hostList.clear();
	hostList.push_back("104.27.148.227");

	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
	for (auto & ip : hostList) {
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
		if (connect(client, (SOCKADDR *)&addr, sizeof(addr)) == 0) {
			break;
		}
	}

	/*
	请求行\r\n
	Key: Value\r\n
	Key: Value\r\n
	Key: Value\r\n
	\r\n
	*/
	//addHeader("Referer", "");
	addHeader("Host", host);
	string req = build(reqHeaders);
	send(client, req.c_str(), req.size(), 0);
	char buffer[1024 * 4] = { 0 };
	status = S_INIT;
	data.clear();
	httpFile.clear();
	while (true)
	{
		int bytes = recv(client, buffer, sizeof(buffer), 0);
		if (bytes <= 0) {
			break;
		}

		httpFile.write(buffer, bytes);
		//接收成功，解包
		switch (status)
		{
		case S_INIT:
			init();
			break;
		case S_Chunked:
			chunked();
			break;
		case S_Content:
			content();
			break;
		}

		if (status == S_Complete) {
			break;
		}
	}

	closesocket(client);
	return status == S_Complete;
}

void HttpClient::addHeader(const std::string & key, const std::string & value)
{
	for (auto & line : reqHeaders) {
		if (line.first == key) {
			line.second = value;
			return;
		}
	}

	reqHeaders.push_back(make_pair(key, value));
}

bool HttpClient::save(const std::string & filename) const
{
	ofstream file(filename, ios::binary | ios::out);
	if (!file.is_open()) {
		return false;
	}

	file << data;
	return true;
}

const std::string & HttpClient::getData() const { return data; }

bool HttpClient::parseHost()
{
	regex pattern("([\\w]+)://([^/:]+)(:(\\d+))?(/.*)$");
	smatch match;
	if (regex_search(url, match, pattern)) {
		protocol = match[1];
		host = match[2];
		path = match[5];

		if (match[4].length() > 0) {
			port = stoi(match[4]);
		}
		else {
			if (protocol == "http") { port = 80; }
			else if (protocol == "https") { port = 443; }
		}

		return true;
	}

	return false;
}

std::vector<std::string> HttpClient::getHostList()
{
	std::vector<std::string> result;

	addrinfo hints, *res;
	int err;

	ZeroMemory(&hints, sizeof(addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if ((err = getaddrinfo(host.c_str(), NULL, &hints, &res)) != 0)
	{
		return result;
	}

	char buf[32] = { 0 };
	for (addrinfo* ptr = res; ptr != nullptr; ptr = ptr->ai_next) {
		if (ptr->ai_family != AF_INET) {
			continue;
		}

		inet_ntop(ptr->ai_family, &((SOCKADDR_IN*)(res->ai_addr))->sin_addr, buf, sizeof(buf));
		result.push_back(buf);
	}

	freeaddrinfo(res);

	return result;
}

std::string HttpClient::build(const HttpHeader & header)
{
	ostringstream stream;
	stream << "GET " << path << " HTTP/1.1\r\n";

	for (auto& line : header) {
		stream << line.first << ": " << line.second << "\r\n";
	}

	stream << "\r\n";
	return stream.str();
}

const std::string & HttpClient::header(const std::string & key)
{
	static string empty;

	auto iter = resHeaders.find(key);
	if (iter != resHeaders.end()) {
		return iter->second;
	}

	return empty;
}

void HttpClient::init()
{
	/*
	响应行\r\n
	响应头\r\n
	\r\n
	数据体
	*/
	string line;
	httpFile.readLine(line);

	resHeaders.clear();
	while (httpFile.readLine(line) > 0)
	{
		size_t pos = line.find(':');
		size_t right = line.find_first_not_of(' ', pos + 1);

		resHeaders[line.substr(0, pos)] = line.substr(right);
	}

	/*
	122\r\n
	分块数据\r\n
	122\r\n
	分块数据\r\n
	122\r\n
	分块数据\r\n
	122\r\n
	分块数据\r\n
	0\r\n
	\r\n
	*/
	string transfer = header("Transfer-Encoding");
	string contentLength = header("Content-Length");
	if (transfer == "chunked") {
		status = S_Chunked;
		chunkedLen = 0;
		chunked();
	}
	else if (!contentLength.empty()) {
		status = S_Content;
		contentLen = stoi(contentLength);
		content();
	}

}

void HttpClient::chunked()
{
	while (true)
	{
		if (chunkedLen == 0) {
			string line;
			httpFile.readLine(line);

			try
			{
				chunkedLen = stoi(line, 0, 16);
				if (chunkedLen == 0) {
					status = S_Complete;
					break;
				}
			}
			catch (...)
			{
				cout << "解析error" << endl;
				break;
			}

		}
		else {
			if (httpFile.read(data, chunkedLen) > 0) {
				chunkedLen = 0;
				httpFile.seek(2);
			}
			else {
				break;
			}
		}
	}
}

void HttpClient::content()
{
	if (httpFile.read(data, contentLen) > 0) {
		status = S_Complete;
	}
}
