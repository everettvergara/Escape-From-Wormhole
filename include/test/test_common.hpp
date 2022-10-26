#pragma once

namespace g80::test {
    const wchar_t *FORE_COLOR_BLACK{L"\033[30"};
    const wchar_t *FORE_COLOR_RED{L"\033[31"};
    const wchar_t *FORE_COLOR_GREEN{L"\033[32"};
    const wchar_t *FORE_COLOR_YELLOW{L"\033[33"};
    const wchar_t *FORE_COLOR_BLUE{L"\033[34"};
    const wchar_t *FORE_COLOR_MAGENTA{L"\033[35"};
    const wchar_t *FORE_COLOR_CYAN{L"\033[36"};
    const wchar_t *FORE_COLOR_GREY{L"\033[37"};
    const wchar_t *FORE_COLOR_LIGHT_RED{L"\033[91"};
    const wchar_t *FORE_COLOR_LIGHT_GREEN{L"\033[92"};
    const wchar_t *FORE_COLOR_LIGHT_YELLOW{L"\033[93"};
    const wchar_t *FORE_COLOR_LIGHT_BLUE{L"\033[94"};
    const wchar_t *FORE_COLOR_LIGHT_MAGENTA{L"\033[95"};
    const wchar_t *FORE_COLOR_LIGHT_CYAN{L"\033[96"};
    const wchar_t *FORE_COLOR_WHITE{L"\033[97"};
    const wchar_t *BACK_COLOR_BLACK{L"\033[40"};
    const wchar_t *BACK_COLOR_RED{L"\033[41"};
    const wchar_t *BACK_COLOR_GREEN{L"\033[42"};
    const wchar_t *BACK_COLOR_YELLOW{L"\033[43"};
    const wchar_t *BACK_COLOR_BLUE{L"\033[44"};
    const wchar_t *BACK_COLOR_MAGENTA{L"\033[45"};
    const wchar_t *BACK_COLOR_CYAN{L"\033[46"};
    const wchar_t *BACK_COLOR_GREY{L"\033[47"};
    const wchar_t *BACK_COLOR_LIGHT_RED{L"\033[101"};
    const wchar_t *BACK_COLOR_LIGHT_GREEN{L"\033[102"};
    const wchar_t *BACK_COLOR_LIGHT_YELLOW{L"\033[103"};
    const wchar_t *BACK_COLOR_LIGHT_BLUE{L"\033[104"};
    const wchar_t *BACK_COLOR_LIGHT_MAGENTA{L"\033[105"};
    const wchar_t *BACK_COLOR_LIGHT_CYAN{L"\033[106"};
    const wchar_t *BACK_COLOR_WHITE{L"\033[107"};

    const wchar_t *RESET{L"\033[0m"};
    const wchar_t *BOLD{L"\033[1m"};
    const wchar_t *UNDERLINED{L"\033[4m"};
    const wchar_t *NO_UNDERLINE{L"\033[24m"};
    const wchar_t *REVERSE_COLOR{L"\033[7m"};
    const wchar_t *NO_REVERSE_COLOR{L"\033[27m"};

    const wchar_t *PASSED_TEXT{L"\033[32mPassed\033[0m"};
    const wchar_t *FAILED_TEXT{L"\033[31mFailed\033[0m"};
    const wchar_t *WARNING_TEXT{L"\033[33mWarning\033[0m"};     
}