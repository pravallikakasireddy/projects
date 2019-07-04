#include<stdio.h>
#include<stdlib.h>
struct intermediate_table
{
	int opcode;
	int parameters[10];
};
struct symbol
{
	char name[10];
	int address;
	int size;
};
int compare(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		return 0;
		i++;
	}
	if (str1[i] || str2[i])
		return 0;
	return 1;
}
int checkregister(char *str)
{
	if (str[1] != '\0' && str[1] == 'X')
		return 1;
	return 0;
}
int getopcode(char opcodes[15][7],char *operation)
{
	for (int i = 0; i < 14; i++)
	{
		if (compare(opcodes[i], operation))
		{
			return i + 1;
		}
	}
	return -1;
}
void buildsymboltable(char *symbol, struct symbol symboltable[20], int symbol_count, int size)
{
	int index = 0;
	while (symbol[index])
	{
		symboltable[symbol_count].name[index] = symbol[index];
		index++;
	}
	symboltable[symbol_count].name[index] = '\0';
	if (symbol_count == 0)
		symboltable[symbol_count].address = 0;
	else
	symboltable[symbol_count].address = symboltable[symbol_count - 1].address + symboltable[symbol_count - 1].size;
	symboltable[symbol_count].size = size;
}
void tokenize(char *inputline,char tokens[10][10])
{
	int i = 0;
	int token_index1 = 0;
	while (inputline[i])
	{
		int token_index2 = 0;
		while (inputline[i]!='\0' &&(inputline[i] != '[' && inputline[i] != ']' && inputline[i] != ',' && inputline[i]!='\n' && inputline[i] != '=' && inputline[i] != ' '))
		{
			tokens[token_index1][token_index2] = inputline[i];
			i++;
			token_index2++;
		}
		tokens[token_index1][token_index2] = '\0';
		if (inputline[i] == '\0')
			break;
		i++;
		if (token_index2!=0)
		token_index1++;
	}
}
int getsizeof(char *str)
{
	int i = 0;
	int size = 0;
	while (str[i] != '\0')
	{
		size = size * 10 + str[i] - '0';
		i++;
	}
	return size;
}
int getValFromSymbolTable(struct symbol symboltable[20],int symbol_count ,char *token)
{
	int i = 0;
	for (int i = 0; i < symbol_count; i++)
	{
		if (compare(symboltable[i].name, token))
			return symboltable[i].address;
	}
	return -1;
}
void printsymboltable(struct symbol symboltable[20],int symbol_count)
{
	for (int i = 0; i < symbol_count; i++)
	{
		printf("%s  ", symboltable[i].name);
		printf("%d  ", symboltable[i].address);
		printf("%d\n", symboltable[i].size);
	}
}
int getopcode(char *token)
{
	char opcodes[15][7] = { { "MOV1" }, { "MOV2" }, { "ADD" }, { "SUB" }, { "MUL" }, { "JMP" }, { "IF" }, { "EQ" }, { "LT" }, { "GT" }, { "LTEQ" }, { "GTEQ" }, { "PRINT" }, { "READ" } };
	if (compare(token, "ELSE"))
		return 6;
	for (int i = 0; i < 14; i++)
	{
		if (compare(token, opcodes[i]))
			return i+1;
	}
	return -1;
}
int isinteger(char *token)
{
	int index = 0;
	while (token[index])
	{
		if (token[index] >= '0' && token[index] <= '9')
			return 1;
		index++;
	}
	return 0;
}
void update_instruction_table(char tokens[10][10], struct intermediate_table instruction_table[20], int instruction_count,struct symbol symbol_table[20],int symbol_count)
{
	int size = 0;
	int opcode = getopcode(tokens[0]);
	if (opcode != -1)
	{
		instruction_table[instruction_count].opcode = opcode;
		for (int i = 1; i < 10;i++)
		{
			if (tokens[i][0] != '\0' && tokens[i][0]!=' ')
			{
				int opcode = getopcode(tokens[i]);
				if (checkregister(tokens[i]))
					instruction_table[instruction_count].parameters[i - 1] = tokens[i][0] - 'A';
				else if (opcode != -1)
					instruction_table[instruction_count].parameters[i - 1] = opcode;
				else
				{
					for (int j = 0; j < symbol_count; j++)
					{
						if (compare(symbol_table[j].name, tokens[i]))
						{
							if (tokens[i + 1][0] != '\0' && isinteger(tokens[i + 1]))
							{
								size = getsizeof(tokens[i + 1]);
								instruction_table[instruction_count].parameters[i - 1] = symbol_table[j].address + size;
								i = i + 1;
								break;
							}
							else
								instruction_table[instruction_count].parameters[i - 1] = symbol_table[j].address;
						}
					}
				}
			}
		}
	}
}
void print_instruction_table(struct intermediate_table instruction_table[20],int instruction_count)
{
	FILE *fp = fopen("out1.txt", "w");
	for (int i = 0; i < instruction_count-1; i++)
	{
		fprintf(fp,"%d ", instruction_table[i].opcode);
		for (int j = 0; j < 5; j++)
		{
			if (instruction_table[i].parameters[j] != -1)
				fprintf(fp, "%d ", instruction_table[i].parameters[j]);
		}
		fprintf(fp,"\n");
	}
}
int processif(int stack[10],int top,int instruction)
{
	stack[++top] = instruction;
	return top;
}
int processelse(int stack[10], int top,int instruction)
{
	stack[++top] = instruction;
	return top;
}
int processendif(int stack[10], int top, struct intermediate_table instruction_table[20],int instruction)
{
	int index;
	while (instruction_table[stack[top]].opcode != 7)
	{
		index = stack[top--];
		int i = 0;
		while (instruction_table[index].parameters[i] != -1)
		{
			i++;
		}
		instruction_table[index].parameters[i] = instruction;
		instruction = index;
	}
	index = stack[top--];
	int i = 0;
	while (instruction_table[index].parameters[i] != 0)
	{
		i++;
	}
	instruction_table[index].parameters[i] = instruction + 1;
	return top;
}
int isnotlabel(char *token)
{
	int i = 0;
	while (token[i])
	{
		i++;
	}
	if (token[i - 1] ==':')
		return 0;
	return 1;
}
int main()
{
	FILE *fp = fopen("sample1.txt", "r+");
	if (fp == NULL)
	{
		printf("cannot open the file");
		return 0;
	}
	char *inputline;
	struct symbol symboltable[20];
	int symbol_count = 0;
	int top = -1;
	int stack[10];
	struct intermediate_table instruction_table[20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			instruction_table[i].parameters[j] = -1;
		}
	}
	int instruction_count = 0;
	inputline = (char *)malloc(20 * sizeof(char));
	while (fgets(inputline,100,fp))
	{
		int size;
		char tokens[10][10];
		for (int i = 0; i < 10; i++)
			tokens[i][0] = '\0';
		tokenize(inputline, tokens);
		if (compare(tokens[0], "DATA"))
		{
			size = 1;
			if (tokens[2][0]!='\0')
			size = getsizeof(tokens[2]);
			buildsymboltable(tokens[1], symboltable, symbol_count,size);
			symbol_count = symbol_count + 1;
		}
		else if (compare(tokens[0], "CONST"))
		{
			size = 1;
			if (tokens[2][0]!='\0')
				size = getsizeof(tokens[2]);
			buildsymboltable(tokens[1], symboltable, symbol_count, size);
			symbol_count = symbol_count + 1;
		}
		else if (compare(tokens[0], "MOV"))
		{
			if (checkregister(tokens[1]))
			{
				 instruction_table[instruction_count].opcode= 1;
				 instruction_table[instruction_count].parameters[0] = tokens[1][0] - 'A';
				 instruction_table[instruction_count].parameters[1] = getValFromSymbolTable(symboltable,symbol_count,tokens[2]);
			}
			else
			{
				instruction_table[instruction_count].opcode = 2;
				instruction_table[instruction_count].parameters[0] = getValFromSymbolTable(symboltable, symbol_count, tokens[1]);
				instruction_table[instruction_count].parameters[1] = tokens[2][0] - 'A';
			}
			instruction_count = instruction_count + 1;
		}
		else
		{
			update_instruction_table(tokens, instruction_table,instruction_count,symboltable,symbol_count);
			if (compare(tokens[0], "IF"))
			{
				top = processif(stack, top, instruction_count);
				instruction_count = instruction_count + 1;
			}
			else if (compare(tokens[0], "ELSE"))
			{
				top = processelse(stack, top, instruction_count);
				instruction_count = instruction_count + 1;
			}
			else if (compare(tokens[0], "ENDIF"))
				top = processendif(stack, top,instruction_table, instruction_count);
			else if (isnotlabel(tokens[0]))
				instruction_count = instruction_count + 1;
		}
	}
	print_instruction_table(instruction_table, instruction_count);
	system("pause");
}


































































































































































































































