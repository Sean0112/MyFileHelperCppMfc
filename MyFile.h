#pragma once

class MyFile {
public:
	TCHAR* getFileName(const TCHAR* filePath);
	const TCHAR* getFilePath();
	bool setWindowText(LPWSTR fileName, HWND IDC);
};
