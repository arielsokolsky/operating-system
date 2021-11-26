#include "../include/input.h"

/*
the function gets the user input
param: none
return: the user input
*/
string readString()
{
    char buffstr[200];  
    //string buffstr;
    int i = 0; //the last place in the string
    bool is_reading = true; // if the system is reading input, it is 1, and if it stops, its 0
    while (is_reading)
    {
        if(inputPort(CHECK_PORT) & 0x1) //checks if there is an input from the user
        {
                
            switch(inputPort(READ_PORT))
            {
                case 2:
                        
                        printch('1');
                        buffstr[i] = '1';
                        i++;
                        break;
                case 3:
                        printch('2');
                        buffstr[i] = '2';
                        i++;
                        break;
                case 4:
                        printch('3');
                        buffstr[i] = '3';
                        i++;
                        break;
                case 5:
                        printch('4');
                        buffstr[i] = '4';
                        i++;
                        break;
                case 6:
                        printch('5');
                        buffstr[i] = '5';
                        i++;
                        break;
                case 7:
                        printch('6');
                        buffstr[i] = '6';
                        i++;
                        break;
                case 8:
                        printch('7');
                        buffstr[i] = '7';
                        i++;
                        break;
                case 9:
                        printch('8');
                        buffstr[i] = '8';
                        i++;
                        break;
                case 10:
                        printch('9');
                        buffstr[i] = '9';
                        i++;
                        break;
                case 11:
                        printch('0');
                        buffstr[i] = '0';
                        i++;
                        break;
                case 12:
                        printch('-');
                        buffstr[i] = '-';
                        i++;
                        break;
                case 13:
                        printch('=');
                        buffstr[i] = '=';
                        i++;
                        break;
                case 14:
                        i--;
                        buffstr[i] = 0;
                        backSpace();
                        break;
                //cases 16-27 are the second row, without tab since we have no use for it (at least for now)
                case 16:
                        printch('q');
                        buffstr[i] = 'q';
                        i++;
                        break;
                case 17:
                        printch('w');
                        buffstr[i] = 'w';
                        i++;
                        break;
                case 18:
                        printch('e');
                        buffstr[i] = 'e';
                        i++;
                        break;
                case 19:
                        printch('r');
                        buffstr[i] = 'r';
                        i++;
                        break;
                case 20:
                        printch('t');
                        buffstr[i] = 't';
                        i++;
                        break;
                case 21:
                        printch('y');
                        buffstr[i] = 'y';
                        i++;
                        break;
                case 22:
                        printch('u');
                        buffstr[i] = 'u';
                        i++;
                        break;
                case 23:
                        printch('i');
                        buffstr[i] = 'i';
                        i++;
                        break;
                case 24:
                        printch('o');
                        buffstr[i] = 'o';
                        i++;
                        break;
                case 25:
                        printch('p');
                        buffstr[i] = 'p';
                        i++;
                        break;
                case 26:
                        printch('[');
                        buffstr[i] = '[';
                        i++;
                        break;
                case 27:
                        printch(']');
                        buffstr[i] = ']';
                        i++;
                        break;
                //casses 30- 40 are in the second letter row                
                case 30:
                        printch('a');
                        buffstr[i] = 'a';
                        i++;
                        break;
                case 31:
                        printch('s');
                        buffstr[i] = 's';
                        i++;
                        break;
                case 32:
                        printch('d');
                        buffstr[i] = 'd';
                        i++;
                        break;
                case 33:
                        printch('f');
                        buffstr[i] = 'f';
                        i++;
                        break;
                case 34:
                        printch('g');
                        buffstr[i] = 'g';
                        i++;
                        break;
                case 35:
                        printch('h');
                        buffstr[i] = 'h';
                        i++;
                        break;
                case 36:
                        printch('j');
                        buffstr[i] = 'j';
                        i++;
                        break;
                case 37:
                        printch('k');
                        buffstr[i] = 'k';
                        i++;
                        break;
                case 38:
                        printch('l');
                        buffstr[i] = 'l';
                        i++;
                        break;
                case 39:
                        printch(';');
                        buffstr[i] = ';';
                        i++;
                        break;
                case 40:
                        printch('\'');
                        buffstr[i] = '\'';
                        i++;
                        break;
                //casses 44- 55 are in the third letter row
                case 44:
                        printch('z');
                        buffstr[i] = 'z';
                        i++;
                        break;
                case 45:
                        printch('x');
                        buffstr[i] = 'x';
                        i++;
                        break;
                case 46:
                        printch('c');
                        buffstr[i] = 'c';
                        i++;
                        break;
                case 47:
                        printch('v');
                        buffstr[i] = 'v';
                        i++;
                        break;                
                case 48:
                        printch('b');
                        buffstr[i] = 'b';
                        i++;
                        break;               
                case 49:
                        printch('n');
                        buffstr[i] = 'n';
                        i++;
                        break;                
                case 50:
                        printch('m');
                        buffstr[i] = 'm';
                        i++;
                        break;               
                case 51:
                        printch(',');
                        buffstr[i] = ',';
                        i++;
                        break;                
                case 52:
                        printch('.');
                        buffstr[i] = '.';
                        i++;
                        break;            
                case 53:
                        printch('/');
                        buffstr[i] = '/';
                        i++;
                        break;            
                case 54:
                        printch('.');
                        buffstr[i] = '.';
                        i++;
                        break;            
                case 55:
                        printch('/');
                        buffstr[i] = '/';
                        i++;
                        break;
                case 57: //space
                        printch(' ');
                        buffstr[i] = ' ';
                        i++;
                        break;
                //press enter stop reading
                case 28:
                        i++;
                        is_reading = false;
                        break;
            }
        }
    }
    buffstr[i-1] = 0;
    string str = (string)buffstr;
    print("\n");
    return str;
}