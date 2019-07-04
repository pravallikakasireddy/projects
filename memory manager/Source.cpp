#include<stdio.h>
#include<stdlib.h>
#define max_limit 10
struct file
{
	char filename[10];
	unsigned long int start;
	int length;
};
struct metadata
{
	struct file files[max_limit];
};
struct metadata data;
int filecount = 0;
int compare(char *str, char *s)
{
	int i = 0;
	while (str[i]!=NULL && s[i]!=NULL)
	{
		i++;
		if (str[i] != s[i])
			return 0;
	}
	return 1;
}
unsigned long int set_offset(char *str)
{
	if (filecount == 0)
	{
		data.files[filecount].start = 3145728;
		int i = 0;
		while (str[i])
		{
			data.files[filecount].filename[i] = str[i];
			i++;
		}
		data.files[filecount].filename[i] = '\0';
		filecount = filecount + 1;
		return 3145728;
	}
	int i = 0;
	while (str[i])
	{
		data.files[filecount].filename[i] = str[i];
		i++;
	}
	data.files[filecount].filename[i] = '\0';
	data.files[filecount].start = data.files[filecount-1].start + data.files[filecount-1].length+1;
	unsigned long int start_loc = data.files[filecount].start;
	filecount = filecount + 1;
	printf("%lu", start_loc);
	return start_loc;
}
unsigned long int get_offset(char *filename)
{
	for (int i = 0; i <filecount; i++)
	{
		if (compare(filename, data.files[i].filename))
		{
			return data.files[i].start + data.files[i].length+1;
		}
	}
	return -1;
}
int get_length(char *filename)
{
	int length = 0;
	char ch;
	FILE *file_to_be_read = fopen(filename, "rb");
	if (file_to_be_read == NULL)
	{
		printf("canot open the file");
		return 0;
	}
	while (fread(&ch, 1, 1, file_to_be_read))
	{
		length++;
	}
	fclose(file_to_be_read);
	return length;
}
unsigned long int get_start_pos_of_file(char *disk_file)
{
	for (int i = 0; i < filecount; i++)
	{
		if (compare(data.files[i].filename, disk_file))
			return i;
	}
}
void copy_from_disk(char *disk_file,char *dest_file)
{
	int index = get_start_pos_of_file(disk_file);
	unsigned long int start = data.files[index].start;
	int length = data.files[index].length;
	FILE *filetoread = fopen("harddisk.hdd", "rb");
	if (filetoread == NULL)
	{
		printf("cannot open the file");
		return;
	}
	FILE *filetowrite = fopen(dest_file, "wb");
	if (filetowrite == NULL)
	{
		printf("cannot open the file");
		return;
	}
	fseek(filetoread, start, SEEK_SET);
	while (length--)
	{
		char ch;
		fread(&ch, 1, 1, filetoread);
		fwrite(&ch, 1, 1, filetowrite);
	}
	fclose(filetowrite);
	fclose(filetoread);
}
void write_to_disk(char *filename)
{
	char ch;
	int length=0;
	unsigned long int start = set_offset(filename);
	printf("%lu", start);
	FILE *disk_head = fopen("harddisk.hdd", "rb+");
	if (disk_head == NULL)
	{
		printf("head canonot open the file");
			return;
	}
	FILE *readfile = fopen(filename, "rb");
	if (readfile == NULL)
	{
		printf("canonot open the file");
		return;
	}
	fseek(disk_head, start, SEEK_SET);
	while (fread(&ch, 1, 1, readfile))
	{
		length++;
		fwrite(&ch, 1, 1, disk_head);
	}
	data.files[filecount-1].length = length;
	fclose(disk_head);
	fclose(readfile);
}
void print_list_of_files()
{
	printf("files\n");
	for (int i = 0; i < filecount; i++)
	{
		printf("%s\n", data.files[i].filename);
	}
}
void write_metadata()
{
	FILE *disk_head = fopen("harddisk.hdd", "rb+");
	if (disk_head == NULL)
	{
		printf("cannot open the file");
		return;
	}
	fwrite(&filecount, sizeof(int), 1, disk_head);
	fseek(disk_head, 4 , SEEK_SET);
	for (int i = 0; i < filecount; i++)
	{
		fwrite(&data.files[i], sizeof(struct file), 1, disk_head);
	}
	fclose(disk_head);
}
int main()
{
	FILE *disk_head = fopen("harddisk.hdd", "rb+");
	char *diskfile = (char *)malloc(100 * sizeof(char));
	char *input = (char *)malloc(100 * sizeof(char));
	fread(&filecount, sizeof(int), 1, disk_head);
	for (int i = 0; i < filecount;i++)
	fread(&data.files[i], sizeof(struct file), 1, disk_head);
	do
	{
		printf(">>");
		scanf("%s", input);
		if (compare(input, "copy"))
		{
			char s[100];
			scanf("%s", s);
			if (compare(s, "to"))
			{
				char *filename = (char *)malloc(100 * sizeof(char));
				scanf("%s", filename);
				write_to_disk(filename);
				write_metadata();
			}
			else
			{
				char *filename = (char *)malloc(100 * sizeof(char));
				scanf("%s", diskfile);
				scanf("%s", filename);
				copy_from_disk(diskfile, filename);
			}
		}
		else if (compare(input, "ls"))
		{
			print_list_of_files();
		}
	} while (1);
	system("pause");
	return 0;
}
