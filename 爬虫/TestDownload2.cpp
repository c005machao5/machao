// TestDownload2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <winsock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "HttpClient.h"
using namespace std;

void downloadImg()
{
	HttpClient client;

	string url = "http://www.nlegs.com/girls/2019/07/06/11447.html";
	vector<string> imgList;
	if (client.request(url)) {
		cout << "ok" << endl;
		client.save("D:\\11447.html");
		const string& data = client.getData();
		regex pattern("\\<a href=\"(/images[^\"]+)");
		smatch match;
		string::const_iterator start = data.begin();

		while (regex_search(start, data.end(), match, pattern))
		{
			imgList.push_back(string("http://www.nlegs.com") + string(match[1]));
			start = match[0].second;
		}
	}

	int idx = 1;
	for (auto & img : imgList) {
		cout << "下载： " << img << endl;
		if (client.request(img)) {
			client.save("D:\\美女\\" + to_string(idx++) + ".jpg");
		}

		//break;
	}
}

void downloadBooks();
int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	downloadBooks();
	WSACleanup();
	return 0;
}

void downloadBooks()
{
	HttpClient client;

	string url = "http://www.biquge.cm/1/1872/";

	vector<pair<string, string>> urlList;
	if (client.request(url)) {
		client.save("D:\\11447.html");

		const string& data = client.getData();
		regex pattern("\\<a href=\"(/1/1872/[^\"]+)\"\\>([^\\<]+)");
		smatch match;
		string::const_iterator start = data.begin();


		while (regex_search(start, data.end(), match, pattern))
		{
			url = string("http://www.biquge.cm") + string(match[1]);
			urlList.push_back(make_pair(string(match[2]), url));
			start = match[0].second;
		}
	}

	int idx = 1;
	ofstream file1("D:\\text\\武动乾坤.txt");
	for (auto & item : urlList) {
		cout << "下载： " << item.second << endl;
		if (client.request(item.second)) {
			const string& data = client.getData();
			string start("<div id=\"content\">");
			string end("</div>");
			size_t pos = data.find(start);
			if (pos == string::npos) continue;
			pos += start.size();
			size_t right = data.find(end, pos);
			if (right == string::npos) continue;

			string content = data.substr(pos, right - pos);

			regex pattern("<br />");
			content = regex_replace(content, pattern, "");
			content = regex_replace(content, regex("&nbsp;&nbsp;"), " ");
			content = regex_replace(content, regex("\r\n\r\n"), "\r\n");

			file1 << "====" << item.first << "====\r\n";
			file1 << content;
		}
	}

	file1.close();
}

