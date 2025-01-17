#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

/**
 * @fn
 * @brief
 * リストの末尾に新しい生徒情報を追加する
 * @note
 * 第１引数に渡した生徒情報を変更するとリストの内容も変更されるので注意すること.
 * 戻り値で元のリストを上書きすること．
 * @param new 新しい生徒情報のポインタ
 * @param head 生徒リストの先頭のポインタ
 * @return 追加後のリストの先頭のポインタ
 */
student_t *appendStudent(student_t *new, student_t *head) {
    new->next = head;
    head = new;
    return head;
}

/**
 * @fn
 * @brief
 * 生徒リストの要素数を返す
 * @param head 生徒リストの先頭のポインタ
 * @return 生徒リストの要素数
 */
unsigned int countStudent(student_t *head) {
    unsigned int count = 0;
    student_t *p;
    for (p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;
}

/**
 * @fn
 * @brief
 * 第１引数に指定された学籍番号の生徒情報をリストから削除する
 * @note
 * 戻り値で元のリストを上書きすること
 * @param num 削除対象の学生番号
 * @param head 生徒リストの先頭のポインタ
 * @return 削除後のリスト先頭のポインタ
 */
student_t *removeStudent(unsigned int num, student_t *head) {
    student_t *p;
    student_t *prev = NULL;

    for (p = head; p != NULL; p = p->next) {
        if (p->num == num) {
            if (prev == NULL) {
                head = p->next;
            } else {
                prev->next = p->next;
            }
            removeAllSubjects(&p->subjects);
            free(p);
            printf("Removed student \"%d\"\n", num);
            return head;
        }
        prev = p;
    }

    printf("Not found given student number\n");
    return head;
}

/**
 * @fn
 * @brief
 * 生徒リストの全ての要素を削除し，メモリを解放する．
 * 実行後，生徒リスト先頭のポインタはNULLになる．
 * @param head 生徒リスト先頭のポインタのポインタ
 */
void removeAllStudent(student_t **head) {
    student_t *p = *head;
    student_t *target;
    while (p != NULL) {
        target = p;
        p = p->next;
        free(target);
    }

    *head = NULL;
}

/**
 * @fn
 * @brief
 * 教科リストに新しい要素を追加する．
 * @note
 * 第１引数に渡した新しい要素を他の場所で変更すると，リストの内容にも影響する．
 * 戻り値で元のリストを上書きすること
 * @param new 新しい教科情報
 * @param head 教科リストの先頭のポインタ
 * @return 追加後の教科リスト先頭のポインタ
 */
subject_t *appendSubject(subject_t *new, subject_t *head) {
    new->next = head;
    head = new;
    return head;
}

/**
 * @fn
 * @brief
 * 教科リストから指定された名前の教科を探す
 * @param name 探す教科名
 * @param head 教科リストの先頭のポインタ
 * @return 見つかった教科のポインタ 見つからなければNULLを返す
 */
subject_t *searchSubject(const char *name, subject_t *head) {
    for (subject_t *p = head; p != NULL; p = p->next) {
        if (strcmp(p->name, name) == 0) {
            return p;
        }
    }

    return NULL;
}

/**
 * @fn
 * @brief
 * 教科リストの全ての要素を削除し，メモリを解放する.
 * 実行後，教科リスト先頭のポインタはNULLになる．
 * @param head 削除する教科リストの先頭のポインタ
 */
void removeAllSubjects(subject_t **head) {
    subject_t *p = *head;
    subject_t *target;
    while (p != NULL) {
        target = p;
        p = p->next;
        free(target);
    }
    *head = NULL;
}

unsigned int subjectCount(subject_t *head) {
    int count = 0;
    subject_t *p;
    for (p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;
}

/**
 * @fn
 * @brief
 * 新しい教科分析をリストに追加する
 * @note
 * 第１引数の新しい要素を外部で変更するとリストにも影響する．
 * 戻り値で元のリストを更新すること．
 * @param new 新しい教科分析情報
 * @param head リストの先頭のポインタ
 * @return 追加後のリスト先頭のポインタ
 */
subject_analysis_t *appendSubjectAnalysis(subject_analysis_t *new, subject_analysis_t *head) {
    new->next = NULL;
    if (head == NULL) {
        head = (subject_analysis_t *)malloc(sizeof(subject_analysis_t));
        *head = *new;
    } else {
        subject_analysis_t *p;
        for (p = head; p->next != NULL; p = p->next);
        p->next = new;
    }

    return head;
}

/**
 * @fn
 * @brief
 * 教科の得点をリスト内の教科ごとの合計点に加算する．
 * もしリスト内に対象の教科がなければ，新しく作成してリストに追加する．
 * @param name 加算対象の教科名
 * @param score 加算する得点
 * @param head リスト先頭のポインタ
 * @return 変更後のリスト先頭のポインタ
 */
subject_analysis_t *addSubjectScore(char name[], unsigned int score, subject_analysis_t *head) {
    bool isAdded = false;
    subject_analysis_t *p;
    for (p = head; p != NULL; p = p->next) {
        if (strcmp(p->name, name) == 0) {
            p->sumScore += score;
            isAdded = true;
        }
    }

    if (!isAdded) {
        subject_analysis_t *new =
            (subject_analysis_t *)malloc(sizeof(subject_analysis_t));
        strcpy(new->name, name);
        new->sumScore = score;
        new->averageScore = 0;
        head = appendSubjectAnalysis(new, head);
    }

    return head;
}

/**
 * @fn
 * @brief
 * リスト内から指定された名前の教科分析を探す
 * @param name 探す教科名
 * @param head リスト先頭のポインタ
 * @return 見つかった教科分析のポインタ 見つからなければNULLを返す
 */
subject_analysis_t *searchSubjectAnalysis(const char *name, subject_analysis_t *head)
{
    for (subject_analysis_t *p = head; p != NULL; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            return p;
        }
    }

    return NULL;
}

/**
 * @fn
 * @brief 
 * 教科分析のリストの要素を全て削除し，メモリを解放する．
 * 実行後，リストの先頭ポインタはNULLになる．
 * @param head リスト先頭のポインタのポインタ
 */
void removeAllSubjectAnalysis(subject_analysis_t **head) {
    subject_analysis_t *p = *head;
    subject_analysis_t *target;
    while (p != NULL) {
        target = p;
        p = p->next;
        free(target);
    }

    *head = NULL;
}