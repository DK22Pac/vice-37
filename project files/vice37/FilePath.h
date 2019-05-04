#pragma once
#include <Windows.h>
#include <string>

std::wstring GetModulePath(HMODULE hmodule) {
    static constexpr auto INITIAL_BUFFER_SIZE = MAX_PATH;
    static constexpr auto MAX_ITERATIONS = 7;
    std::wstring ret;
    auto bufferSize = INITIAL_BUFFER_SIZE;
    for (size_t iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        ret.resize(bufferSize);
        auto charsReturned = GetModuleFileNameW(hmodule, &ret[0], bufferSize);
        if (charsReturned < ret.length()) {
            ret.resize(charsReturned);
            return ret;
        }
        else
            bufferSize *= 2;
    }
    return std::wstring();
}

std::wstring GetModuleDir(HMODULE hmodule) {
    std::wstring modulePath = GetModulePath(hmodule);
    if (!modulePath.empty()) {
        auto lastSlash = modulePath.find_last_of(L"/\\");
        if (lastSlash != std::wstring::npos) {
            modulePath.resize(lastSlash + 1);
            return modulePath;
        }
    }
    return std::wstring();
}
