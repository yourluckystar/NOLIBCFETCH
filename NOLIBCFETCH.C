/*
 * NOLIBCFETCH(1) - nolibc fetch in asm+c .3
 */

#define SYS_exit 60
#define SYS_uname 63
#define SYS_sysinfo 99

struct utsname {
        char sysname[65];         /* os name (linux)              */
        char nodename[65];        /* weird name for hostname      */
        char release[65];         /* example x.x.x-arch1-x        */
        char version[65];         /* dont think ill use this      */
        char machine[65];         /* hardware identified (x86_64) */
};
struct utsname sys_info;

struct infolines {
        const char *text;
        const char *data;
        const char *newln;
};
struct infolines lines[] = {
        { ">os ", sys_info.sysname, "\n" },
        { ">host ", sys_info.nodename, "\n" }
};

static void err(const char *fmt, ...);
static void itoa(int num, char *buf);
static unsigned long strlen(const char *s);
static void print_sysinfo(void);

void
err(const char *fmt, ...)
{
        /* this should be replaced with
         * something better xd */
        char *__progname = "NOLIBCFETCH";

        write(1, __progname, strlen(__progname));
        write(1, ": ", 2);
        write(1, fmt, strlen(fmt));
        exit(-1);
}

/* not a fully implemented itoa because i only need base 10
 * and as far as i know i dont need to check for negative numbers
 * (unless i do in which case yell at me ty) */
void
itoa(int num, char *buf)
{
        int i = 0;
        int j, k;

        if (num == 0) {
                buf[0] = '0';
                buf[1] = '\0';
                return;
        }

        while (num > 0) {
                buf[i++] = num % 10 + '0';
                num /= 10;
        }
        buf[i] = '\0';

        for (j = 0, k = i - 1; j < k; j++, k--) {
                char tmp = buf[j];
                buf[j] = buf[k];
                buf[k] = tmp;
        }
}

unsigned long
strlen(const char *s)
{
        unsigned int len = 0;
        while (s[len]) ++len;
        return len;
}

void
print_sysinfo(void)
{
        int i;
        long rv;        /* return value */
        unsigned short rows = sizeof(lines) / sizeof(lines[0]);

        /* call sys_uname and store return value
         * into utsname struct */
        rv = uname(SYS_uname, (long)&sys_info);
        if (rv != 0) {
                err("syscall uname (63) failed\n");
        }

        /* print each line with a simple loop
         * but might have to modify later */
        for (i = 0; i < rows; i++) {
                write(1, lines[i].text, strlen(lines[i].text));
                write(1, lines[i].data, strlen(lines[i].data));
                write(1, lines[i].newln, strlen(lines[i].newln));
        }
}

int
main(int argc, char *argv[])
{
        /* add arg handling later */
        print_sysinfo();

        return 0;
}
