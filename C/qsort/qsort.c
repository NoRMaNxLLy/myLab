#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        int width;
        int height;
} rectangle;

int numcmp(const void* n1, const void* n2);
int numcmp_desc(const void* n1, const void* n2);
int compare_areas(const void* a_ptr, const void* b_ptr);
int compare_areas_desc(const void* a_ptr, const void* b_ptr);
int compare_strings(const void* a_ptr, const void* b_ptr);
int compare_strings_desc(const void* a_ptr, const void* b_ptr);

int main()
{
//        int i;
//        int scores[] = {543,323,32,554,11,3,112};
//
//        qsort(scores, 7, sizeof(int), numcmp);
//
//        for (i = 0; i < 7; i++)
//                printf("%d ", scores[i]);
//        printf("\n");
//
//        qsort(scores, 7, sizeof(int), numcmp_desc);
//
//        for (i = 0; i < 7; i++)
//                printf("%d ", scores[i]);
//        printf("\n");


//        rectangle rectangles[] = {{5, 3}, {4, 7}, {8, 2}};
//
//        qsort(rectangles, 3, sizeof(rectangle), compare_areas);
//
//        int i;
//
//        for (i = 0; i < 3; i++) {
//                printf("%d: %d %d %d\n", i, rectangles[i].width,
//                                rectangles[i].height,
//                                rectangles[i].width *
//                                rectangles[i].height);
//        }


        char *names[] = {"Mohammed", "Ali", "Osama"};

        qsort(names, 3, sizeof(char*), compare_strings_desc);

        int i;
        for (i = 0; i < 3; i++) {
                printf("%s\n", names[i]);
        }
}

int numcmp(const void* n1, const void* n2)
{
        /* n1 > n2 : >0, n1 = n2: =0, n1 < n2: <0 */
        return *(int*)n1 - *(int*)n2;
}

int numcmp_desc(const void* n1, const void* n2)
{
        return *(int*)n2 - *(int*)n1;
}

int compare_areas(const void* a_ptr, const void* b_ptr)
{
        rectangle *a = (rectangle*) a_ptr;
        rectangle *b = (rectangle*) b_ptr;

        return (a->height * a->width) - (b->height * b->width);
}

int compare_strings(const void* a_ptr, const void* b_ptr)
{
        char **a = (char**)a_ptr;
        char **b = (char**)b_ptr;

        return strcmp(*a, *b);
}

int compare_areas_desc(const void* a_ptr, const void* b_ptr)
{
        return - compare_areas(a_ptr, b_ptr);
}

int compare_strings_desc(const void* a_ptr, const void* b_ptr)
{
        return -compare_strings(a_ptr, b_ptr);
}
