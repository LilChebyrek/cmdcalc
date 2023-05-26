#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

char* calc(char* input)
{
    for (int i = 0; i < strlen(input)+1; ++i)
    {
        if ((input[i] < '0' || input[i] > '9') && input[i] != '*' && input[i] != '+' && input[i] != '-' && input[i] != '/' && input[i] != '(' && input[i] != ')' && input[i] != ',' && input[i] != '.' && input[i] != ':') break;
        if (input[i] == ':') input[i] = '/';
        if (input[i] == ',') input[i] = '.';
        
        if (input[i] == '(' || input[i] == ')'){
        	char* newinput = malloc(strlen(input));
        	for (int j = 0; j < strlen(input); j++){
        		if (j < i){
        		
        		newinput[j] = input[j];
        		}
        		else if (j > i) newinput[j-1] = input[j];
        	}
        newinput[strlen(input)-1] = '\0';
       	free(input);
       	input = newinput;
       	i--;
        }
        
        if (i == strlen(input) - 1)
        {

            for (int step = 1; step <= 2; ++step)
            {
                char x, y;

                if (step == 1)
                    x = '*', y = '/';
                else
                    x = '+', y = '-';

                for (int i = 0; i < strlen(input)+1; )
                {
                    if (input[i] == x || input[i] == y)
                    {
                        double leftOp = 0, rightOp = 0;
                        int rightIterator = i, s = i;
                        short sign = 1;
                        int flag = 0;

                        for (int k = 0; i > 0 && (input[i - 1] >= '0' && input[i - 1] <= '9' || input[i - 1] == '-' || input[i - 1] == '.'); ++k)
                        {
                            flag = 1;
                            if (input[i - 1] == '-')
                            {
                                if ((i - 2) >= 0 && (input[i - 2] == '*' || input[i - 2] == '+' || input[i - 2] == '-' || input[i - 2] == '/') || i == 1)
                                {
                                    leftOp *= -1;
                                    --i;
                                }
                                break;
                            }
                            else if (input[i - 1] == '.')
                            {
                                if (leftOp == 0)
                                {
                                    --i;
                                    continue;
                                }
                                else
                                {
                                    while ((int)leftOp > 0) leftOp /= 10;
                                    int temp = i;
                                    while (input[temp++] == '0') leftOp /= 10;
                                    k = -1;
                                }
                            }
                            else
                                leftOp += (input[i - 1] - 48) * pow(10, k);

                            --i;
                        }

                        short floatCounter = 0;

                        for (rightIterator; rightIterator < strlen(input) + 1 && (input[rightIterator + 1] >= '0' && input[rightIterator + 1] <= '9' || input[rightIterator + 1] == '-' || input[rightIterator + 1] == '.'); ++rightIterator)
                        {
                            if (input[rightIterator + 1] == '-' && (input[rightIterator] == '*' || input[rightIterator] == '+' || input[rightIterator] == '-' || input[rightIterator] == '/'))
                                sign = -1;
                            else if (input[rightIterator + 1] == '-')
                                break;
                            else if (input[rightIterator + 1] == '.')
                                floatCounter = 1;
                            else if (floatCounter == 0)
                                rightOp = rightOp * 10 + input[rightIterator + 1] - 48;
                            else
                                rightOp += (input[rightIterator + 1] - 48) * pow(10, -1 * floatCounter++);
                        }

                        rightOp *= sign;

                        if (flag == 0)
                        {
                            ++i;
                            continue;
                        }

                        if (step == 2)
                            leftOp = (input[s] == '+') ? leftOp+rightOp : leftOp-rightOp;
                        else if (input[s] == '*')
                            leftOp *= rightOp;
                        else if (rightOp != 0)
                            leftOp /= rightOp;
                        else
                        {
                            printf("%s", "Exception! Division by zero.\n");
                            return input;
                        }
                        char* temp = malloc(64);
                        snprintf(temp, 64, "%lf", leftOp);
                        int tempsize=0;
                        while (temp[tempsize] != '\0') {
                            ++tempsize;
                        }
                      
                        if (temp[tempsize - 1] == '0')
                        {
                            int i = tempsize - 1;
                            for (i; temp[i] == '0'; i--)
                                temp[i]='\0';

                            if (temp[i] == '.')
                                temp[i] = '\0';
                        }
                        tempsize = 0;
                        while (temp[tempsize] != '\0') {
                            ++tempsize;
                        }
                        
                        char* newptr = malloc(strlen(input)+1 - (rightIterator - i) + tempsize);
                        int x = 0;
                        for (x; x < i; x++) {
                            newptr[x] = input[x];
                        }
                        for (int y = 0; y < tempsize; y++, x++) {
                            newptr[x] = temp[y];
                        }
                        for (int y = rightIterator + 1; y < strlen(input)+1; y++,x++) {
                            newptr[x] = input[y];
                        }
                        free(input);
                        input = newptr;



                    }
                    else
                        ++i;
                }
            }
            return input;
        }
    }
    char* ret = malloc(17);
    strcpy(ret, "Incorrect input!\0");
    return ret;
}

int main()
{
    char* input;
    do
    {
       printf("%s", "Enter an arithmetic expression: ");
       char* buf= malloc(1024);
        scanf("%s", buf);
        int i = 0;
        while (buf[i] != '\0')
            i++;
        input = malloc(i + 1);
        strcpy(input, buf);
        free(buf);
        if (strcmp(input,"exit") != 0) printf("%s%s\n\n", "Result: ", calc(input));
    } while (strcmp(input, "exit"));
}
