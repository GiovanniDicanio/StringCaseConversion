////////////////////////////////////////////////////////////////////////////////
// Testing the string case conversion functions.
// By Giovanni Dicanio
////////////////////////////////////////////////////////////////////////////////

#include "StringCaseConv.hpp"       // Module to test

#include <crtdbg.h>                 // _ASSERTE
#include <iostream>                 // std::wcout
#include <stdexcept>                // std::runtime_error
#include <string>                   // std::wstring

using StringCaseConv::ToStringUpper;
using StringCaseConv::ToStringLower;
using std::wcout;
using std::wstring;


// Very primitive check...
// Assert in debug builds, and throws an exception in release builds.
void Check(bool expression)
{
    _ASSERTE(expression);
    if (!expression)
    {
        wcout << "*** CHECK FAILED ***\n";
        throw std::runtime_error("Failed check");
    }
}


void BasicTests()
{
    wstring s1 = L"Ciao Ciao 1234";
    wstring s2 = ToStringUpper(s1);
    Check(s2 == L"CIAO CIAO 1234");

    wstring s3 = ToStringLower(s2);
    Check(s3 == L"ciao ciao 1234");

    wstring emptyStr;
    Check(ToStringLower(emptyStr).empty());
    Check(ToStringUpper(emptyStr).empty());

    Check(ToStringLower(L"Hello World 1122") == L"hello world 1122");
    Check(ToStringUpper(L"Hello World 1122") == L"HELLO WORLD 1122");
}


int main()
{
    wcout << L"\n*** Testing String Case Conversion Helpers ***\n";
    wcout << L"    by Giovanni Dicanio\n\n";

    BasicTests();

    // TODO: Add other more advanced tests...

    wcout << L"All tests passed :-) \n";
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

