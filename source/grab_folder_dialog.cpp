#include "grab_folder_dialog.h"

std::wstring GetSelectFolder()
{
    // Initialize the COM library
    CoInitialize(nullptr);

    IFileOpenDialog *pFileOpen;

    // Create the FileOpenDialog object
    HRESULT hr = CoCreateInstance(
        CLSID_FileOpenDialog,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pFileOpen));

    if (SUCCEEDED(hr))
    {
        // Set options to pick folders
        DWORD dwOptions;
        hr = pFileOpen->GetOptions(&dwOptions);

        if (SUCCEEDED(hr))
        {
            hr = pFileOpen->SetOptions(dwOptions | FOS_PICKFOLDERS);

            if (SUCCEEDED(hr))
            {
                // Show the dialog
                hr = pFileOpen->Show(nullptr);

                if (SUCCEEDED(hr))
                {
                    IShellItem *pItem;
                    hr = pFileOpen->GetResult(&pItem);

                    if (SUCCEEDED(hr))
                    {
                        PWSTR pszFilePath;
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                        if (SUCCEEDED(hr))
                        {
                            std::wstring selectedFolder = pszFilePath;

                            CoTaskMemFree(pszFilePath);
                            pItem->Release();
                            pFileOpen->Release();

                            // Uninitialize the COM library
                            CoUninitialize();

                            return selectedFolder;
                        }
                    }
                }
            }
        }

        pFileOpen->Release();
    }
    CoUninitialize();

    return L"";
}

std::string OpenFileAndGetPath()
{
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    IFileOpenDialog *pFileOpen;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void **>(&pFileOpen));

    std::string selectedFilePath;

    if (SUCCEEDED(hr))
    {
        DWORD dwOptions;
        hr = pFileOpen->GetOptions(&dwOptions);
        if (SUCCEEDED(hr))
        {
            hr = pFileOpen->SetOptions(dwOptions | FOS_FORCEFILESYSTEM);
        }

        COMDLG_FILTERSPEC fileTypes[] = {{L"No Man's Sky Executable", L"NMS.exe"}};
        hr = pFileOpen->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
        hr = pFileOpen->SetFileTypeIndex(1); // Set the default file type index

        if (SUCCEEDED(hr))
        {
            hr = pFileOpen->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR filePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

                    if (SUCCEEDED(hr))
                    {
                        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
                        selectedFilePath = conv.to_bytes(filePath);
                        // Free the allocated memory
                        CoTaskMemFree(filePath);
                    }

                    pItem->Release();
                }
            }
        }

        pFileOpen->Release();
    }

    CoUninitialize();

    return selectedFilePath;
}