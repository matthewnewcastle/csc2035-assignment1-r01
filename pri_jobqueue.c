/*
 * Replace the following string of 0s with your student number
 * 240674999
 */
#include <stdlib.h>
#include <stdbool.h>
#include "pri_jobqueue.h"

/*
 * Private helper to find the index of the highest priority job.
 * Returns -1 if queue is empty or no valid jobs found.
 */
static int find_best_index(pri_jobqueue_t *pjq)
{
    if (pjq->size == 0)
        return -1;

    int best_index = -1;
    int best_priority = 2147483647;

    for (int i = 0; i < pjq->size; i++)
    {
        if (pjq->jobs[i].priority < best_priority)
        {
            best_index = i;
            best_priority = pjq->jobs[i].priority;
        }
    }
    return best_index;
}

/*
 * TODO: you must implement this function that allocates a job queue and
 * initialise it.
 * Hint:
 * - see job_new in job.c
 */
pri_jobqueue_t *pri_jobqueue_new()
{
    pri_jobqueue_t *pjq = (pri_jobqueue_t *)malloc(sizeof(pri_jobqueue_t));

    if (pjq == NULL)
        return NULL;

    pri_jobqueue_init(pjq);

    return pjq;
}

/*
 * TODO: you must implement this function.
 */
void pri_jobqueue_init(pri_jobqueue_t *pjq)
{
    if (pjq == NULL)
        return;

    pjq->buf_size = JOB_BUFFER_SIZE;
    pjq->size = 0;

    for (int i = 0; i < pjq->buf_size; i++)
        job_init(&pjq->jobs[i]);
}

/*
 * TODO: you must implement this function.
 * Hint:
 *      - if a queue is not empty, and the highest priority job is not in the
 *      last used slot on the queue, dequeueing a job will result in the
 *      jobs on the queue having to be re-arranged
 *      - remember that the job returned by this function is a copy of the job
 *      that was on the queue
 */
job_t *pri_jobqueue_dequeue(pri_jobqueue_t *pjq, job_t *dst)
{
    if (pjq == NULL || pri_jobqueue_is_empty(pjq))
        return NULL;

    int best_index = find_best_index(pjq);

    job_t *j = job_copy(&pjq->jobs[best_index], dst);

    for (int i = best_index; i < pjq->size - 1; i++)
        job_copy(&pjq->jobs[i + 1], &pjq->jobs[i]);

    pjq->size--;

    job_init(&pjq->jobs[pjq->size]);

    return j;
}

/*
 * TODO: you must implement this function.
 * Hints:
 * - if a queue is not full, and if you decide to store the jobs in
 *      priority order on the queue, enqueuing a job will result in the jobs
 *      on the queue having to be re-arranged. However, it is not essential to
 *      store jobs in priority order (it simplifies implementation of dequeue
 *      at the expense of extra work in enqueue). It is your choice how
 *      you implement dequeue (and enqueue) to ensure that jobs are dequeued
 *      by highest priority job first (see pri_jobqueue.h)
 * - remember that the job passed to this function is copied to the
 *      queue
 */
void pri_jobqueue_enqueue(pri_jobqueue_t *pjq, job_t *job)
{
    if (pjq == NULL || job == NULL || pri_jobqueue_is_full(pjq) || job->priority == 0)
        return;

    if (job_copy(job, &pjq->jobs[pjq->size]) != NULL)
        pjq->size++;
}

/*
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_empty(pri_jobqueue_t *pjq)
{
    if (pjq == NULL || pjq->size == 0)
        return true;

    return false;
}

/*
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_full(pri_jobqueue_t *pjq)
{
    if (pjq == NULL || pjq->size == pjq->buf_size)
        return true;

    return false;
}

/*
 * TODO: you must implement this function.
 * Hints:
 *      - remember that the job returned by this function is a copy of the
 *      highest priority job on the queue.
 *      - both pri_jobqueue_peek and pri_jobqueue_dequeue require copying of
 *      the highest priority job on the queue
 */
job_t *pri_jobqueue_peek(pri_jobqueue_t *pjq, job_t *dst)
{
    if (pjq == NULL || pri_jobqueue_is_empty(pjq))
        return NULL;

    return job_copy(&pjq->jobs[find_best_index(pjq)], dst);
}

/*
 * TODO: you must implement this function.
 */
int pri_jobqueue_size(pri_jobqueue_t *pjq)
{
    if (pjq == NULL)
        return 0;

    return pjq->size;
}

/*
 * TODO: you must implement this function.
 */
int pri_jobqueue_space(pri_jobqueue_t *pjq)
{
    if (pjq == NULL)
        return 0;

    return pjq->buf_size - pjq->size;
}

/*
 * TODO: you must implement this function.
 *  Hint:
 *      - see pri_jobqeue_new
 */
void pri_jobqueue_delete(pri_jobqueue_t *pjq)
{
    if (pjq == NULL)
        return;

    free(pjq);
}
