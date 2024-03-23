#pragma once
// https ://stackoverflow.com/questions/402283/stdwstring-vs-stdstring?rq=2
#ifdef _MSC_VER
# define STR_CLASS std::wstring
# define STR_VALUE(s) L##s
# define CONVERT_TO_STD_STRING(str) std::string(str.begin(), str.end())
#else
# define STR_CLASS std::string
# define STR_VALUE(s) s
# define CONVERT_TO_STD_STRING(str) str
#endif
