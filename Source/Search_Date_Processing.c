
#include "Search_Date_Functions.h"

void Print(TreeNode *root, int depth);

void PrintFindDate(TreeNode *root, time_t key, int opt, int controll) {
    int result;
    if (root == NULL) {
        return;
    }

    time_t timestamp;
    ParseDateTime(root->data.date, &timestamp);

    if (controll == 0) {
        result = SearchDate(timestamp, key, key);
    } else if (controll == 1) {
        result = SearchLastHours(timestamp, opt);
    } else if (controll == 2) {
        result = SearchLastDay(timestamp, opt);
    } else if (controll == 3) {
        result = SearchLastMonth(timestamp, opt);
    }

    if (result == 1) {
        ReadNDat(root->data.start, root->data.end);
        Print(root, 1);
    }

    PrintFindDate(root->firstChild, key, opt, controll);
    PrintFindDate(root->nextSibling, key, opt, controll);
}

void ProcessData(TreeNode *root) {

    if (strstr(In_Date, "h") != NULL || strstr(In_Date, "H") != NULL) {
        int val = atoi(In_Date);
        PrintFindDate(root, 0, val, 1);
    }

    else if (strstr(In_Date, "d") != NULL || strstr(In_Date, "D") != NULL) {
        int val = atoi(In_Date);
        PrintFindDate(root, 0, val, 2);
    }

    else if (strstr(In_Date, "m") != NULL || strstr(In_Date, "M") != NULL) {
        int val = atoi(In_Date);
        PrintFindDate(root, 0, val, 3);
    }

    else {
        find = FindDateNode;
        NDatPrintFind(root, In_Date, find);
    }
}
