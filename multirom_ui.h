/*
 * This file is part of MultiROM.
 *
 * MultiROM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MultiROM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MultiROM.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MULTIROM_UI_H
#define MULTIROM_UI_H

#include "multirom_main.h"
#include "multirom_misc.h"
#include "multirom_partitions.h"
#include "multirom_rom.h"
#include "multirom_status.h"
#include "input.h"
#include "listview.h"

enum
{
    TAB_INTERNAL = 0,
    TAB_EXT_SD,
    TAB_USB,
    TAB_MISC,

    TAB_COUNT
};

#include "multirom_ui_themes.h"

enum
{
    UI_EXIT_BOOT_ROM          = 1,
    UI_EXIT_REBOOT            = 2,
    UI_EXIT_REBOOT_RECOVERY   = 3,
    UI_EXIT_REBOOT_BOOTLOADER = 4,
    UI_EXIT_POWEROFF          = 5
};

enum
{
    CLRS_BLUE    = 0,
    CLRS_PURPLE  = 1,
    CLRS_GREEN   = 2,
    CLRS_ORANGE  = 3,
    CLRS_RED     = 4,
    CLRS_BROWN   = 5,

    CLRS_MAX
};

extern uint32_t CLR_PRIMARY;
extern uint32_t CLR_SECONDARY;

int multirom_ui(struct multirom_rom **to_boot, struct multirom_romdata **boot_profile);
void multirom_ui_init_header(void);
void multirom_ui_header_select(int tab);
void multirom_ui_destroy_tab(int tab);
int multirom_ui_touch_handler(touch_event *ev, void*);
int multirom_ui_destroy_msgbox(void);
void multirom_ui_switch(int tab);
void multirom_ui_fill_rom_list(listview *view, enum multirom_partition_type part_type);
void multirom_ui_auto_boot(void);
//void multirom_ui_refresh_usb_handler(void);
void multirom_ui_start_pong(int action);
void multirom_ui_setup_colors(int clr, uint32_t *primary, uint32_t *secondary);

void *multirom_ui_tab_rom_init(int tab_type);
void multirom_ui_tab_rom_destroy(tab_data_roms *data);
void multirom_ui_tab_rom_selected(listview_item *prev, listview_item *now);
void multirom_ui_tab_rom_boot_btn(int action);
void multirom_ui_tab_rom_confirmed(listview_item *it);
//void multirom_ui_tab_rom_refresh_usb(int action);
//void multirom_ui_tab_rom_update_usb(void *data);
void multirom_ui_tab_rom_set_empty(tab_data_roms *data, int empty, int tab_type);

void *multirom_ui_tab_misc_init(void);
void multirom_ui_tab_misc_destroy(void *data);
void multirom_ui_tab_misc_copy_log(int action);
void multirom_ui_tab_misc_change_clr(int clr);

void multirom_ui_reboot_btn(int action);

#endif
