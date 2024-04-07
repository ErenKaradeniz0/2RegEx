#include <iostream>
#include <string>
using namespace std;

int main()
{
    string regEx = "[a-zA-Z]";
    string input = "AZaZ";

    // cout << "Enter string " << regEx << ": ";
    // cin >> input;

    int inputindex = 0;
    int regExindex = 0;
    int regExArrayindex = 0;
    int orCount = 0;
    int regExOrindex = 0;
    char current = ' ';
    char regExCurrent = ' ';
    char regExarray[30] = {}; // Initialize all elements to null characters

    while (current != '\0' || regExCurrent != '\0')
    {
        current = input[inputindex];
        regExCurrent = regEx[regExindex];

        if (current == regExCurrent)
        {
            if (current != '\0')
            {
                inputindex += 1;
                regExindex += 1;
            }
            else
            {
                cout << "Regex and string compatible" << endl;
                break;
            }
            if (regEx[regExindex] == '|')
            {
                cout << "Regex and string compatible first |" << endl;
                break;
            }
        }
        else if (current == '\0' && regExCurrent != '|')
        {
            cout << "Not compatible Short input" << endl;
            break;
        }
        else if (regExCurrent == '\0')
        {
            cout << "Regex and string compatible" << endl;
            break;
        }
        else if (regExCurrent == '[')
        {
            while (regExCurrent != ']')
            {
                regExindex += 1;
                regExCurrent = regEx[regExindex];
                if (regExCurrent == '-')
                {
                    char before = regEx[regExindex - 1];
                    char after = regEx[regExindex + 1];
                    if (current >= before && current <= after)
                    {
                        regExindex += 2;
                        regExCurrent = regEx[regExindex];
                        inputindex += 1;
                        current = input[inputindex];
                    }
                    else
                    {
                        break;
                    }
                }
                if (regExCurrent == ']')
                {
                    regExindex += 1;
                    regExArrayindex = 0;
                    break;
                }
                regExCurrent = regExarray[regExArrayindex];
                regExArrayindex += 1;
            }

            while (regExarray[regExArrayindex] != '\0')
            {
                if (current == regExarray[regExArrayindex])
                {
                    inputindex += 1;
                    regExindex += 1;
                    current = input[inputindex];
                    regExCurrent = regEx[regExindex];

                    regExArrayindex += 30;
                    break;
                }
                regExArrayindex += 1;
            }
        }
        else if (regExCurrent == '(')
        {
            while (regExCurrent != ')')
            {
                regExindex += 1;
                regExCurrent = regEx[regExindex];
                if (regExCurrent == ')')
                {
                    regExArrayindex = 0;
                    break;
                }
                if (regExCurrent != '|')
                {
                    regExarray[regExArrayindex] = regExCurrent;
                    regExArrayindex += 1;
                }
            }

            while (regExArrayindex < 30)
            {
                if (current == regExarray[regExArrayindex])
                {
                    inputindex += 1;
                    regExindex += 1;
                    current = input[inputindex];
                    regExCurrent = regEx[regExindex];

                    regExArrayindex += 30;
                    break;
                }
                regExArrayindex += 1;
            }
        }
        else if (regExCurrent == '?')
        {
            regExindex += 1;
            regExCurrent = regEx[regExindex];
        }
        else if (regEx[regExindex + 1] == '?')
        {
            regExindex += 2;
            regExCurrent = regEx[regExindex];
        }
        else
        {
            if (input[inputindex + 1] != '\0')
            {
                regExindex = regExOrindex;
                if (regEx[regExindex] != input[inputindex])
                {
                    inputindex += 1;
                }
                current = input[inputindex];
            }
            else
            {
                while (regExCurrent != '\0')
                {
                    if (regExCurrent == '[')
                    {
                        break;
                    }
                    if (regExCurrent == '|')
                    {
                        regExOrindex = regExindex;
                        orCount += 1;
                        break;
                    }
                    regExCurrent = regEx[regExindex];
                    regExindex += 1;
                }
                regExindex = 0;
                if (orCount)
                {
                    regExindex = regExOrindex;
                    inputindex = 0;
                    orCount -= 1;
                }
                else
                {
                    cout << "Not compatible" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}

/*

Meta Characters:
(   )
[   ] +
{   }
^
$
.
\
?
*
+
|

Escape Character: \
Within square brackets, you only have to escape (1) an initial ^, (2) a non-initial or non-final -, (3) a non-initial ], and (4) a \.


hello contains {hello}                                                  +
hello hellox xhello xhellox                                             +

gray|grey contains {gray, grey}                                         +
-

gr(a|e)y contains {gray, grey}                                          +
-

gr[ae]y contains {gray, grey}                                           +
gray grey xgray xgrey grayx  greyx xgrayx  xgreyx xgrayx                +

b[aeiou]bble    contains {babble, bebble, bibble, bobble, bubble}       +
babble xbabble babblex xbabblex                                         +

[b-chm-pP]at|ot  contains {bat, cat, hat, mat, nat, oat, pat, Pat, ot}  -

[a-zA-Z] a through z or A through Z, inclusive (range)                  +
                                                                        -

colou?r contains {color, colour}                                        +
                                                                        -
                                                                        
rege(x(es)?|xps?) contains {regex, regexes, regexp, regexps}

go*gle contains {ggle, gogle, google, gooogle, goooogle, ...}

go+gle contains {gogle, google, gooogle, goooogle, ...}

g(oog)+le contains {google, googoogle, googoogoogle, googoogoogoogle, ...}

z{3} contains {zzz}

z{3,6} contains {zzz, zzzz, zzzzz, zzzzzz}

z{3,} contains {zzz, zzzz, zzzzz, ...}

[Gg]o\*\*le contains {Go**le, go**le }

\d contains {0,1,2,3,4,5,6,7,8,9}

1\d{10} contains an 11-digit string starting with a 1

Hello\nworld contains Hello followed by a newline followed by world

mi.....f contains a nine-character (sub)string beginning with mi and ending with ft (Note: depending on context, the dot stands either for “any character at all” or “any character except a newline”.) Each dot is allowed to match a different character, so both microsoft and minecraft will match.

^dog begins with "dog"

dog$ ends with "dog"

^dog$ is exactly "dog"

[^i*&2@] contains any character other than an i, asterisk, ampersand, 2, or at-sign.

([A-Z])\w+      Finds all words starting with uppercase letter

*/