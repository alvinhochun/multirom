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

#include <stdlib.h>
#include <unistd.h>
#include <cutils/android_reboot.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mount.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "multirom_main.h"
#include "multirom_misc.h"
#include "framebuffer.h"
#include "log.h"
#include "version.h"
#include "util.h"

#define EXEC_MASK (S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define KEEP_REALDATA "/dev/.keep_realdata"
#define REALDATA "/realdata"

static void __attribute__((noreturn)) do_reboot(int exit)
{
    sync();
    umount(REALDATA);

    if(exit & EXIT_REBOOT_RECOVERY)         android_reboot(ANDROID_RB_RESTART2, 0, "recovery");
    else if(exit & EXIT_REBOOT_BOOTLOADER)  android_reboot(ANDROID_RB_RESTART2, 0, "bootloader");
    else if(exit & EXIT_POWEROFF)           android_reboot(ANDROID_RB_POWEROFF, 0, NULL);
    else                                    android_reboot(ANDROID_RB_RESTART, 0, NULL);

    while(1);
}

static __attribute__((noreturn)) void do_kexec(void)
{
    sync();
    umount(REALDATA);

    execl("/multirom/kexec", "/multirom/kexec", "-e", NULL);

    ERROR("kexec -e failed! (%d: %s)", errno, strerror(errno));
    multirom_emergency_reboot_recovery();
    while(1);
}

int main(int argc, char *argv[])
{
    int i;
    for(i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "-v") == 0)
        {
            printf("%d%s\n", VERSION_MULTIROM, VERSION_DEV_FIX);
            fflush(stdout);
            return 0;
        }
    }

    srand(time(0));
    klog_init();

    // output all messages to dmesg,
    // but it is possible to filter out INFO messages
    klog_set_level(6);

    ERROR("Running MultiROM v%d%s\n", VERSION_MULTIROM, VERSION_DEV_FIX);

    int exit = multirom();

    if(exit >= 0)
    {
        if(exit & EXIT_REBOOT_MASK)
        {
            do_reboot(exit);
        }

        if(exit & EXIT_KEXEC)
        {
            do_kexec();
        }
    }

    vt_set_mode(0);

    return 0;
}
