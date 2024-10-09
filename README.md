# StringCaseConversion
Reusable C++ helper functions to properly convert Unicode strings to upper and lower cases 

by Giovanni Dicanio

This is a header-only C++ library containing some helper functions to convert Unicode strings
to upper and lower cases.

Related blog post:
https://giodicanio.com/2024/10/09/how-to-convert-unicode-strings-to-lower-case-and-upper-case-in-c-plus-plus/

## A popular but wrong way of converting strings to upper or lower cases

A common, but in general *wrong* way, of converting a (Unicode) string to lower case, is this:

```c++

std::wstring str;

std::transform(str.begin(), str.end(), str.begin(),
               /* some lambda wrapper around std::tolower */);

```

For example, searching StackOverflow for this type of conversion in C++, the following most-voted
answer comes up:

https://stackoverflow.com/a/313990/1629821


```c++

// *** BEWARE: WRONG CODE AHEAD ***

// From StacOverflow most-voted answer:
// https://stackoverflow.com/a/313990/1629821


#include <algorithm>
#include <cctype>
#include <string>


std::string data = "Abc";
std::transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); });

```

The CppReference web site has similar wrong code:

https://en.cppreference.com/w/cpp/string/byte/tolower

```c++

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                // static_cast<int(*)(int)>(std::tolower)         // wrong
                // [](int c){ return std::tolower(c); }           // wrong
                // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

```

I published a blog post in my previous MS MVPS blog back in **November 2017**, 
discussing how that code was wrong, and how in Windows C++ code a possible solution 
is to use the [`LCMapStringEx`](https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-lcmapstringex) API.

In addition, there is an interesting [blog post](https://devblogs.microsoft.com/oldnewthing/20241007-00/?p=110345)
recently (October 2024) published on The Old New Thing blog describing why that kind of code is wrong.

Besides the *copy-and-pasto* of using `std::tolower` instead of the wchat_t-based `std::towlower`,
two key points are:

- You cannot simply convert wchar_t-by-wchar_t in a *context-free* manner, 
as context involving adjacent wchar_ts can indeed be important in some cases.

- The result string could be of a *different length* than the source string, 
and you have to take that into account in your conversion code.


## A solution: Convenient reusable string case conversion helpers

This repo contains *reusable* C++ code that implements helper functions to convert **Unicode UTF-16**
strings represented by `std::wstring` instances, abstracting away all the details of invoking 
the low-level `LCMapStringEx` Windows API (and properly allocating the destination string buffer, 
checking for errors, etc.)

To use this *header-only* library, simply `#include` the [**`StringCaseConv.hpp`** header](StringCaseConversion/StringCaseConv.hpp).
The exported helper functions are named **`ToStringUpper`** and **`ToStringLower`**.

I wrote this C++ code with Visual Studio 2019; the code compiles cleanly in **C++17** mode 
at warning level 4 (`/W4`) in both 64-bit and 32-bit builds.

