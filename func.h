#ifndef _SPACING_LINE_H_
#define _SPACING_LINE_H_

#define endl printf("\n")

// Structs
struct Student
{
    char code[6];
    char name[101];
    char cpf[21];
};

struct Discipline
{
    char code[5];
    char name[101];
    char teacher[101];
    int credits;
};

struct StudentNode
{
    struct Student info;
    struct StudentNode *next;
};

struct DisciplineNode
{
    struct Discipline info;
    struct DisciplineNode *next;
};

struct Student createStudent();
struct Discipline createDiscipline();
void appendStudent(struct StudentNode **head);
void appendDiscipline(struct DisciplineNode **head);
void showStudents(struct StudentNode *head);
void showDisciplines(struct DisciplineNode *head);
int searchStudent(struct StudentNode *head);
int findStudentByCode(struct StudentNode *head);
int findStudentByName(struct StudentNode *head);
int findStudentByCPF(struct StudentNode *head);
int searchDiscipline(struct DisciplineNode *head);
int findDisciplineByCode(struct DisciplineNode *head);
int findDisciplineByName(struct DisciplineNode *head);
int findDisciplineByTeacher(struct DisciplineNode *head);
void deleteStudent(struct StudentNode **head);
void spacingLine(int quantity, int spacingBefore, int spacingAfter);

#endif