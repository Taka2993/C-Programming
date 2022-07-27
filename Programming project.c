#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>



#define MAX_CONTENT_SIZE 30

typedef struct {
    int month;
    int day;
    int hour;
}TIME_DATA;

typedef struct _schedule
{
    TIME_DATA start;
    TIME_DATA end;
    char content[MAX_CONTENT_SIZE];
    struct _schedule* next;
    struct _schedule* prev;
}SCHEDULE;


int TimeDataChk(const TIME_DATA * p)
{
    int chkday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };


    if(p->month < 1 || p->month > 12) return -1;
    if(p->day < 1 || p->day > chkday[p->month]) return -1;
    if(p->hour < 0 || p->hour > 23) return -1;
    return 0;
}


int cmpTimeData(const TIME_DATA p, const TIME_DATA q)
{
    if(p.month > q.month) return 1;
    else if(p.month < q.month) return -1;

    if(p.day > q.day) return 1;
    else if(p.day < q.day) return -1;

    if(p.hour > q.hour) return 1;
    else if(p.hour < q.hour) return -1;

    return 0;
}



int AddEvent(SCHEDULE** head, SCHEDULE* add)
{
    if(head == NULL) return -1;
    if(add == NULL) return -1;
    if(TimeDataChk(&add->start)) return -1;
    if(TimeDataChk(&add->end)) return -1;

    SCHEDULE* p = *head;

    if(p==NULL) {
        *head = add;
        return 0;
    }

    while(p!=NULL) {
        int mch = cmpTimeData(p->start, add->start);
        if( mch == 0 )mch = cmpTimeData(p->end, add->end);

        if(mch >= 0){
            add->next = p;
            add->prev = p->prev;
            if(add->prev != NULL) add->prev->next = add;
            else *head = add;
            p->prev = add;
            break;
        }
        if(p->next == NULL) {
            p->next = add;
            add->prev = p;
            break;
        }
        p = p->next;
    }
    return 0;
}


int DeleteEvent(SCHEDULE** head, SCHEDULE* del)
{
    if(head == NULL) return -1;
    if(del == NULL) return -1;
    if(TimeDataChk(&del->start)) return -1;
    if(TimeDataChk(&del->end)) return -1;

    SCHEDULE* p = *head;
    int s_data = del->start.month * 10000 + del->start.day * 100 + del->start.hour;
    int e_data = del->end.month   * 10000 + del->end.day   * 100 + del->end.hour;

    int count = 0;

    while(p!=NULL) {
        int s_p = p->start.month * 10000 + p->start.day * 100 + p->start.hour;
        int e_p = p->end.month   * 10000 + p->end.day   * 100 + p->end.hour;

        if(s_p == s_data && e_p == e_data) {
            SCHEDULE* q = p->prev;
            if(q) q->next = p->next;
            q = p->next;
            if(q) q->prev = p->prev;
            free(p);
            p = q;
            count++;
        }
        else {
            p = p->next;
        }
    }
    if(count) printf("Delete %d Events\n", count);
    else printf("No Such Event.... \n");

    return 0;
}



SCHEDULE* CreateEvent(TIME_DATA s , TIME_DATA e , char * content)
{
    SCHEDULE* sch = (SCHEDULE*)calloc(1, sizeof(SCHEDULE));
    if(sch == NULL) return NULL;

    sch->start = s;
    sch->end = e;
    if(strlen(content) >= MAX_CONTENT_SIZE) content[MAX_CONTENT_SIZE-1] = '\0';
    strcpy(sch->content, content);
    sch->next = NULL;
    sch->prev = NULL;
    return sch;
}

void printAllSchedule(SCHEDULE* head)
{
    SCHEDULE* p = head;

    printf("\n----\n" );
    while(p!=NULL) {
        printf("%-30s : %02d/%02d %02d:00 - %02d/%02d %02d:00\n",
               p->content, p->start.month, p->start.day, p->start.hour,
               p->end.month, p->end.day, p->end.hour);
        p = p->next;
    }
    printf("---- eof \n");
}

unsigned long FreeTimeSearch(SCHEDULE* head, int mon, int day)
{
    unsigned long ret = 0;
    SCHEDULE *p = head;
    int d = mon * 100 + day;

    while(p) {
        int s = p->start.month*100 + p->start.day;
        int e = p->end.month*100 + p->end.day;

        if(s > d) break;
        else if(e < d) { p = p->next; continue; }

        int s_tim = (s==d) ? p->start.hour : 0;
        int e_tim = (s==d) ? p->end.hour : 23;

        for(int i = s_tim; i<=e_tim; i++) ret |= (0x000001 << i);

        p = p->next;
    }
    return ret;
}


void printFreeSearch(SCHEDULE* head, TIME_DATA s, TIME_DATA e)
{
    int chkday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int s_d;
    int e_d;
    unsigned long times;

    printf("\n");
    printf("mm/dd | 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23\n");
    printf("------+------------------------------------------------------------------------\n");


    for(int i = s.month; i<=e.month; i++) {
        s_d = 1;
        e_d = chkday[e.month];

        if(i==s.month) s_d = s.day;

        if(i==e.month) e_d = e.day;

        for(int j = s_d; j <= e_d; j++) {
            times = FreeTimeSearch(head, i, j);
            printf("%02d/%02d | ", i, j);
            for(int i = 0; i<24; i++) {
                if(times & (0x000001<<i)) printf(" x ");
                else printf(" o ");
            }
            printf("\n");
        }
    }
    printf("------+------------------------------------------------------------------------\n\n");
}

void DeleteEventList(SCHEDULE** head)
{
    SCHEDULE* p = *head;
    SCHEDULE* q;

    while(p) {
        q = p->next;
        free(p);
        p = q;
    }
    *head = NULL;
}

void SaveFile(SCHEDULE* head)
{
    SCHEDULE* p = head;
    FILE* fp;

    fp = fopen("data.dat", "wb");
    while(p) {
        fwrite(&p->start, sizeof(TIME_DATA), 1, fp);
        fwrite(&p->end, sizeof(TIME_DATA), 1, fp);
        fwrite(&p->content, MAX_CONTENT_SIZE, 1, fp);
        p = p->next;
    }
    fclose(fp);
}
void ReadFile(SCHEDULE** head)
{
    SCHEDULE p;
    FILE* fp;

    fp = fopen("data.dat", "rb");
    while(1) {
        size_t size;
        size = fread(&(p.start), sizeof(TIME_DATA), 1, fp);
        if(size == 0) break;
        size = fread(&(p.end), sizeof(TIME_DATA), 1, fp);
        if(size == 0) break;
        size = fread(p.content, MAX_CONTENT_SIZE, 1, fp);
        if(size == 0) break;

        SCHEDULE* q = CreateEvent(p.start,p.end,p.content);
        AddEvent(head, q);
    }
    fclose(fp);
}


SCHEDULE getEventDataInput(int ptn)
{
    int chkday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; //??????????2021????
    SCHEDULE s;
    int ret;

    while(1) {
        printf(" input %s schedule Start Month (1-12) >>> ",(ptn==1)?"delete":"add");
        ret = scanf("%d", &s.start.month);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.start.month < 1 || s.start.month > 12) {
            printf("Month Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }
    while(1) {
        printf(" input %s schedule Start day (1-%d) >>> ", (ptn==1) ? "delete" : "add", chkday[s.start.month]);
        ret = scanf("%d", &s.start.day);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.start.day < 1 || s.start.day > chkday[s.start.month]) {
            printf("Day Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }
    while(1) {
        printf(" input %s schedule Start Hour(0-23) **Input time is included in the schedule**  >>> ", (ptn==1) ? "delete" : "add");
        ret = scanf("%d", &s.start.hour);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.start.hour < 0 || s.start.hour > 23) {
            printf("Time Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }

    while(1) {
        printf(" input %s schedule End Month (1-12) >>> ", (ptn==1) ? "delete" : "add");
        ret = scanf("%d", &s.end.month);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.end.month < 1 || s.end.month > 12) {
            printf("Month Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }
    while(1) {
        printf(" input %s schedule End day (1-%d) >>> ", (ptn==1) ? "delete" : "add", chkday[s.end.month]);
        ret = scanf("%d", &s.end.day);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.end.day < 1 || s.end.day > chkday[s.end.month]) {
            printf("Day Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }
    while(1) {
        printf(" input %s schedule End Hour(0-23) **Input time is included in the schedule**  >>> ", (ptn==1) ? "delete" : "add");
        ret = scanf("%d", &s.end.hour);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || s.end.hour < 0 || s.end.hour > 23) {
            printf("Time Input Error. TryAgain\n\n");
            continue;
        }
        break;
    }

    if(s.start.month*10000+s.start.day*100+s.start.hour > s.end.month*10000+s.end.day*100+s.end.hour) {
        printf("input Error ... Swap \"from\" and \"to\"\n");
        TIME_DATA t = s.start;
        s.start = s.end;
        s.end = t;
    }

    if(ptn != 1) {
        char txt[128] = { 0 };
        printf(" input schedule name (max %d chars)  >>> ", MAX_CONTENT_SIZE-1);
        ret = scanf("%s", txt);
        txt[MAX_CONTENT_SIZE-1] = 0;
        strcpy(s.content, txt);
    }
    return s;
}


int main(int argc ,char **argv)
{

    SCHEDULE* head = NULL;
    SCHEDULE *p;
    SCHEDULE s;
    TIME_DATA st, et;
    bool quitflg = false;
    int chkday[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; //??????????2021????

    int menu;
    int ret;

    while(1) {
        printf("menu---\n");
        printf(" 1 : Delete DataBase \n");
        printf(" 2 : Save DataBase to File\n");
        printf(" 3 : Read DataBase from File(editing data will be erased)\n");
        printf(" 4 : Add Event\n");
        printf(" 5 : Delete Event\n");
        printf(" 6 : Show Schedule\n");
        printf(" 7 : Search Free Time\n");
        printf(" 8 : Quit\n");
        printf(" ----\n");
        printf(" input menu no >>> ");

        ret = scanf("%d", &menu);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || menu < 1 || menu > 8) {
            printf("Menu No Error. TryAgain\n\n");
            continue;
        }

        switch(menu) {
            case 1:
                DeleteEventList(&head);
                printf("Delete Finished\n\n");
                break;
            case 2:
                SaveFile(head);
                printf("Save File Finished\n\n");
                break;
            case 3:
                if(head) DeleteEventList(&head);
                ReadFile(&head);
                printf("Read File Finished\n\n");
                break;
            case 4:
                s = getEventDataInput(0);
                p = CreateEvent(s.start, s.end, s.content);
                AddEvent(&head, p);
                printf("Add Event Finished\n\n");
                break;
            case 5:
                s = getEventDataInput(1);
                DeleteEvent(&head, &s);
                printf("Delete Event Finished\n\n");
                break;
            case 6:
                printAllSchedule(head);
                break;
            case 7:
                printf(" Input Serch \"from\" and \"to\" Month and day \n");
                while(1) {
                    printf(" Input Serch \"from\" Month (1-12) >>> ");
                    ret = scanf("%d", &st.month);
                    while((fgetc(stdin))!='\n') {};
                    if(ret != 1 || st.month < 1 || st.month > 12) {
                        printf("Month Input Error. TryAgain\n\n");
                        continue;
                    }
                    break;
                }
                while(1) {
                    printf(" Input Serch \"from\" day(1-%d) >>> ", chkday[st.month]);
                    ret = scanf("%d", &st.day);
                    while((fgetc(stdin))!='\n') {};
                    if(ret != 1 || st.day < 1 || st.day > chkday[st.month]) {
                        printf("Day Input Error. TryAgain\n\n");
                        continue;
                    }
                    break;
                }
                while(1) {
                    printf(" Input Serch \"to\" Month (1-12) >>> ");
                    ret = scanf("%d", &et.month);
                    while((fgetc(stdin))!='\n') {};
                    if(ret != 1 || et.month < 1 || et.month > 12) {
                        printf("Month Input Error. TryAgain\n\n");
                        continue;
                    }
                    break;
                }
                while(1) {
                    printf(" Input Serch \"to\" day(1-%d) >>> ", chkday[et.month]);
                    ret = scanf("%d", &et.day);
                    while((fgetc(stdin))!='\n') {};
                    if(ret != 1 || et.day < 1 || et.day > chkday[et.month]) {
                        printf("Day Input Error. TryAgain\n\n");
                        continue;
                    }
                    break;
                }
                printFreeSearch(head,st,et);
                break;
            case 8:
                DeleteEventList(&head);
                quitflg = true;
                break;
        }
        if(quitflg) break;
    }

    return 0;
}
