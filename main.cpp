#include <iostream>
#include <string>
using namespace std;

// Yardımcı işlev: Verilen desenin bir parçaya eşleşip eşleşmediğini kontrol eder
bool isSubMatch(const string &input, size_t &inputIndex, const string &subPattern, size_t &patternIndex)
{

    size_t subPatternIndex = 0;
    int orCount = 0;
    int orIndex = 0;
    while (subPattern[subPatternIndex] != '\0')
    {
        if (subPattern[subPatternIndex] == '|')
        {
            orCount++;
            orIndex = subPatternIndex;
        }
        subPatternIndex++;
    }
    subPatternIndex = 0;
    while (subPatternIndex < subPattern.size())
    {
        char subPatternChar = subPattern[subPatternIndex];
        if (subPatternChar == '(')
        {
            // İç içe parantez grubunu işle
            ++subPatternIndex;
            size_t groupStart = subPatternIndex;
            size_t groupEnd = 0;
            int parenCount = 1;
            while (subPatternIndex < subPattern.size() && parenCount != 0)
            {
                subPatternChar = subPattern[subPatternIndex];
                if (subPatternChar == '(')
                {
                    ++parenCount;
                }
                else if (subPatternChar == ')')
                {
                    --parenCount;
                    --subPatternIndex;
                }
                ++subPatternIndex;
            }
            string groupPattern = subPattern.substr(groupStart, subPatternIndex - groupStart);

            // İç içe parantez grubunu kontrol et
            size_t subPatternIndexalt = 0; // Reset subPattern index for the inner group
            if (isSubMatch(input, inputIndex, groupPattern, subPatternIndexalt))
            {
                continue; // Bir sonraki karaktere geç
            }
        }
        else if (subPatternChar == ')')
        {
            subPatternIndex++;
        }
        else if (subPatternChar == '?')
        {
            // '?' karakterini işle
            ++subPatternIndex; // '?' karakterini atla
        }
        else
        {
            // Tek karakteri kontrol et
            if (inputIndex < input.size() && input[inputIndex] == subPattern[subPatternIndex])
            {
                ++inputIndex;
                ++subPatternIndex;
                if (subPattern[subPatternIndex] == '|')
                {
                    return true;
                }
            }
            else if (subPattern[subPatternIndex + 1] == '|')
            {
                subPatternIndex = subPatternIndex + 2;
            }
            else if (input[inputIndex + 1] != '\0')
            {
                inputIndex++;
            }
            else if (inputIndex != 0 && subPatternIndex != 0)
            {
                subPatternIndex = 0;
            }

            else if (input[inputIndex + 1] == '\0' && orIndex != 0)
            {
                inputIndex = 0;
                subPatternIndex = orIndex + 1;
            }
            else
            {
                return false; // Eşleşme yok
            }
        }
    }

    // Desenin sonuna ulaşıldı mı?
    return true;
}

// Ana işlev: Verilen desenin girişle eşleşip eşleşmediğini kontrol eder
bool isMatch(const string &input, const string &pattern)
{
    size_t inputIndex = 0;
    size_t patternIndex = 0;

    int orCount = 0;
    int orIndex = 0;
    while (pattern[patternIndex] != '\0')
    {
        if (pattern[patternIndex] == '|')
        {
            orCount++;
            orIndex = patternIndex;
        }
        patternIndex++;
    }
    patternIndex = 0;
    while (inputIndex < input.size() || patternIndex < pattern.size())
    {
        if (pattern[patternIndex] == '(')
        {
            // Parantez grubunu işle
            ++patternIndex;
            size_t groupStart = patternIndex;
            int parenCount = 1;
            while (patternIndex < pattern.size() && parenCount != 0)
            {
                if (pattern[patternIndex] == '(')
                {
                    ++parenCount;
                }
                else if (pattern[patternIndex] == ')')
                {
                    --parenCount;
                }
                ++patternIndex;
            }
            string groupPattern = pattern.substr(groupStart, patternIndex - groupStart - 1);

            // Parantez grubunu kontrol et
            if (isSubMatch(input, inputIndex, groupPattern, patternIndex))
            {
                continue; // Bir sonraki karaktere geç
            }
            else
            {
                if (pattern[patternIndex] == '?')
                {
                    // '?' karakterini işle
                    ++patternIndex; // '?' karakterini atla
                    continue;       // Bir sonraki karaktere geç
                }
                return false; // Eşleşme yok
            }
        }
        else if (pattern[patternIndex] == '\0')
        {
            return 1;
        }
        else if (pattern[patternIndex] == '[')
        {
            while (pattern[patternIndex] != ']')
            {
                patternIndex += 1;
                if (pattern[patternIndex] == '-')
                {
                    char before = pattern[patternIndex - 1];
                    char after = pattern[patternIndex + 1];
                    if (input[inputIndex] >= before && input[inputIndex] <= after)
                    {
                        patternIndex += 2;
                        inputIndex += 1;
                    }
                    else
                    {
                        patternIndex = 0;
                    }
                }
                if (pattern[patternIndex] == ']')
                {
                    patternIndex += 1;
                    // regExArrayindex = 0;
                    break;
                }
                // regExarray[regExArrayindex] = pattern[patternIndex];
                // regExArrayindex += 1;
            }

            // while (regExarray[regExArrayindex] != '\0')
            // {
            //     if (input[inputIndex] == regExarray[regExArrayindex])
            //     {
            //         inputIndex += 1;
            //         patternIndex += 1;
            //         input[inputIndex] = input[inputIndex];
            //         pattern[patternIndex] = pattern[patternIndex];

            //         regExArrayindex += 30;
            //         break;
            //     }
            //     regExArrayindex += 1;
            // }
        }

        else if (pattern[patternIndex] == '?')
        {
            // '?' karakterini işle
            ++patternIndex; // '?' karakterini atla
            continue;       // Bir sonraki karaktere geç
        }
        else
        {
            // Tek karakteri kontrol et
            if (inputIndex < input.size() && input[inputIndex] == pattern[patternIndex])
            {
                ++inputIndex;
                ++patternIndex;
            }
            else if (pattern[patternIndex] == '|')
            {
                return true;
            }
            else if (input[inputIndex + 1] != '\0')
            {
                inputIndex++;
            }
            else if (inputIndex != 0 && patternIndex != 0)
            {
                patternIndex = 0;
            }

            else if (input[inputIndex + 1] == '\0' && orIndex != 0)
            {
                inputIndex = 0;
                patternIndex = orIndex + 1;
            }
            else
            {
                return false; // Eşleşme yok
            }
        }
    }

    // Girişin sonuna ve desenin sonuna ulaşıldı mı?
    return inputIndex == input.size() && patternIndex == pattern.size();
}

int main()
{
    string pattern = "gr(a|e)y"; // Matches "a", "aBC", "aBaC"
    string input = "grexgray";       // pattern regexes
    // aBa match

    string input1 = "grayx";
    string input2 = "xhello";
    string input3 = "xhellox";
    string input4 = "aBaX"; // Bu giriş eşleşmemelidir
    string input5 = "aaC";

    cout << "Input: " << input << ", Pattern: " << pattern << ", Match: " << isMatch(input, pattern) << endl;
    cout << "Input: " << input1 << ", Pattern: " << pattern << ", Match: " << isMatch(input1, pattern) << endl;
    // cout << "Input: " << input2 << ", Pattern: " << pattern << ", Match: " << isMatch(input2, pattern) << endl;
    // cout << "Input: " << input3 << ", Pattern: " << pattern << ", Match: " << isMatch(input3, pattern) << endl;
    // cout << "Input: " << input4 << ", Pattern: " << pattern << ", Match: " << isMatch(input4, pattern) << endl;
    // cout << "Input: " << input5 << ", Pattern: " << pattern << ", Match: " << isMatch(input5, pattern) << endl;
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

1.
hello contains {hello}                                                  +
hello hellox xhello xhellox                                             +

2.
gray|grey contains {gray, grey}                                         +
gray grayx xgray xgrayx grgrayx xxgreyx                                 +

3.
gr(a|e)y contains {gray, grey}                                          +
gray grey grayx xgray xgrayx grexgray                                   +

4.
gr[ae]y contains {gray, grey}                                           -
gray grey xgray xgrey grayx  greyx xgrayx  xgreyx xgrayx                -

5.
b[aeiou]bble    contains {babble, bebble, bibble, bobble, bubble}       -
babble xbabble babblex xbabblex                                         -

6.
[b-chm-pP]at|ot  contains {bat, cat, hat, mat, nat, oat, pat, Pat, ot}  -

7.
[a-zA-Z] a through z or A through Z, inclusive (range)                  -
                                                                        -
8.
colou?r contains {color, colour}                                        -
                                                                        -
9.
rege(x(es)?|xps?) contains {pattern, regexes, regexp, regexps}          -
                                                                        -
10.
go*gle contains {ggle, gogle, google, gooogle, goooogle, ...}

11.
go+gle contains {gogle, google, gooogle, goooogle, ...}

12.
g(oog)+le contains {google, googoogle, googoogoogle, googoogoogoogle, ...}

13.
z{3} contains {zzz}

14.
z{3,6} contains {zzz, zzzz, zzzzz, zzzzzz}

15.
z{3,} contains {zzz, zzzz, zzzzz, ...}

16.
[Gg]o\*\*le contains {Go**le, go**le }

17.
\d contains {0,1,2,3,4,5,6,7,8,9}

18.
1\d{10} contains an 11-digit string starting with a 1

19.
Hello\nworld contains Hello followed by a newline followed by world

20.
mi.....f contains a nine-character (sub)string beginning with mi and ending with ft (Note: depending on context, the dot stands either for “any character at all” or “any character except a newline”.) Each dot is allowed to match a different character, so both microsoft and minecraft will match.

21.
^dog begins with "dog"

22.
dog$ ends with "dog"

23.
^dog$ is exactly "dog"

24.
[^i*&2@] contains any character other than an i, asterisk, ampersand, 2, or at-sign.

25.
([A-Z])\w+      Finds all words starting with uppercase letter

*/