/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef KEYS_H
#define KEYS_H

// Key encodings for use with the KEYS global variable.
// Use like this: if (KEYS[keys::esc]) {...}
namespace keys
{
    const int esc = 27;
    const int enter = 13;

    const int a = 'a';
    const int b = 'b';
    const int c = 'c';
    const int d = 'd';
    const int e = 'e';
    const int f = 'f';
    const int g = 'g';
    const int h = 'h';
    const int i = 'i';
    const int j = 'j';
    const int k = 'k';
    const int l = 'l';
    const int m = 'm';
    const int n = 'n';
    const int o = 'o';
    const int p = 'p';
    const int q = 'q';
    const int r = 'r';
    const int s = 's';
    const int t = 't';
    const int u = 'u';
    const int v = 'v';
    const int w = 'w';
    const int x = 'x';
    const int y = 'y';
    const int z = 'z';

    const int zero = '0';
    const int one = '1';
    const int two = '2';
    const int three = '3';
    const int four = '4';
    const int five = '5';
    const int six = '6';
    const int seven = '7';
    const int eight = '8';
    const int nine = '9';

    const int space = ' ';

    const int leftArrow = 1073741904;
    const int rightArrow = 1073741903;
    const int upArrow = 1073741906;
    const int downArrow = 1073741905;

    const int shift = 1073742053;
}

#endif
