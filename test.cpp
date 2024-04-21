#include <iostream>
#include <string>
using namespace std;
#include <stack>


// Yardımcı işlev: Verilen desenin bir parçaya eşleşip eşleşmediğini kontrol eder
bool isSubMatch(const string &input, size_t &inputIndex, const string &pattern, size_t &patternIndex)
{
    size_t subPatternIndex = 0;
    while (subPatternIndex < pattern.size())
    {
    char patternchar = pattern[subPatternIndex];
        if (patternchar == '(')
        {
            // İç içe parantez grubunu işle
            size_t groupStart = subPatternIndex;
            size_t groupEnd = 0;
            ++subPatternIndex;
            char patternchar = pattern[subPatternIndex];
            int parenCount = 1;
            while (subPatternIndex < pattern.size() && parenCount != 0)
            {
                if (patternchar == '(')
                {
                    ++parenCount;
                }
                else if (patternchar == ')')
                {
                    --parenCount;
                }
                ++subPatternIndex;
            }
            string groupPattern = pattern.substr(groupStart, subPatternIndex - groupStart - 1);

            // İç içe parantez grubunu kontrol et
            size_t subPatternIndexalt = 0; // Reset pattern index for the inner group
            if (isSubMatch(input, inputIndex, groupPattern, subPatternIndexalt))
            {
                continue; // Bir sonraki karaktere geç
            }
        }
        else if (patternchar == '?')
        {
            // '?' karakterini işle
            ++subPatternIndex; // '?' karakterini atla
        }
        else
        {
            // Tek karakteri kontrol et
            if (inputIndex < input.size() && input[inputIndex] == patternchar)
            {
                ++inputIndex;
                ++subPatternIndex;
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
    string pattern = "a(B(a)?C)?"; // Matches "a", "aBC", "aBaC"

    string input1 = "a";
    string input2 = "aBCx";
    string input3 = "aBaC";
    string input4 = "aBaX"; // Bu giriş eşleşmemelidir
    string input5 = "aaC";

    //cout << "Input: " << input1 << ", Pattern: " << pattern << ", Match: " << isMatch(input1, pattern) << endl;
    cout << "Input: " << input2 << ", Pattern: " << pattern << ", Match: " << isMatch(input2, pattern) << endl;
    //cout << "Input: " << input3 << ", Pattern: " << pattern << ", Match: " << isMatch(input3, pattern) << endl;
    // cout << "Input: " << input4 << ", Pattern: " << pattern << ", Match: " << isMatch(input4, pattern) << endl;
    // cout << "Input: " << input5 << ", Pattern: " << pattern << ", Match: " << isMatch(input5, pattern) << endl;

    return 0;
}
