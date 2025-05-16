/*
 * NOLIBCFETCH(1) - nolibc fetch in asm+c .3
 */

#define SYS_exit 60
#define SYS_uname 63
#define SYS_sysinfo 99

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
        /* TODO */
}

int
main(int argc, char *argv[])
{
        /* add arg handling later */
        print_sysinfo();

        return 0;
}
