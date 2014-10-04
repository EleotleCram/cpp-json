#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include <cJSON/cJSON.h>

class cppJSON {
    cJSON* root;
	bool isRoot;

  protected:
    cppJSON(cJSON* root, bool isRoot);

  public:
	static std::unique_ptr<cppJSON> parse(const char* jsonString);
	~cppJSON();

	cppJSON get(const char* name);

	int getInt();
	void setInt(int v);

	double getDouble();
	void setDouble(double v);

	char* getString();
	void setString(char* v);
};

class cppJSONReader {
	std::function<int(char* buffer, size_t bufferSize)> readBytes;
	std::string jsonBuffer;

  public:
	/**
	 *  Create a cppJSONReader that reads NUL ('\0') delimited JSON objects
	 *  from a char* stream using the specified readBytes function.
	 */
	cppJSONReader(std::function<int(char* buffer, size_t bufferSize)> readBytes);
	/**
	 *	Attempt to read the next JSON objects using the readBytes function.
	 *  The read objects, if any, are returned through the std::vector.
	 */
	std::vector<std::unique_ptr<cppJSON>> read();
};
