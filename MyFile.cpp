#include "stdafx.h"
#include "MyFile.h"

//given the path to a file, returns the substring after the last "/" (aka the file name)
TCHAR* MyFile::getFileName(const TCHAR* filePath) {
	TCHAR string1[200];
	_tcscpy_s(string1, filePath);
	TCHAR seps[] = _T("\\");
	const TCHAR* token1 = NULL;
	TCHAR* next_token1 = NULL;
	token1 = _tcstok_s(string1, seps, &next_token1);
	TCHAR theToken1[200];
	_tcscpy_s(theToken1, token1);
	while (token1) {
		_tcscpy_s(theToken1, token1);
		token1 = _tcstok_s(NULL, seps, &next_token1);
	}
	return theToken1;
}

//opens a file dialog
//returns the path of the file
const TCHAR* MyFile::getFilePath() {
	LPWSTR fileName = NULL;
	//get file
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		IFileDialog *pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileOpen));
		if (SUCCEEDED(hr)) {
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
					pItem->GetDisplayName(SIGDN_FILESYSPATH, &fileName);
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}
	CoUninitialize();
	return fileName;
}

//does not work
bool MyFile::setWindowText(LPWSTR fileName, HWND IDC) {
	bool result = false;
	if (fileName) {
		result = true;
		//change window name to file name
		//CWnd *wndl = GetDlgItem(IDC);
		//abbreviates fileName: gets rid of directory piece
		TCHAR string1[200];
		_tcscpy_s(string1, fileName);
		TCHAR seps[] = _T("\\");
		const TCHAR* tokenl = NULL;
		TCHAR* next_tokenl = NULL;
		tokenl = _tcstok_s(string1, seps, &next_tokenl);
		const TCHAR* theTokenl = tokenl;
		while (tokenl) {
			theTokenl = tokenl;
			tokenl = _tcstok_s(NULL, seps, &next_tokenl);
		}
		//wndl->SetWindowTextW(theTokenl);
	}
	return result;
}