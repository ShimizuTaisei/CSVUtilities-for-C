#include <stdio.h>
#include <math.h>

#include "student.h"

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
        for (subject_t* q = p->subjects; q != NULL; q = q->next) {
            analysis = addSubjectScore(q->name, q->score, analysis);
        }
    }

    for (subject_analysis_t* s = analysis; s != NULL; s = s->next) {
        unsigned int studentCount = countStudent(head);
        s->averageScore = (double)s->sumScore / (double)studentCount;
    }
    return analysis;
}

/**
 * @fn
 * @brief
 * 生徒ごとの平均点を計算して構造体に追加する
 * @param head 生徒リストの先頭ポインタ
 */
void eachStudentAverage(student_t *head) {
    for (student_t* p = head; p != NULL; p = p->next) {
        p->sumScore = 0;
        for (subject_t* q = p->subjects; q != NULL; q = q->next) {
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
    for (student_t* p = head; p != NULL; p = p->next) {
        totalScore += p->sumScore;
    }
    return totalScore / (double)(studentCount);
}

subject_analysis_t *calcStandardDeviation(student_t *students, subject_analysis_t *analyses) {
    subject_t *subject = NULL;
    double powerDeviationSum = 0;
    for (subject_analysis_t *analysis = analyses; analysis != NULL; analysis = analysis->next)
    {
        for (student_t *student = students; student != NULL; student = student->next)
        {
            subject = searchSubject(analysis->name, student->subjects);
            if (subject != NULL)
            {
                powerDeviationSum += pow(subject->score - analysis->averageScore, 2);
            }
        }
        analysis->standardDeviation = sqrt(powerDeviationSum / countStudent(students));
    }
    return analyses;
}

void calcTScore(student_t *students, subject_analysis_t *analyses)
{
    calcStandardDeviation(students, analyses);
    for (student_t *student = students; student != NULL; student = student->next)
    {
        for (subject_t *subject = student->subjects; subject != NULL; subject = subject->next)
        {
            subject_analysis_t *analysis = searchSubjectAnalysis(subject->name, analyses);
            if (analysis != NULL)
            {
                subject->tScore = (subject->score - analysis->averageScore) / analysis->standardDeviation * 10 + 50;
            }
        }
    }
}

/**
 * @fn
 * @brief
 * 生徒ごとの得点情報を表形式で表示する
 * @param students 生徒リストの先頭のポインタ
 */
void printScores(student_t *students) {
    subject_analysis_t *analysis = eachSubjectAverage(students);

    // 表のヘッダを表示
    printf("%5s ", "ID");
    subject_t *sbPtr;
    for (sbPtr = students->subjects; sbPtr != NULL; sbPtr = sbPtr->next) {
        printf("%5s ", sbPtr->name);
    }
    printf("Total\n");

    // 生徒ごとの得点情報を表示
    for (student_t* stPtr = students; stPtr != NULL; stPtr = stPtr->next) {
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
    for (subject_analysis_t* a = analysis; a != NULL; a = a->next) {
        printf("%5.1f ", a->averageScore);
    }
    printf("%5.1f\n", totalAverage(students));
    printf("\n");
}

void printTScore(student_t *students)
{
    subject_analysis_t *analysis = eachSubjectAverage(students);
    calcTScore(students, analysis);

    // 表のヘッダを表示
    printf("%5s ", "ID");
    subject_t *sbPtr;
    for (sbPtr = students->subjects; sbPtr != NULL; sbPtr = sbPtr->next) {
        printf("%5s ", sbPtr->name);
    }
    printf("Total\n");

    // 生徒ごとの偏差値を表示
    for (student_t* stPtr = students; stPtr != NULL; stPtr = stPtr->next) {
        printf("%5d ", stPtr->num);
        for (sbPtr = stPtr->subjects; sbPtr != NULL; sbPtr = sbPtr->next) {
            printf("%5.1f ", sbPtr->tScore);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");

    // 教科ごとの平均点を表示
    printf("%5s ", "Ave");
    for (subject_analysis_t* a = analysis; a != NULL; a = a->next) {
        printf("%5.1f ", a->averageScore);
    }
    printf("\n");

    // 教科ごとの平均点を表示
    printf("%5s ", "SD");
    for (subject_analysis_t* a = analysis; a != NULL; a = a->next) {
        printf("%5.1f ", a->standardDeviation);
    }

    printf("\n");
}

int main (void) {
    student_t *students = readFile("score.csv");
    eachStudentAverage(students);
    printScores(students);
    printTScore(students);
    writeFile(students, "result.csv");
    return 0;
}