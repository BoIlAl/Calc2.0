#pragma once
#include <windows.h>
#include <vector>
#include "AbstractOperation.h"

typedef AbstractOperation*(__cdecl* getOperation)(void);

class DllLoader {
	std::vector<HINSTANCE> dllList;
	
	bool loadDll(const std::string& path, std::vector<AbstractOperation*>&);
public:
	bool getDllOperations(std::vector<AbstractOperation*>&);
	~DllLoader();
};