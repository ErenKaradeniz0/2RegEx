#include <stdio.h>
int main()
{

    char regEx[30] = "gray|grey";
    char regExarray[30]; // []'s array
    char color[30];
    // gr(a|e)y   true grey gray
    printf("Enter string %s: ", regEx);

    scanf("%s", color);
    int index = 0;
    int regExindex = 0;
    int regExArrayindex = 0;
    int or = 0;
    int regExOrindex = 0;
    char current = ' ';
    char regExCurrent = ' ';

    while (current != '\0' || regExCurrent != '\0')
    {
        current = color[index];
        regExCurrent = regEx[regExindex];

        if (current == regExCurrent)
        {
            if (current != '\0')
            {
                // printf("= if %c \n", current);
                index += 1;
                regExindex += 1;
            }
            else
            {
                printf("Regex and string compaible\n");
                break;
            }
            if (regEx[regExindex] == '|')
            {
                printf("Regex and string compaible first |\n");
                break;
            }
        }
        else if (current == '\0' && regExCurrent != '|')
        {
            printf("Not compaible Short input \n");
            break;
        }
        else if (regExCurrent == '\0')
        {
            printf("Regex and string compaible\n");
            break;
        }
        else if (regExCurrent == '[')
        {
            while (regExCurrent != ']')
            {
                regExindex += 1;
                regExCurrent = regEx[regExindex];
                if (regExCurrent == ']')
                {
                    regExArrayindex = 0;
                    break; // regex index at ]
                }
                regExarray[regExArrayindex] = regExCurrent;
                regExArrayindex += 1;
            }

            while (regExArrayindex < 30)
            {
                if (current == regExarray[regExArrayindex])
                {
                    // printf("= else %c \n", current);
                    index += 1;
                    regExindex += 1;
                    current = color[index];
                    regExCurrent = regEx[regExindex];

                    regExArrayindex += 30;
                    break;
                }
                regExArrayindex += 1;
            }
        }

        else
        {
            if (color[index + 1] != '\0')
            {
                regExindex = regExOrindex;
                if (regEx[regExindex] != color[index])
                {
                    index += 1;
                }
                current = color[index];
            }
            else
            {
                // check or
                while (regExCurrent != '\0')
                {
                    if (regExCurrent == '[')
                    {
                        break; // [|] change
                    }
                    if (regExCurrent == '|')
                    {
                        regExOrindex = regExindex;
                        or += 1;
                        break;
                    }
                    regExCurrent = regEx[regExindex];
                    regExindex += 1;
                }
                regExindex = 0;
                if (or)
                {
                    regExindex = regExOrindex;
                    index = 0;
                    or -= 1;
                }
                else
                {
                    printf("Not compaible \n");
                    break;
                }
            }
        }
    }
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


hello contains {hello}
hello hellox xhello xhellox +

gray|grey contains {gray, grey}

gr(a|e)y contains {gray, grey}


gr[ae]y contains {gray, grey}
gray grey xgray xgrey grayx  greyx xgrayx  xgreyx xgrayx +

b[aeiou]bble    contains {babble, bebble, bibble, bobble, bubble}
babble xbabble babblex xbabblex +

[b-chm-pP]at|ot  contains {bat, cat, hat, mat, nat, oat, pat, Pat, ot}
[a-zA-Z] a through z or A through Z, inclusive (range)
colou?r contains {color, colour}
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