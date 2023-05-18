#pragma once
// https ://stackoverflow.com/questions/402283/stdwstring-vs-stdstring?rq=2
#ifdef _MSC_VER
# define STR_CLASS std::wstring
#else
# define STR_CLASS std::string
# define L
#endif
