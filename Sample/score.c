#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "../csv.h"

/**
 * @fn
 * @brief
 * 教科ごとの平均点を計算して返す
 * @param head 生徒リストの先頭ポインタ
 * @return 教科ごとの平均点のリスト
 */
subject_analysis_t *eachSubjectAverage(student_t *head) {
    subject_analysis_t *analysis = NULL;

    for (student_t* p = head; p != NULL; p = p->next) {
        subject_t *q;
        for (q = p->subjects; q != NULL; q = q->next) {
            analysis = addSubjectScore(q->name, q->score, analysis);
        }
    }

    subject_analysis_t *s;
    for (s = analysis; s != NULL; s = s->next) {
        unsigned int studentCount = countStudent(head);
        s->averageScore = s->sumScore / (float)studentCount;
    }
    return analysis;
}

/**
 * @fn
 * @brief
 * 生徒ごとの平均点を計算して表示する
 * @param head 生徒リストの先頭ポインタ
 */
void eachStudentAverage(student_t *head) {
    student_t *p;
    for (p = head; p != NULL; p = p->next) {
        p->sumScore = 0;
        subject_t *q;
        for (q = p->subjects; q != NULL; q = q->next) {
            p->sumScore += q->score;
        }
        p->averageScore = (float)p->sumScore / (float)subjectCount(p->subjects);
    }
}

/**
 * @fn
 * @brief
 * 生徒の合計点の平均を計算する
 * @param head 生徒リストの先頭ポインタ
 * @return 生徒の合計点の平均
 */
double totalAverage(student_t *head) {
    unsigned int studentCount = countStudent(head);
    unsigned int totalScore = 0;
    student_t *p;
    for (p = head; p != NULL; p = p->next) {
        totalScore += p->sumScore;
    }
    return totalScore / (double)(studentCount);
}

/**
 * @fn
 * @brief
 * 生徒ごとの得点情報を表形式で表示する
 * @param students 生徒リストの先頭のポインタ
 */
void printScores(student_t *students) {
    subject_analysis_t *analysis = eachSubjectAverage(students);
    eachStudentAverage(students);

    // 表のヘッダを表示
    printf("%5s ", "ID");
    subject_t *sbPtr = students->subjects;
    for (sbPtr = students->subjects; sbPtr != NULL; sbPtr = sbPtr->next) {
        printf("%5s ", sbPtr->name);
    }
    printf("Total\n");

    // 生徒ごとの得点情報を表示
    student_t *stPtr;
    for (stPtr = students; stPtr != NULL; stPtr = stPtr->next) {
        printf("%5d ", stPtr->num);
        for (sbPtr = stPtr->subjects; sbPtr != NULL; sbPtr = sbPtr->next) {
            printf("%5d ", sbPtr->score);
        }
        printf("%5d ", stPtr->sumScore);
        printf("\n");
    }
    printf("----------------------------------------\n");

    // 教科ごとの平均点を表示
    printf("%5s ", "Ave");
    subject_analysis_t *a;
    for (a = analysis; a != NULL; a = a->next) {
        printf("%5.1f ", a->averageScore);
    }
    printf("%5.1f\n", totalAverage(students));
    printf("\n");
}

int main (void) {
    student_t *students = readFile("score.csv");
    printScores(students);
    writeFile(students, "result.csv");
    return 0;
}