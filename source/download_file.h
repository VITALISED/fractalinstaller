#pragma once

#include <Windows.h>
#include <curl/curl.h>
#include <filesystem>
#include <fstream>
#include <iostream>

void DownloadFile(const std::string &url, const std::string &outPath);