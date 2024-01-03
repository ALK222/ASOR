#include <sched.h>
#include <sys/resource.h>
#include <stdio.h>

int main()
{
    int sched = sched_getscheduler(0);

    printf("Planificador: ");
    switch (sched)
    {
    case SCHED_OTHER:
        printf("Other\n");
        break;
    case SCHED_FIFO:
        printf("FIFO\n");
        break;
    case SCHED_RR:
        printf("RR\n");
        break;
    default:
        printf("Ni idea\n");
        break;
    }

    struct sched_param param;
    sched_getparam(0, &param);

    int max = sched_get_priority_max(sched);
    int min = sched_get_priority_min(sched);

    printf("Prioridad proceso: %d, Max prioridad: %d, Min prioridad: %d\n", param.sched_priority, max, min);

    return 0;
}
