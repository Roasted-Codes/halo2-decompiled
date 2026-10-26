#include "unknown_11c920.h"
#include "files.h"
#include <string.h>

// @flags /O2 /Gr

bool function_1249f0(long memory_unit, char *drive_letter);
char *function_11c9c0(char *buffer, long maximum_count, const char *format, ...);
char *function_122810(char *string, const char *suffix);
const char *saved_game_type_get_storage_name(long type);
bool function_1368f0(s_type_acf665 *file);

// @retail 0x216400
char *function_216400(long memory_unit, char *buffer, short capacity)
{
	char drive_letter;
	if (function_1249f0(memory_unit, &drive_letter))
		function_11c9c0(buffer, capacity, "%c:\\", drive_letter);
	else
		buffer[0] = 0;
	return buffer;
}

// @retail 0x216d70
bool function_216d70(char *path, const char *directory, long type)
{
	strncpy(path, directory, 0x100);
	path[0xff] = 0;
	function_122810(path, saved_game_type_get_storage_name(type));
	return true;
}

struct s_storage_file_reference
{
	dword signature;
	word flags;
	short location;
	char path[0x100];
	__int64 state;
};

// @retail 0x217590
long function_217590(long memory_unit)
{
	char root[8] = "";
	char drive_letter;
	long count = 0;
	if (function_1249f0(memory_unit, &drive_letter))
		function_11c9c0(root, sizeof(root), "%c:\\", drive_letter);
	else
		root[0] = 0;
	XGAME_FIND_DATA data;
	HANDLE find = XFindFirstSaveGame(root, &data);
	if (find != INVALID_HANDLE_VALUE)
	{
		do
		{
			count++;
		}
		while (XFindNextSaveGame(find, &data));
		XFindClose(find);
	}
	return count;
}



void __stdcall function_216e50(word const *display_name, long type, char *language, word *name);
void unicode_string_snprintf(word *buffer, long maximum_count, word const *format, ...);

struct s_save_entry_2164c0
{
    char directory[20];
    word name[17];
    byte unknown36[2];
    long type;
    byte unknown3c;
    char language;
    byte unknown3e[2];
};

struct s_save_list_2164c0
{
    long count;
    s_save_entry_2164c0 entries[4096];
};

PRIVATE inline bool append_save_entry_2164c0(s_save_list_2164c0 *list, s_save_entry_2164c0 const *entry)
{
    bool result = list->count != 4096;
    if (result)
    {
        memcpy(&list->entries[list->count++], entry, sizeof(s_save_entry_2164c0));
    }
    return result;
}

// score 32 (was 32): Frame 0x8ac and extent agree; append count/result/list and
// diagnostic/enumeration scratch rotation remain. Post-copy success/early-capacity exits 54/54;
// wide result 51; list/entry/both references 32/32/32; count plus array pointer/reference inputs
// 32/32.
// diagnostic arguments, append count/result and enumeration registers differ.
// File path/directory/both receivers 51/51/51; conditional character store 69;
// capacity first 54; capacity nonzero 51; short type index 189; no parameter address 51.
// conversion addresses, append list/count/result and final call registers differ.
// Existing root/path helpers 51/51; file-reference/all helpers 233/233;
// append names/force-inline and buffer names 51/51/51; source step at character read 72.
// conversion addresses, append and enumeration registers still differ.
// Const handle/unsigned conversion capacity 51; indexed conversion 63; full path copy 110;
// aggregate-zero file 53; unsigned append count/entry memcpy/enumeration names 51.
// matching 0x8ac frame; conversion scratch registers, append count/result homes
// and enumeration argument registers differ. Earlier helper/index/loop forms excluded; tried append
// success result 54; capacity return 54; counted conversion 229; conversion end pointer 58;
// entry lifetime 51; entry zero initializer 199; file lifetime 51; drive-validation return 51;
// shared character conversion 51.
// the append's count/result/list registers (ours eax/cl/edx, retail esi/al/ecx,
// new count stored before the copy) and the two scratch pairs before 0x13fb70 and
// XFindNextSaveGame differ. The append's memcpy into `&entries[count++]` gives retail's index copy
// (51 -> 32); an element pointer for the slot 32; post-increment index local 51; index then
// count store 51; found flag with the found arm first 51/32; helper parameters swapped 32;
// force-inline helper 32.
// @retail 0x2164c0
void function_2164c0(long memory_unit, s_save_list_2164c0 *list)
{
    (void)&list;
    char drive;
    if (function_1249f0(memory_unit, &drive))
    {
        char root[8] = "";
        if (function_1249f0(memory_unit, &drive))
            function_11c9c0(root, sizeof(root), "%c:\\", drive);
        else
            root[0] = 0;
        XGAME_FIND_DATA data;
        HANDLE find = XFindFirstSaveGame(root, &data);
        if (find != INVALID_HANDLE_VALUE)
        {
            do
            {
                s_save_entry_2164c0 entry;
                memset(&entry, 0, sizeof(entry));
                strncpy(entry.directory, data.szSaveGameDirectory, sizeof(entry.directory));
                entry.directory[19] = 0;
                long type;
                for (type = 0; type < 11; type++)
                {
                    char path[256];
                    path[0] = 0;
                    strncpy(path, entry.directory, sizeof(path));
                    path[255] = 0;
                    function_122810(path, saved_game_type_get_storage_name(type));
                    s_storage_file_reference file;
                    memset(&file, 0, sizeof(file));
                    file.signature = FILE_REFERENCE_SIGNATURE;
                    file.location = NONE;
                    if (file.flags & 1)
                    {
                        short length = (short)strlen(file.path);
                        while (length > 0 && file.path[length] != '\\') length--;
                        file.path[length] = 0;
                    }
                    if (*path)
                    {
                        size_t length = strlen(file.path);
                        char *end = file.path + length;
                        if (end != file.path && end[-1] != '\\')
                        {
                            *end++ = '\\';
                            *end = 0;
                            length++;
                        }
                        strncpy(end, path, sizeof(file.path) - length);
                        file.path[255] = 0;
                    }
                    file.flags |= 1;
                    if (function_1368f0((s_type_acf665 *)&file))
                        goto found;
                }
                {
                    word description[256];
                    unicode_string_snprintf(description, 256, L"unrecognized saved game file found by XFindNextSaveGame(): display name= '%s' path= '%hs'", data.szSaveGameName, data.wfd.cFileName);
                    char text[256];
                    word const *source = description;
                    char *destination = text;
                    long left = 256;
                    word character;
                    do
                    {
                        character = *source;
                        if (left == 1)
                            *destination = 0;
                        else if (character <= 0x7f)
                            *destination = (char)character;
                        else
                            *destination = '?';
                        source++;
                        destination++;
                        left--;
                    } while (character && left > 0);
                }
                goto next;
found:
                {
                    entry.type = type;
                    function_216e50(data.szSaveGameName, type, &entry.language, entry.name);
                    if (!append_save_entry_2164c0(list, &entry))
                        break;
                }
next:;
            } while (XFindNextSaveGame(find, &data));
            XFindClose(find);
        }
    }
}
