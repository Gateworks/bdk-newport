/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#ifndef BDK_BUILD_HOST
#include <bdk.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#ifdef BDK_BUILD_HOST
#include <stdlib.h>
#include <termios.h>
#include <sys/time.h>
#include "bdk-readline.h"
#endif

#define MAX_INSERT 8

#define CURSOR_ON  "\033[?25h"  /* Turn on cursor */
#define CURSOR_OFF "\033[?25l"  /* Turn off cursor */

#define MAX_COMMAND 128
#define MAX_HISTORY_LOG2 (5)
#define MAX_HISTORY (1<<MAX_HISTORY_LOG2)
#define MAX_HISTORY_MASK (MAX_HISTORY-1)

static char command_history[MAX_HISTORY][MAX_COMMAND];
static int history_index;
static int history_lookup_index;

static const char *cmd_prompt;
static unsigned int readline_flags; /* so far: bit[0] is 1 for enabling '.' to '_' conversion */
static const bdk_readline_tab_t *tab_complete_data;
static unsigned int cmd_len;
static unsigned int cmd_pos;
static char *cmd;

static int escape_saw_char;
static int escape_mode;
static int find_mode;
static int find_orig_cmd_pos;
static int search_mode;
static int was_lookup;
static int insert_mode = 1;
static int delete_mode;
static int overwrite_once;
static const bdk_readline_tab_t *saved_avail_p;
static int saved_suffix_size;
static int tab_mode;
static char pattern[MAX_COMMAND];
static int pattern_dir_delta=-1;
static int pattern_dir_reverse;
typedef struct {
    char cmd[MAX_COMMAND];
    unsigned int cmd_len;
    unsigned int cmd_pos;
} undo_t;
static undo_t undo = {{0,},0,0};

static const char *function_key_commands[] = {
    "F1",       /* F1 */
    "F2",       /* F2 */
    "F3",       /* F3 */
    "F4",       /* F4 */
    "F5",       /* F5 */
    "F6",       /* F6 */
    "F7",       /* F7 */
    "F8",       /* F8 */
    "F9",       /* F9 */
    "F10",      /* F10 */
    "",         /* N/A */
    "F11",      /* F11 */
    "F12",      /* F12 */
    "Shift-F1", /* Shift-F1 */
    "Shift-F2", /* Shift-F2 */
    "",         /* N/A */
    "Shift-F3", /* Shift-F3 */
    "Shift-F4", /* Shift-F4 */
    "",         /* N/A */
    "Shift-F5", /* Shift-F5 */
    "Shift-F6", /* Shift-F6 */
    "Shift-F7", /* Shift-F7 */
    "Shift-F8", /* Shift-F8 */
    NULL
};

static const char *process_function_key(int function)
{
    escape_mode=0;
    escape_saw_char=0;
    if ((function < 1) || (function > 22)) {
        printf ("function key error %d\n",function);
        return NULL;
    }
    return function_key_commands[function-1];
}

static char on_screen[256];
static int on_screen_len = 0;
static int on_screen_cursor = 0;

static void reset_screen_draw(int do_back)
{
    while (do_back && on_screen_cursor--)
        putchar('\b');
    on_screen_len = 0;
    on_screen_cursor = 0;
}

static void process_input_draw_current()
{
    char update_screen[256];
    int update_screen_len;
    int update_screen_cursor = cmd_pos + 5 + strlen(cmd_prompt);
    int cursor_is_off = 0;

    command_history[history_index][cmd_len] = 0;
    update_screen_len = snprintf(update_screen, sizeof(update_screen)-1,
        "(%s)%s%s",
        delete_mode ? "DEL" : find_mode ? "FND" : escape_mode ? "ESC" : insert_mode ? "INS" : "OVR",
        cmd_prompt, command_history[history_index]);

    /* If the on screen cursor is after the new location than back it up */
    while (on_screen_cursor > update_screen_cursor)
    {
        putchar('\b');
        on_screen_cursor--;
    }

    /* Check if any characters before the on screen cursor are different */
    if (memcmp(on_screen, update_screen, on_screen_cursor))
    {
        cursor_is_off = 1;
        fputs(CURSOR_OFF, stdout);
        int pos = on_screen_cursor;
        while (pos--)
            putchar('\b');
        fwrite(update_screen, 1, on_screen_cursor, stdout);
    }
    /* Write any characters between the old cursor and the new */
    fwrite(update_screen+on_screen_cursor, 1, update_screen_cursor-on_screen_cursor, stdout);
    on_screen_cursor = update_screen_cursor;

    /* Check if any characters after the cursor are different */
    if ((on_screen_len > update_screen_len) ||
        memcmp(on_screen+update_screen_cursor, update_screen+update_screen_cursor, update_screen_len - update_screen_cursor))
    {
        int pos;
        cursor_is_off = 1;
        fputs(CURSOR_OFF, stdout);
        fwrite(update_screen+update_screen_cursor, 1, update_screen_len - update_screen_cursor, stdout);
        for (pos=update_screen_len; pos<on_screen_len; pos++)
            putchar(' ');
        while (pos > update_screen_cursor)
        {
            putchar('\b');
            pos--;
        }
    }
    if (cursor_is_off)
        fputs(CURSOR_ON, stdout);
    strcpy(on_screen, update_screen);
    on_screen_len = update_screen_len;
}

static const char *find_token_end(const char *token)
{
    char *b;
    char *p=strchr(token,' ');
    if ((b=strchr(token,'[')) && (b<p)) p=b;    /* for 'tx.data[' style case */
    if (p==NULL)
        return (token + strlen(token));
    return (p+1);
}

static void process_input_commit_character(char ch) {
    if (insert_mode) {
        if (cmd_len < MAX_COMMAND-1) {
            if (cmd_len > cmd_pos) {
                memmove(&cmd[cmd_pos+1], &cmd[cmd_pos], cmd_len-cmd_pos+1);
            }
            cmd[cmd_pos++] = ch;
            cmd_len++;
        }
    }
    else {      /* overwrite mode */
        if (cmd_pos < MAX_COMMAND-1) {
            cmd[cmd_pos++] = ch;
            if (cmd_pos > cmd_len) cmd_len = cmd_pos;
        }
    }
}

static const bdk_readline_tab_t *next_avail_p(const bdk_readline_tab_t *avail_p, const bdk_readline_tab_t *lut)
{
    if (avail_p->str == NULL) return lut;
    avail_p++;
    if (avail_p->str == NULL) return lut;
    return avail_p;
}

static void tab_complete(char *token_start, const bdk_readline_tab_t *lut)
{       /* find longest common suffix, of those with matching prefixes */
    const bdk_readline_tab_t *avail_p;
    const char *p;
    int suffix_size=-1;
    const char *suffix = NULL;
    int offset = cmd_pos - (token_start - cmd);
    int delta_pos=0;
    int printed=0;

    if (tab_mode==1) {
        if (saved_avail_p == NULL) {
            for (saved_avail_p = lut; saved_avail_p->str; saved_avail_p++);
            saved_avail_p--;    /* initialize to the one before the end */
        }
        for (avail_p = next_avail_p(saved_avail_p,lut); avail_p != saved_avail_p; avail_p = next_avail_p(avail_p,lut)) {
            if (strncasecmp(token_start, avail_p->str, offset)==0) {        /* prefix matches */
                suffix = avail_p->str+offset;
                p=find_token_end(suffix);
                suffix_size = p - suffix;
                saved_avail_p = avail_p;
                delta_pos = suffix_size;
                if ((cmd_pos + saved_suffix_size) > MAX_COMMAND-1) {
                    saved_suffix_size=0;        /* this should never happen, but just in case... */
                }
                if ((cmd_pos + saved_suffix_size) > cmd_len) {
                    cmd_len = (cmd_pos + saved_suffix_size);
                }
                if (insert_mode) {
                    memmove(&cmd[cmd_pos], &cmd[cmd_pos+saved_suffix_size], saved_suffix_size);
                    cmd_len -= saved_suffix_size;
                }
                else {  /* in overwrite mode, at least cover leftover junk that we created with spaces */
                    memset(&cmd[cmd_pos], ' ', saved_suffix_size);
                }
                cmd[cmd_len]=0;
                saved_suffix_size = suffix_size;
                break;
            }
        }
    }
    else {
        if (tab_mode==2) putchar('\n');
        for (avail_p = lut; avail_p->str && suffix_size; avail_p++) {
            if (strncasecmp(token_start, avail_p->str, offset)==0) {        /* prefix matches */
                if (tab_mode==2) {      /* list all */
                    p = find_token_end(avail_p->str);
                    fwrite(avail_p->str, p - avail_p->str, 1, stdout);
                    putchar(' ');
                    printed += p - avail_p->str;
                    if (printed > 70) {
                        putchar('\n');
                        printed = 0;
                    }
                }
                else {
                    if (suffix==NULL) { /* first match */
                        suffix = avail_p->str+offset;
                        p=find_token_end(suffix);
                        suffix_size = p - suffix;
                    }
                    else {      /* not first match */
                        while ((suffix_size>0) && (strncasecmp(suffix,avail_p->str+offset, suffix_size)!=0)) {
                            suffix_size--;
                        }
                    }
                }
            }
        }
    }
    while (suffix_size > 0) {   /* copy suffix to buffer and echo to output (unless too big) */
        process_input_commit_character(*suffix);
        suffix++;
        suffix_size--;
    }
    cmd_pos -= delta_pos;

    if ((tab_mode==2) && printed) putchar('\n');
    process_input_draw_current();
}

static void process_input_change_index(int delta)
{
    int new_index = (history_lookup_index+delta) & MAX_HISTORY_MASK;
    int new_cmd_len = strlen(command_history[new_index]);

    if (new_cmd_len == 0) return;       /* ignore if uncharted */
    history_lookup_index = new_index;
    cmd_len = new_cmd_len;
    cmd_pos = cmd_len;

    strcpy(command_history[history_index], command_history[history_lookup_index]);      /* copy to current command */
    process_input_draw_current();
}

static void process_input_change_index_to(int line)
{
    process_input_change_index(line - history_lookup_index);
}

static void process_input_change_pos(int delta)
{
    cmd_pos += delta;

    if ((signed)cmd_pos < 0) cmd_pos=0;
    if (cmd_pos > cmd_len) cmd_pos=cmd_len;

    process_input_draw_current();
}

static void process_input_save_undo(void)
{
    undo.cmd_len = cmd_len;
    undo.cmd_pos = cmd_pos;
    strncpy(undo.cmd, cmd, MAX_COMMAND);
}

static void process_input_undo(void)
{
    undo_t temp;

    temp.cmd_len = undo.cmd_len;
    temp.cmd_pos = undo.cmd_pos;
    strncpy(temp.cmd, undo.cmd, MAX_COMMAND);

    process_input_save_undo();

    cmd_len = temp.cmd_len;
    cmd_pos = temp.cmd_pos;
    strncpy(cmd, temp.cmd, MAX_COMMAND);
}

static void process_input_beginning_of_word(void)
{
    cmd_pos--;
    while (((signed)cmd_pos >= 0) && (cmd[cmd_pos] == ' ')) {
        cmd_pos--;
    }
    while (((signed)cmd_pos >= 0) && (cmd[cmd_pos] != ' ')) {
        cmd_pos--;
    }
    cmd_pos++;
}

static void process_input_next_word(void)
{
    cmd_pos++;
    while ((cmd_pos < cmd_len) && (cmd[cmd_pos] != ' ')) {
        cmd_pos++;
    }
    while ((cmd_pos < cmd_len) && (cmd[cmd_pos] == ' ')) {
        cmd_pos++;
    }
}

static void process_input_delete(unsigned int orig_cmd_pos)
{
    int delta = cmd_pos - orig_cmd_pos;
    int len = cmd_len - cmd_pos + 1;
    if (delta < 0) {
        memmove(&cmd[cmd_pos], &cmd[orig_cmd_pos], len);
        cmd_len += delta;
    }
    else if (delta > 0) {
        memmove(&cmd[orig_cmd_pos], &cmd[cmd_pos], len);
        cmd_len -= delta;
        cmd_pos = orig_cmd_pos;
    }
    delete_mode=0;
}

static int remove_leading_spaces(void)
{
    unsigned int num_leading_spaces;
    char *curr_cmd = command_history[history_index];

    curr_cmd[cmd_len] = 0;      /* make sure the command is terminated */
    /* first find leading spaces */
    for (num_leading_spaces=0; curr_cmd[num_leading_spaces] == ' '; num_leading_spaces++) { /* loop */ }
    if (num_leading_spaces != 0) {      /* found leading spaces, remove them */
        cmd_len -= num_leading_spaces;
        if (cmd_pos < num_leading_spaces) cmd_pos=0;
        else cmd_pos -= num_leading_spaces;
        memmove(&curr_cmd[0], &curr_cmd[num_leading_spaces], cmd_len+1);
        return 1;
    }
    return 0;
}

static const char *process_input(int c)
{
    cmd = command_history[history_index];
    cmd[cmd_len] = 0;

    if (c == 0)         /* no new input */
    {
        process_input_draw_current();
        goto process_input_done;
    }

    if (! (escape_mode && !escape_saw_char && !find_mode && (c=='u')) )
        process_input_save_undo();

    if (escape_mode) {  /* process escape sequences */
        if (escape_saw_char == '[') {
            switch (c) {
                case 'A':
                    process_input_change_index(-1);
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'B':
                    process_input_change_index(+1);
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'C':
                    process_input_change_pos(+1);
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'D':
                    process_input_change_pos(-1);
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'P':       /* Pause/Break key, toggle start/stop */
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case '\r':
                case '\n':
                    escape_mode=0;
                    escape_saw_char=0;
                    goto parse_input;   /* parse this as a normal character */
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    escape_saw_char=c;  /* really should handle more than one character here */
                    break;
                default:
                    escape_mode=0;
                    escape_saw_char=0;
                    goto parse_input;   /* parse this as a normal character */
            }
        }
        else if (escape_saw_char == 'O') {
            switch (c) {
                case 'H':       /* Home */
                    cmd_pos=0;
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'F':       /* End */
                    cmd_pos=cmd_len;
                    escape_mode=0;
                    escape_saw_char=0;
                    break;
                case 'P':       /* F1 */
                case 'Q':       /* F2 */
                case 'R':       /* F3 */
                case 'S':       /* F4 */
                    return process_function_key(c-'P'+1);
                    break;
                default:
                    escape_mode=0;
                    escape_saw_char=0;
                    goto parse_input;   /* parse this as a normal character */
            }
        }
        else if (isdigit((int)escape_saw_char) && isdigit(c)) {
#define TWO_DIGIT_ESC_CODE(first,second) (0x200 + ((first) - '0')*10 + (second) - '0')
            escape_saw_char = TWO_DIGIT_ESC_CODE(escape_saw_char,c);
        }
        else if (escape_saw_char != 0) {
            if (c == '~') {
                if (escape_saw_char & 0x200) {
                    int func = escape_saw_char-0x200-16+5;
                    if ((func >= 5) && (func <= 22))    /* F5..F12 and shift-F1..shift-F8 are 5..22 (with some holes) */
                        return process_function_key(func);
                    escape_mode=0;
                    escape_saw_char=0;
                }
                else switch (escape_saw_char) {
                    case '2':   /* Insert */
                        insert_mode ^= 1;       /* toggle insert mode */
                        escape_mode=0;
                        escape_saw_char=0;
                        break;
                    case '3':   /* Delete*/
                        process_input_change_pos(+1); /* translate ESC-x to move right then backspace */
                        c = '\b';
                        escape_mode=0;
                        escape_saw_char=0;
                        goto parse_input;       /* parse this as a normal character */
                    case '1':   /* Home */
                        cmd_pos=0;              /* goto the beginning of the line */
                        escape_mode=0;
                        escape_saw_char=0;
                        break;
                    case '4':   /* End */
                        cmd_pos=cmd_len;        /* goto the end of the line */
                        escape_mode=0;
                        escape_saw_char=0;
                        break;
                    case '5':   /* PageUp */
                        escape_mode=0;
                        escape_saw_char=0;
                        return  "PageUp";
                        break;
                    case '6':   /* PageDown */
                        escape_mode=0;  /* ignore for now */
                        escape_saw_char=0;
                        return "PageDown";
                        break;
                    default:
                        escape_mode=0;
                        escape_saw_char=0;
                        goto parse_input;       /* parse this as a normal character */
                }
            }
        }
        else {
            unsigned int orig_cmd_pos = cmd_pos;
            switch (c) {        /* parse some vi style escape sequences and arrow keys */
                case 'h':
                    process_input_change_pos(-1);
                    break;
                case 'j':
                    process_input_change_index(+1);
                    break;
                case 'k':
                    process_input_change_index(-1);
                    break;
                case '$':
                    cmd_pos=cmd_len;
                    break;
                case '0':
                    cmd_pos=0;
                    break;
                case 'l':
                    process_input_change_pos(+1);
                    break;
                case 'D':
                    cmd_len=cmd_pos;
                    cmd[cmd_len] = 0;
                    break;
                case 'A':
                    cmd_pos=cmd_len;
                    insert_mode=1;
                    escape_mode=0;
                    break;
                case 'a':
                    process_input_change_pos(+1);
                    /* NOTE: fall through */
                case 'i':
                    insert_mode=1;
                    escape_mode=0;
                    break;
                case 'f':
                    find_orig_cmd_pos = cmd_pos;
                    find_mode=1;
                    escape_mode=0;
                    goto process_input_done;    /* skip delete_mode check */
                case 'R':
                    insert_mode=0;
                    escape_mode=0;
                    break;
                case 'b':
                    process_input_beginning_of_word();
                    break;
                case 'w':
                    process_input_next_word();
                    break;
                case 'r':
                    insert_mode=0;
                    escape_mode=0;
                    overwrite_once=1;
                    break;
                case '?':
                case ':':
                case '/':
                    escape_mode=0;
                    cmd_len=0;
                    cmd_pos=0;
                    goto parse_input;   /* parse this as a normal character */
                case '~':
                    if (islower((int)cmd[cmd_pos])) cmd[cmd_pos] = toupper((int)cmd[cmd_pos]);
                    else if (isupper((int)cmd[cmd_pos])) cmd[cmd_pos] = tolower((int)cmd[cmd_pos]);
                    process_input_change_pos(+1);
                    break;
                case 'c':
                    delete_mode=2;
                    goto process_input_done;    /* skip delete_mode check */
                case 'u':
                    process_input_undo();
                    break;
                case 'd':
                    if (delete_mode==1) {       /* dd is delete line */
                        cmd_len=0;
                        cmd_pos=0;
                        delete_mode=0;
                        break;
                    }
                    delete_mode=1;
                    goto process_input_done;    /* skip delete_mode check */
                case 'x':               /* translate ESC-x to move right then backspace */
                    process_input_change_pos(+1);
                    c = '\b';
                    goto parse_input;   /* parse this as a normal character */
                case 'n':
                    search_mode=1;
                    was_lookup = 0;
                    pattern_dir_reverse = 0;
                    goto search_pattern;
                case 'N':
                    search_mode=1;
                    was_lookup = 0;
                    pattern_dir_reverse = 1;
                    goto search_pattern;
                case '[':
                case 'O':
                    escape_saw_char=c;
                    break;
                case '\r':
                case '\n':
                    escape_mode=0;
                    goto parse_input;   /* parse this as a normal character */
                default:
                    escape_mode=0;
                    escape_saw_char=0;
                    goto parse_input;   /* parse this as a normal character */
            }
            if (delete_mode) {
                if (delete_mode==2) {   /* change mode (delete then insert) */
                    insert_mode=1;
                    escape_mode=0;
                }
                process_input_delete(orig_cmd_pos);
            }
        }
        goto process_input_done;
    }

    if (find_mode) {    /* find a character */
        char *p = strchr(&cmd[cmd_pos],c);
        if ((p!=NULL) && ((p-cmd+1) <= (int)cmd_len)) { /* ignore, not found or beyond range */
            cmd_pos = p-cmd;            /* move to next c */
        }
        find_mode=0;
        escape_mode=1;  /* "stay" in escape mode after find */
        if (delete_mode) {
            cmd_pos++;  /* also delete found character in find mode */
            if (cmd_pos > cmd_len) cmd_pos=cmd_len;
            process_input_delete(find_orig_cmd_pos);
        }
        goto process_input_done;
    }

parse_input:
    if (overwrite_once) {
        escape_mode=1;
        overwrite_once=0;
    }
    if ((c == '\t') || (c == '\x04'))   /* tab completion, scan help strings for completion possibilities */
    {
        char *token_start;

        remove_leading_spaces();
        process_input_draw_current();

        if (c == '\x04') tab_mode=2;    /* list all possibilities */
        if (tab_mode==0) {
            saved_avail_p=NULL;         /* start over */
            saved_suffix_size=0;        /* start over */
        }
        cmd[cmd_len] = 0;
        token_start = &cmd[cmd_pos] - (cmd_pos != 0);
        while ((token_start > cmd) && (*token_start != ' ')) token_start--;
        if (token_start==cmd) {         /* first token of command */
            if (tab_complete_data)
                tab_complete(cmd, tab_complete_data);
        }
        else {
            token_start++;      /* skip space */
            if (strncasecmp(cmd, "help", strlen("help")) == 0) {        /* for help <command> secondary lookup is help_commands */
                if (tab_complete_data)
                    tab_complete(token_start, tab_complete_data);
            }
#ifndef BDK_BUILD_HOST
            else if (__bdk_csr_get_tab_complete && strncasecmp(cmd, "csr", strlen("csr")) == 0) {
                /* Treat CSR as a special case that uses predefined tables */
                bdk_readline_tab_t *tab = __bdk_csr_get_tab_complete();
                if (tab)
                    tab_complete(token_start, tab);
            }
#endif
            else if (tab_complete_data) {
                const bdk_readline_tab_t *loc = tab_complete_data;
                while (loc->str)
                {
                    if (strncasecmp(cmd, loc->str, strlen(loc->str)) == 0) {
                        if (loc->next)
                            tab_complete(token_start, loc->next);
                        break;
                    }
                    loc++;
                }
            }
        }
        if (tab_mode==2)
            tab_mode=0;
        else
            tab_mode=1;
    }
    else if ((tab_mode==1) && (c==' ')) {       /* space after multi-tab selects and moves to next space or end */
        char *p = strchr(&cmd[cmd_pos],' ');
        if ((p==NULL) || ((p-cmd+1) > (int)cmd_len)) {
            cmd_pos = cmd_len;          /* move to end of command */
            process_input_commit_character(c);
        }
        else {
            cmd_pos = p-cmd+1;          /* move to just after next space */
        }
    }
    else if ((tab_mode=0)) {    /* NOTE: always false, but used to clear tab mode and keep "else if" strucure clean */
        /* never happens */
    }
    else if (c=='\033') {       /* escape character */
        escape_mode=1;
    }
    else if ((readline_flags & 0x1) && (c=='.'))   /* a period.  Change to '_' if in first word (i.e. before the first space.) */
    {
        char *p;
        for (p = &cmd[cmd_pos-1]; p > cmd; p--) {
          if (*p == ' ') break;
        }
        if (p <= cmd) c = '_';  /* in first word, change '.' to '_' for command compatibility with original traffic-gen */
        process_input_commit_character(c);
    }
    else if ((c>=32) && (c<=126))       /* normal character */
    {
        process_input_commit_character(c);
    }
    else if (c == '\x0c')       /* control-l erases/redraws sreeen */
    {
        //printf(GOTO_TOP ERASE_EOS);
    }
    else if (c == 3)       /* control-C */
    {
        return "\003";
    }
    else if (c == 26)       /* control-Z */
    {
        return "\032";
    }
    else if ((c == '\b') || (c == 127)) /* backspace or telnet backspace */
    {
        if (cmd_pos)
        {
            cmd_len--;
            cmd_pos--;
            if (cmd_pos < cmd_len) {
                memmove(&cmd[cmd_pos], &cmd[cmd_pos+1], cmd_len-cmd_pos+1);
            }
        }
    }
    else if ((c == '\r') || (c == '\n'))        /* CR/LF */
    {
        //was_lookup = (cmd[0] == '/') || (cmd[0] == '?') || (cmd[0] == ':');
        //search_mode = (cmd[0] == '/') || (cmd[0] == '?');
        // FIXME: Don't allow '/' searches when not in escape mode. It interferes with path names
        was_lookup = (cmd[0] == '?') || (cmd[0] == ':');
        search_mode = (cmd[0] == '?');
        cmd[cmd_len] = 0;
        cmd_pos = cmd_len;
        if ((cmd[0] == '!') || was_lookup) {
            int new_line;
            if ((cmd[1] == '!') || (cmd[1] == ':')) {
                process_input_change_index_to(history_index-1);
            }
            else if ((!search_mode) && (sscanf(cmd+1,"%d",&new_line)==1)) {
                process_input_change_index_to(new_line);
            }
            else {      /* search for first line starting with !pat */
                int len;
                int delta;
                strcpy(pattern,cmd+1);
                pattern_dir_delta = (cmd[0] == '/') ? 1 : -1;
                pattern_dir_reverse=0;
search_pattern:
                delta = pattern_dir_delta;
                if (pattern_dir_reverse) {
                    if (pattern_dir_delta == 1) delta= -1;
                    else delta = 1;
                }
                else if (delta == 0) delta = -1;        /* just in case.... */

                len=strlen(pattern);
#define PREV_HIST(x) ( ((x)+delta) & MAX_HISTORY_MASK )
                for (new_line=PREV_HIST(history_lookup_index);
                        (command_history[new_line][0]) && (new_line!=history_lookup_index);
                        new_line=PREV_HIST(new_line)) {
                    if (search_mode) {  /* search anywhere, NOTE case sensitive */
                        if (strstr(command_history[new_line],pattern)!=0) {
                            process_input_change_index_to(new_line);
                            break;
                        }
                    }
                    else {      /* only search from beginning, case insensitive */
                        if (strncasecmp(pattern,command_history[new_line],len)==0) {
                            process_input_change_index_to(new_line);
                            break;
                        }
                    }
                }
            }
        }
        process_input_draw_current();
        if (!(was_lookup || search_mode)) {     /* don't execute if only a lookup */
            if (remove_leading_spaces()) process_input_draw_current();
            if (cmd_len != 0) history_index = (history_index + 1) & MAX_HISTORY_MASK;
            history_lookup_index = history_index;
            cmd_len = 0;
            cmd_pos = 0;
            return cmd;
        }
        else {
            escape_mode=1;      /* "stay" in escape mode after search */
            search_mode=0;
        }
    }
process_input_done:
    process_input_draw_current();
    return NULL;
}

static uint64_t gettime(void)
{
#ifdef BDK_BUILD_HOST
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return 0;
    return (uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec;
#else
    uint64_t rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    return bdk_clock_get_count(BDK_CLOCK_TIME) / rate;
#endif
}


int bdk_readline_getkey(uint64_t timeout_us)
{
#ifdef BDK_BUILD_HOST
    /* Switch to RAW terminal IO */
    struct termios orig_termios;
    struct termios raw_termios;
    tcgetattr(fileno(stdin), &orig_termios);
    raw_termios = orig_termios;
    cfmakeraw(&raw_termios);
    tcsetattr(fileno(stdin), TCSANOW, &raw_termios);

    fd_set rset;
    struct timeval tv;
    FD_ZERO(&rset);
    FD_SET(fileno(stdin), &rset);
    tv.tv_sec = timeout_us / 1000000;
    tv.tv_usec = timeout_us % 1000000;

    if (select(fileno(stdin) + 1, &rset, NULL, NULL, &tv) > 0)
    {
        char c;
        int count = read(fileno(stdin), &c, 1);
        /* Restore normal RAW terminal IO */
        tcsetattr(fileno(stdin), TCSANOW, &orig_termios);
        if (count != 1)
            abort();
        return 0xff & c;
    }
    /* Restore normal RAW terminal IO */
    tcsetattr(fileno(stdin), TCSANOW, &orig_termios);
    return -1;
#else
    uint64_t stop_time = (timeout_us == (uint64_t)-1) ? timeout_us : gettime() + timeout_us;

    do
    {
        char c;
        if (read(0, &c, 1) == 1)
            return 0xff & c;
        bdk_wait_usec(100);
    } while (gettime() < stop_time);
    return -1;
#endif
}

/* NOTE: if prompt starts with "readline_flags=0x<value>;" where <value> is a hex number, it will be stripped off fromp prompt
 *   and used to set the flags.  If the ';' but everything up to x and a value is there, it will not be stripped, but still
 *   used.  If anything is different (added space before <value>, missing 0x, not there at all, etc....) flags will be 0.  */
const char *bdk_readline(const char *prompt, const bdk_readline_tab_t *tab, int timeout_us)
{
    uint64_t stop_time = gettime() + timeout_us;
    int prompt_offset = 0;
    readline_flags = 0;
    sscanf(prompt, "readline_flags=0x%x;%n", &readline_flags, &prompt_offset);
    cmd_prompt = prompt + prompt_offset;;
    tab_complete_data = tab;
    saved_avail_p = NULL;

    if (timeout_us < 1)
        stop_time = -1;

    process_input_draw_current();
    const char *result = NULL;
    while (1)
    {
        int c;
        fflush(stdout);
        do
        {
            uint64_t cur_time = gettime();
            if (cur_time >= stop_time)
            {
                reset_screen_draw(1);
                goto done;
            }
            uint64_t to = stop_time - cur_time;
            if (to > 10000000)
                to = 10000000;
            c = bdk_readline_getkey(to);
        } while (c == -1);

#ifndef BDK_BUILD_HOST
        if (c == 0xA3)
        {
            extern void __bdk_rpc_serve(void) __attribute__ ((weak));
            if (__bdk_rpc_serve)
            {
                __bdk_rpc_serve();
                continue;
            }
        }
#endif

        result = process_input(c);
        if (result)
        {
            putchar('\n');
            reset_screen_draw(0);
            goto done;
        }
    }
done:
    return result;
}

