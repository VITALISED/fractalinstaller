#pragma once

#include <Windows.h>
#include <codecvt>
#include <locale>
#include <shobjidl.h>
#include <string>

std::wstring GetSelectFolder();
std::string OpenFileAndGetPath();
