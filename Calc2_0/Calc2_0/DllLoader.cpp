#include "DllLoader.h"

DllLoader::~DllLoader() {
	for (int i = 0; i < dllList.size(); ++i) {
		FreeLibrary(dllList[i]);
	}
}

bool DllLoader::getDllOperations(std::vector<AbstractOperation*>& allOperations) {
	WIN32_FIND_DATAA findData;
	HANDLE handle;

	handle = FindFirstFileA((std::string("Plugins/") + std::string("*.dll")).c_str(), &findData);

	if (handle == INVALID_HANDLE_VALUE) {
		return false;
	}
	do {
		if (!loadDll(std::string("Plugins/") + std::string(findData.cFileName), allOperations)) {
			return false;
		}
	} while (FindNextFileA(handle, &findData));

	FindClose(handle);
	return true;
}

bool DllLoader::loadDll(const std::string& path, std::vector<AbstractOperation*>& allOperations) {
	HINSTANCE module = LoadLibraryA(path.c_str());
	if (module == NULL) {
		return false;
	}

	std::string funName = "getOperation";
	FARPROC adress = GetProcAddress(module, funName.c_str());
	if (adress != 0) {
		allOperations.push_back(((getOperation)adress)());
		dllList.push_back(module);
	}
	else {
		FreeLibrary(module);
	}
	return true;
}