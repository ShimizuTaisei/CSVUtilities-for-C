#ifndef STUDENT_H
#define STUDENT_H

/**
 * @struct
 * @brief
 * 各教科の名前と得点を保持する
 */
typedef struct subject {
    struct subject *next;
    char name[20];
    unsigned short score;
    double tScore;
} subject_t;

/**
 * @struct
 * @brief
 * 生徒の学籍番号と教科の情報を保持する．
 */
typedef struct student {
    struct student *next;
    unsigned int num;
    char name[20];
    subject_t *subjects;
    int sumScore;
    double averageScore;
} student_t;

/**
 * @struct
 * @brief
 * 教科ごとの合計点と平均点を保持する．
 */
typedef struct subject_analysis {
    struct subject_analysis *next;
    char name[20];
    int sumScore;
    double averageScore;
    double standardDeviation;
} subject_analysis_t;

// Below are implemented in student.c
extern student_t *appendStudent(student_t *new, student_t *head);
extern unsigned int countStudent(student_t *head);
extern student_t *removeStudent(unsigned int num, student_t *head);
extern void removeAllStudent(student_t **head);

extern subject_t *appendSubject(subject_t *new, subject_t *head);
extern subject_t *searchSubject(const char *name, subject_t *head);
extern void removeAllSubjects(subject_t **head);
extern unsigned int subjectCount(subject_t *head);

extern subject_analysis_t *appendSubjectAnalysis(subject_analysis_t *new, subject_analysis_t *head);
extern subject_analysis_t *addSubjectScore(char name[], unsigned int score, subject_analysis_t *head);
extern subject_analysis_t *searchSubjectAnalysis(const char *name, subject_analysis_t *head);
extern void removeAllSubjectAnalysis(subject_analysis_t **head);
// Above are implemented in student.c

// Below are implemented in read_write.c
extern student_t *readFile(char *fileName);
extern void writeFile(const student_t *list, const char *fileName);
// Above are implemented in read_write.c

#endif