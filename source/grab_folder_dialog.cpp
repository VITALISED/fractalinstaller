#include "grab_folder_dialog.h"

std::wstring GetSelectFolder()
{
    // Initialize the COM library
    CoInitialize(nullptr);
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