/*
 * Replace the following string of 0s with your student number
 * 240674999
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

/*
 * DO NOT EDIT the job_new function.
 */
job_t *job_new(pid_t pid, unsigned int id, unsigned int priority,
               const char *label)
{
    return job_set((job_t *)malloc(sizeof(job_t)), pid, id, priority, label);
}

/*
 * TODO: you must implement this function
 */
job_t *job_copy(job_t *src, job_t *dst)
{
    if (src == NULL)
        return NULL;

    if (strnlen(src->label, MAX_NAME_SIZE) != MAX_NAME_SIZE - 1)
        return NULL;

    if (src == dst)
        return dst;

    if (dst == NULL)
    {
        dst = (job_t *)malloc(sizeof(job_t));
        if (dst == NULL)
            return NULL;
    }

    *dst = *src;

    return dst;
}

/*
 * TODO: you must implement this function
 */
void job_init(job_t *job)
{
    if (job == NULL)
        return;

    job->pid = 0;
    job->id = 0;
    job->priority = 0;
    snprintf(job->label, MAX_NAME_SIZE, "%s", PAD_STRING);
}

/*
 * TODO: you must implement this function
 */
bool job_is_equal(job_t *j1, job_t *j2)
{
    if (j1 == j2)
        return true;
    if (j1 == NULL || j2 == NULL)
        return false;
    if (j1->pid != j2->pid)
        return false;
    if (j1->id != j2->id)
        return false;
    if (j1->priority != j2->priority)
        return false;
    if (strncmp(j1->label, j2->label, MAX_NAME_SIZE) != 0)
        return false;

    return true;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job
 *      labels
 */
job_t *job_set(job_t *job, pid_t pid, unsigned int id, unsigned int priority,
               const char *label)
{
    if (job == NULL)
        return NULL;

    job->pid = pid;
    job->id = id;
    job->priority = priority;

    if (label == NULL)
        snprintf(job->label, MAX_NAME_SIZE, "%s", PAD_STRING);
    else
        snprintf(job->label, MAX_NAME_SIZE, "%s%s", label, PAD_STRING);

    return job;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see malloc and calloc system library functions for dynamic allocation,
 *      and the documentation in job.h for when to do dynamic allocation
 */
char *job_to_str(job_t *job, char *str)
{
    if (job == NULL)
        return NULL;

    if (strnlen(job->label, MAX_NAME_SIZE) != MAX_NAME_SIZE - 1)
        return NULL;

    if (str == NULL)
    {
        str = malloc(JOB_STR_SIZE);
        if (str == NULL)
            return NULL;
    }

    snprintf(str, JOB_STR_SIZE, JOB_STR_FMT, job->pid, job->id, job->priority, job->label);
    return str;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see the hint for job_to_str
 */
job_t *str_to_job(char *str, job_t *job)
{
    if (str == NULL)
        return NULL;

    if (strnlen(str, JOB_STR_SIZE) != JOB_STR_SIZE - 1)
        return NULL;

    if (job == NULL)
    {
        job = malloc(sizeof(job_t));
        if (job == NULL)
            return NULL;
    }

    char label[MAX_NAME_SIZE];
    int amount = sscanf(str, JOB_STR_FMT, &job->pid, &job->id, &job->priority, label);
    if (amount != 4)
        return NULL;

    snprintf(job->label, MAX_NAME_SIZE, "%s", label);

    return job;
}

/*
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t *job)
{
    if (job == NULL)
        return;
    free(job);
}