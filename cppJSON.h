#pragma once

#include "cJSON/cJSON.h"

class cppJSON {
    cJSON* root;

  protected:
    cppJSON(cJSON* root);

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
