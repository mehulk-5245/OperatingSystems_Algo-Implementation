#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int opt_a;
int opt_t;
int opt_r;
int MAX;
int THREAD_MAX;
int *a;
struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
};
void merge(int low, int mid, int high)
{

	int n1 = mid - low + 1;
    int n2 = high - mid;
	int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));
	int i,j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];
	int k = low;
	i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // remaining values from left
    while (i < n1)
        a[k++] = left[i++];

    // remaining values from right
    while (j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

// merge sort
void merge_sort(int low, int high)
{
	int mid = low + (high - low) / 2;
	if (low < high) {
       
        merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);  //merge
    }
}

//  multi-threading
void * merge_sort123(void *arg)
{
    struct tsk *tsk = arg;
    int low;
    int high;
	low = tsk->tsk_low;
    high = tsk->tsk_high;
	int mid = low + (high - low) / 2;
	if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
	return 0;
}
int main(int argc, char **argv)
{
    char *cp;
    struct tsk *tsk;
	--argc;
    ++argv;
	printf("Enter the no of elements you want to sort.\n");
	printf("Elemets will be generated randomly:");
	int MAX;
	scanf("%d",&MAX);
	printf("Array of Random elements:");
    THREAD_MAX = 4;
	opt_a = 1;
	for (; argc > 0; --argc, ++argv) {
        cp = *argv;
        if (*cp != '-')
            break;
		switch (cp[1]) {
        case 'M':  // count of array
            MAX = atoi(cp + 2);
            break;

        case 'T':  // no. of threads
            THREAD_MAX = atoi(cp + 2);
            break;

        case 'a':  // change
            opt_a = !opt_a;
            break;

        case 'r':  
            opt_r = !opt_r;
            break;

        case 't':  
            opt_t = !opt_t;
            break;

        default:
            break;
        }
    }
	a = malloc(sizeof(int) * MAX);
	if (opt_t)
        printf("ORIG:");
    for (int i = 0; i < MAX; i++) {
        if (opt_r)
            a[i] = MAX - i;
        else
            a[i] = rand() % 100;
            
            printf("%d ",a[i]);
        if (opt_t)
            printf(" %d", a[i]);
    }
    if (opt_t)
        printf("\n");

    pthread_t threads[THREAD_MAX];
    struct tsk tsklist[THREAD_MAX];

    int len = MAX / THREAD_MAX;

    if (opt_t)
        printf("THREADS:%d MAX:%d LEN:%d\n", THREAD_MAX, MAX, len);

    int low = 0;

    for (int i = 0; i < THREAD_MAX; i++, low += len) {
        tsk = &tsklist[i];
        tsk->tsk_no = i;

        if (opt_a) {
            tsk->tsk_low = low;
            tsk->tsk_high = low + len - 1;
            if (i == (THREAD_MAX - 1))
                tsk->tsk_high = MAX - 1;
        }

        else {
            tsk->tsk_low = i * (MAX / THREAD_MAX);
            tsk->tsk_high = (i + 1) * (MAX / THREAD_MAX) - 1;
        }

        if (opt_t)
            printf("RANGE %d: %d %d\n", i, tsk->tsk_low, tsk->tsk_high);
    }

    // creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++) {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, merge_sort123, tsk);
    }

    // joining threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);

    
    if (opt_t) {
        for (int i = 0; i < THREAD_MAX; i++) {
            tsk = &tsklist[i];
            printf("SUB %d:", tsk->tsk_no);
            for (int j = tsk->tsk_low; j <= tsk->tsk_high; ++j)
                printf(" %d", a[j]);
            printf("\n");
        }
    }

    
    if (opt_a) {
        struct tsk *tskm = &tsklist[0];
        for (int i = 1; i < THREAD_MAX; i++) {
            struct tsk *tsk = &tsklist[i];
            merge(tskm->tsk_low, tsk->tsk_low - 1, tsk->tsk_high);
        }
    }
    else {
        merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
        merge(MAX / 2, MAX / 2 + (MAX - 1 - MAX / 2) / 2, MAX - 1);
        merge(0, (MAX - 1) / 2, MAX - 1);
    }

    
    printf("\n\nSorted array->\n");
    for (int i = 0; i < MAX; i++)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}
/*Output:
Enter the no of elements you want to sort.
Elemets will be generated randomly:20
Array of Random elements:83 86 77 15 93 35 86 92 49 21 62 27 90 59 63 2640 26 72 36

Sorted array-> 
15 21 26 26 27 35 36 40 49 59 62 63 72 77 83 86 86 90 92 93
*/
