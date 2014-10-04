
#include "cppJSON.h"

std::unique_ptr<cppJSON> cppJSON::parse(const char* jsonString) {
	std::unique_ptr<cppJSON> jsonObject;
	cJSON* jsonStruct = cJSON_Parse(jsonString);

	if(jsonStruct) {
		jsonObject.reset(new cppJSON(jsonStruct));
	}

	return jsonObject;
}

cppJSON::cppJSON(cJSON* root) {
	this->root = root;
}

cppJSON::~cppJSON() {
	printf("ptr: %d\n", this->root);
//	cJSON_Delete(this->root);
	this->root = 0;
}

cppJSON cppJSON::get(const char* name) {
	return cppJSON(cJSON_GetObjectItem(this->root, name));
}

int cppJSON::getInt() {
	return this->root->valueint;
}
void cppJSON::setInt(int v) {
	this->root->valueint = v;
}

double cppJSON::getDouble() {
	return this->root->valuedouble;
}
void cppJSON::setDouble(double v) {
	this->root->valuedouble = v;
}

char* cppJSON::getString() {
	return this->root->valuestring;
}
void cppJSON::setString(char* v) {
	this->root->valuestring = v;
}

cppJSONReader::cppJSONReader(std::function<int(char* buffer, size_t bufferSize)> readBytes) {
	this->readBytes = readBytes;
}
#define READ_BUFFER_LENGTH 128
std::vector<std::unique_ptr<cppJSON>> cppJSONReader::read() {
	std::vector<std::unique_ptr<cppJSON>> jsonObjects;

	char readBuffer[READ_BUFFER_LENGTH] = "";			// don't forget to pre-allocate memory
	int bytesRead = this->readBytes(readBuffer, READ_BUFFER_LENGTH);

	for(int i = 0; i < bytesRead; i++) {
		char nextChar = readBuffer[i];

		if(nextChar == '\0') {
			//printf("|%s|\n\n", this->jsonBuffer.c_str());
			std::unique_ptr<cppJSON> jsonObject = cppJSON::parse(this->jsonBuffer.c_str());
			if(jsonObject) {
				jsonObjects.push_back(std::move(jsonObject));
			}
			this->jsonBuffer.clear();
		} else {
			this->jsonBuffer += nextChar;
		}
	}

	return jsonObjects;
}
