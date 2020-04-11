#include "stdafx.h"
#include "HttpFile.h"


HttpFile::HttpFile()
{
	size = 1024 * 1024 * 4;
	ptr = new char[size];
	offset = 0;
	pos = 0;
}


HttpFile::~HttpFile()
{
	if (ptr != nullptr) {
		delete[] ptr;
	}
}

int HttpFile::write(const char * buf, int len)
{
	if (offset + len >= size) {
		int newSize = size + len * 2;
		char* ptr = new char[newSize];
		memcpy(ptr, this->ptr, size);
		delete[] this->ptr;
		this->ptr = ptr;
	}

	memcpy(ptr + offset, buf, len);
	offset += len;

	return len;
}

int HttpFile::readLine(std::string & buf)
{
	for (int i = pos; i < offset - 1; ++i) {
		if (ptr[i] == '\r' && ptr[i + 1] == '\n') {
			int temp = i - pos;
			buf.assign(ptr + pos, temp);
			pos += temp;
			pos += 2;
			return temp;
		}
	}

	return -1;
}

int HttpFile::read(std::string& buf, int len)
{
	if (pos + len <= offset) {
		buf.append(ptr + pos, len);
		pos += len;
		return len;
	}

	return -1;
}

int HttpFile::seek(int pos)
{
	this->pos += pos;
	return 0;
}

void HttpFile::clear()
{
	offset = 0;
	pos = 0;
}
