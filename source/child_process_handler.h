#pragma once

#include <Windows.h>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ChildProcessHandler
{
public:
    ChildProcessHandler(const std::string &cmd) : cmd_(cmd)
    {
        InitializePipes();
        StartChildProcess();
    }

    ~ChildProcessHandler()
    {
        // Close handles
        CloseHandle(hChildStdoutRd_);
        CloseHandle(hChildStdoutWr_);
        CloseHandle(hChildStdinRd_);
        CloseHandle(hChildStdinWr_);
    }

    // Write text to the child process
    void WriteToChildProcess(const std::string &text)
    {
        DWORD dwBytesWritten;
        WriteFile(hChildStdinWr_, text.c_str(), text.length(), &dwBytesWritten, NULL);
    }

    // Read text from the child process
    std::string ReadFromChildProcess()
    {
        char buffer[4096];
        DWORD dwBytesRead;
        ReadFile(hChildStdoutRd_, buffer, sizeof(buffer), &dwBytesRead, NULL);
        buffer[dwBytesRead] = '\0';
        return std::string(buffer);
    }

private:
    void InitializePipes()
    {
        // Create pipes for communication
        SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

        CreatePipe(&hChildStdoutRd_, &hChildStdoutWr_, &saAttr, 0);
        CreatePipe(&hChildStdinRd_, &hChildStdinWr_, &saAttr, 0);
    }

    void StartChildProcess()
    {
        // Set up members of the PROCESS_INFORMATION structure
        PROCESS_INFORMATION piProcInfo;
        STARTUPINFO siStartInfo;
        BOOL bSuccess = FALSE;

        // Set up the STARTUPINFO structure
        ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
        siStartInfo.cb = sizeof(STARTUPINFO);
        siStartInfo.hStdError = hChildStdoutWr_;
        siStartInfo.hStdOutput = hChildStdoutWr_;
        siStartInfo.hStdInput = hChildStdinRd_;
        siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

        // Construct the full path to the executable in the temp folder
        fs::path tempPath = fs::temp_directory_path();
        fs::path fullCmd = tempPath / cmd_;

        char lbuf[255]{};
        strcpy_s(lbuf, sizeof(lbuf), fullCmd.string().c_str());

        // Create the child process
        bSuccess = CreateProcess(NULL,
                                 lbuf,
                                 NULL,
                                 NULL,
                                 TRUE,
                                 0,
                                 NULL,
                                 NULL,
                                 &siStartInfo,
                                 &piProcInfo);

        // Close handles to the child process and its primary thread
        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);
    }

    // Member variables
    HANDLE hChildStdoutRd_;
    HANDLE hChildStdoutWr_;
    HANDLE hChildStdinRd_;
    HANDLE hChildStdinWr_;
    std::string cmd_;
};