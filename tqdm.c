#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

const char *blocks[] = {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};
#define BLOCKS 8

void progress_bar(long long current, long long total)
{
    static time_t start;
    if (current == 0)
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
#endif

        start = time(NULL);
    }

    time_t now = time(NULL);
    unsigned long elapsed = (unsigned long)difftime(now, start);

    static int last_percent = -1;
    int percent = (int)((current * 100) / total);
    if (percent == last_percent)
        return;
    last_percent = percent;

    int width = 30;
    double ratio = (double)current / total;
    double filled_blocks = ratio * width * BLOCKS;
    int full = (int)(filled_blocks / BLOCKS);
    int partial = (int)(filled_blocks) % BLOCKS;

    printf("\r[");
    for (int i = 0; i < width; i++)
    {
        if (i < full)
            printf("%s", blocks[BLOCKS]);
        else if (i == full)
            printf("%s", blocks[partial]);
        else
            printf(" ");
    }
    printf("] %3d%% %lus", percent, elapsed);
    fflush(stdout);

    if (percent == 100)
        printf("\n");
}

int main()
{

    long long total = 100000000;

    for (long long i = 0; i <= total; i++)
    {
        progress_bar(i, total);
    }

    return 0;
}