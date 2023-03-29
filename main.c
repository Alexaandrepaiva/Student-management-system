/*
Authors: Luiz Guilherme Amadi Braga and Alexandre de Paiva Almeida
University: IME, Rio de Janeiro, Brazil
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define STUDENT_CODE_SIZE 6
#define DISCIPLINE_CODE_SIZE 5
#define NAME_SIZE 101
#define CPF_SIZE 21
#define PERIOD_SIZE 7
#define endl printf("\n")

// Structs

// Student struct
typedef struct Student {
    char code[STUDENT_CODE_SIZE];
    char name[NAME_SIZE];
    char cpf[CPF_SIZE];
    int disciplinesLength;
    struct DisciplineNode *currentDisciplines;
} Student;

// Student linked list node struct
typedef struct StudentNode {
    struct Student info;
    struct StudentNode *next;    
} StudentNode;

// Discipline struct
typedef struct Discipline {
    char code[DISCIPLINE_CODE_SIZE];
    char name[NAME_SIZE];
    char teacher[NAME_SIZE];
    int credits;
    char period[PERIOD_SIZE];
    int studentsLength;
    struct StudentNode *currentStudents;
} Discipline;

// Discipline linked list node struct
typedef struct DisciplineNode {
    struct Discipline info;
    struct DisciplineNode *next;
} DisciplineNode;

// Functions

// Student general functions
Student createStudent();
void showStudents(StudentNode *head);
void appendStudent(StudentNode **head);
int searchStudent(StudentNode *head);
int deleteStudent(StudentNode **head);
void showDisciplinesFromStudentCode(StudentNode *head);
void showStudentsFromPeriod(StudentNode *head);

// Specific searching student functions
int findStudentByCode(StudentNode *head);
int findStudentByName(StudentNode *head);
int findStudentByCPF(StudentNode *head);

// Specific deleting student functions
int deleteStudentByCode(StudentNode **head);
int deleteStudentByName(StudentNode **head);
int deleteStudentByCPF(StudentNode **head);

// Updates students current disciplines and disciplnes current students also
int updateDisciplines(StudentNode *headStudent, DisciplineNode *headDiscipline);

// Discipline general functions
Discipline createDiscipline();
void showDisciplines(DisciplineNode *head);
void appendDiscipline(DisciplineNode **head);
int searchDiscipline(DisciplineNode *head);
int deleteDiscipline(DisciplineNode **head);
void showStudentsFromDisciplineCode(DisciplineNode *head);
void showDisciplinesFromPeriod(StudentNode *head);

// Specific searching discipline functions
int findDisciplineByCode(DisciplineNode *head);
int findDisciplineByName(DisciplineNode *head);
int findDisciplineByTeacher(DisciplineNode *head);

// Specific deleting discipline functions
int deleteDisciplineByCode(DisciplineNode **head);
int deleteDisciplineByName(DisciplineNode **head);
int deleteDisciplineByTeacher(DisciplineNode **head);

// Other functions
void spacingLine(int Length, int spacingBefore, int spacingAfter);

int main() {
    int option;
    StudentNode *headStudent = NULL;
    DisciplineNode *headDiscipline = NULL;
    spacingLine(35, 1, 2);
    printf("Seja bem vindo ao GRANITO\n\n");
    do {
        spacingLine(35, 0, 2);
        printf("Menu\n\n");
        printf("1.\tVer lista de alunos\n2.\tVer lista de disciplinas\n3.\tAdicionar aluno\n4.\tAdicionar disciplina\n5.\tProcurar aluno\n6.\tProcurar disciplina\n7.\tDeletar aluno\n8.\tDeletar disciplina\n9.\tAdicionar disciplina a aluno\n10.\tDisciplinas de um aluno\n11.\tAlunos de uma disciplina\n12.\tDisciplinas de um periodo\n13.\tAlunos de um periodo\n14.\tSair\n\n");
        spacingLine(35, 0, 2);
        printf("Opcao: ");
        scanf("%d", &option);
        switch(option) {
            case 1:
                showStudents(headStudent);
                break;
            case 2:
                showDisciplines(headDiscipline);
                break;
            case 3:
                appendStudent(&headStudent);
                break;
            case 4:
                appendDiscipline(&headDiscipline);
                break;
            case 5: 
                searchStudent(headStudent);
                break;
            case 6: 
                searchDiscipline(headDiscipline);
                break;
            case 7: 
                deleteStudent(&headStudent);
                break;
            case 8:
                deleteDiscipline(&headDiscipline);
                break;
            case 9:
                updateDisciplines(headStudent, headDiscipline);
                break;
            case 10:
                showDisciplinesFromStudentCode(headStudent);
                break;
            case 11:
                showStudentsFromDisciplineCode(headDiscipline);
                break;
            case 12:
                showDisciplinesFromPeriod(headStudent);
                break;
            case 13:
                showStudentsFromPeriod(headStudent);
                break;
            case 14:
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while(option != 14);
    return 0;
}

// ***** Student functions *****

// Creates new student and returns it
Student createStudent() {
    char code[STUDENT_CODE_SIZE];
    char name[NAME_SIZE];
    char cpf[CPF_SIZE];
    Student student;
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno: ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome do aluno: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o CPF do aluno (somente numeros): ");
    fflush(stdin);
    scanf(" %s", cpf);
    strcpy(student.code, code);
    strcpy(student.name, name);
    strcpy(student.cpf, cpf);
    student.disciplinesLength = 0;
    student.currentDisciplines = NULL;
    return student;
}

// Appends student at the end of the list
void appendStudent(StudentNode **head) {
    StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode));
    Student student = createStudent();
    newStudent->info = student;
    newStudent->next = NULL;
    if(*head == NULL) { // Empty student list
        *head = newStudent;
        printf("\nAluno criado com sucesso!\n\n");
        return;
    }
    StudentNode *lastNode = *head;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newStudent;
    printf("\nAluno criado com sucesso!\n\n");
}

// Displays every registered student
void showStudents(StudentNode *head) {
    if(head == NULL) { // Empty student list
        spacingLine(35, 1, 2);
        printf("Nao ha alunos cadastrados\n\n");
        return;
    }
    printf("\nAlunos cadastrados:\n\n");
    printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
    while(head != NULL) {
        printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        head = head->next;
    }
    printf("\n");
}

// Searches for student
int searchStudent(StudentNode *head) {
    char method;
    do {
        printf("\n\nA.\tProcurar aluno por codigo\nB.\tProcurar aluno por nome\nC.\tProcurar aluno por CPF\nD.\tCancelar\n\n");
        printf("Como deseja procurar o aluno? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch(method) {
        case 'A':
            findStudentByCode(head);
            break;
        case 'B':
            findStudentByName(head);
            break;
        case 'C':
            findStudentByCPF(head);
            break;
        case 'D':
            break;
        default:
            printf("Opcao invalida");
            break;
        }
    } while (method != 'D');
}

// Finds student by its code
int findStudentByCode(StudentNode *head) {
    StudentNode *aux = head;
    char code[STUDENT_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            if(!found) {
                printf("\nAluno(s) encontrado(s):\n\n");
                printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
                found = 1;
            }
            printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        }
        head = head->next;
    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nAluno nao encontrado");
        return 0;
    }
}

// Finds student by its name
int findStudentByName(StudentNode *head) {
    StudentNode *aux = head;
    char name[NAME_SIZE];
    printf("Insira o nome do aluno a procurar: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if(strcmp(head->info.name, name) == 0) {
            if(!found) {
                printf("\nAluno(s) encontrado(s):\n\n");
                printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
                found = 1;
            }
            printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        }
        head = head->next;

    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nAluno nao encontrado");
        return 0;
    }
}

// Finds student by its CPF
int findStudentByCPF(StudentNode *head) {
    StudentNode *aux = head;
    char cpf[CPF_SIZE];
    printf("Insira o CPF do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", cpf);
    if (head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->info.cpf, cpf) == 0) {
            if(!found) {
                printf("\nAluno(s) encontrado(s):\n\n");
                printf("%-20s%-40s%-30s%-20s\n", "Codigo", "Nome", "CPF", "Disciplinas");
                found = 1;
            }
            printf("%-20s%-40s%-30s%-20d\n", head->info.code, head->info.name, head->info.cpf, head->info.disciplinesLength);
        }
        head = head->next;
    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nAluno nao encontrado");
        return 0;
    }
}

// Deletes student
int deleteStudent(StudentNode **head) {
    char method;
    do {
        printf("\n\nA.\tDeletar aluno por codigo\nB.\tDeletar aluno por nome\nC.\tDeletar aluno por CPF\nD.\tCancelar\n\n");
        printf("Como deseja deletar o aluno? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch(method) {
        case 'A':
            deleteStudentByCode(head);
            break;
        case 'B':
            deleteStudentByName(head);
            break;
        case 'C':
            deleteStudentByCPF(head);
            break;
        case 'D':
            break;
        default:
            printf("Opção inválida");
            break;
        }
    } while (method != 'D');
}

// Deletes student by code
int deleteStudentByCode(StudentNode **head) {
    char code[STUDENT_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a deletar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    StudentNode *prev = NULL;
    StudentNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.code, code) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nAlunos deletados: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhum aluno foi deletado");
        return 0;
    }
}

// Deletes student by name
int deleteStudentByName(StudentNode **head) {
    char name[NAME_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o nome do aluno a deletar: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    StudentNode *prev = NULL;
    StudentNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.name, name) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nAlunos deletados: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhum aluno foi deletado");
        return 0;
    }
}

// Deletes student by CPF
int deleteStudentByCPF(StudentNode **head) {
    char cpf[CPF_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o CPF do aluno a deletar: ");
    fflush(stdin);
    scanf(" %s", cpf);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    StudentNode *prev = NULL;
    StudentNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.cpf, cpf) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nAlunos deletados: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhum aluno foi deletado");
        return 0;
    }
}

// Shows every discipline a student is registered
void showDisciplinesFromStudentCode(StudentNode *head) {
    StudentNode *auxStudent = head;
    char code[STUDENT_CODE_SIZE];
    printf("Insira o codigo do aluno: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            DisciplineNode *auxDiscipline = head->info.currentDisciplines;
            found = 1;
            printf("\n%s\tAluno: %s\n\n", head->info.code, head->info.name);
            printf("Disciplinas:\n");
            if(head->info.currentDisciplines == NULL) {
                printf("Nao ha disciplinas\n");
                return;
            }
            while(head->info.currentDisciplines != NULL) {
                printf("%s\t%s, Professor: %s, Periodo: %s\n", head->info.currentDisciplines->info.code, head->info.currentDisciplines->info.name, head->info.currentDisciplines->info.teacher, head->info.currentDisciplines->info.period);
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
            printf("\n");
        }
        head = head->next;
    }
    head = auxStudent;
}

// Shows every student registered into a discipline in certain period
void showStudentsFromPeriod(StudentNode *head) {
    StudentNode *auxStudent = head;
    char period[PERIOD_SIZE];
    printf("Insira o periodo: ");
    fflush(stdin);
    scanf(" %s", period);
    if(head == NULL) { // Empty list
        printf("Nao ha alunos cadastradas em periodos");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(head->info.disciplinesLength != 0) {
            DisciplineNode *auxDiscipline = head->info.currentDisciplines;
            while(head->info.currentDisciplines != NULL) {
                if(strcmp(head->info.currentDisciplines->info.period, period) == 0) {
                    if(!found) {
                        printf("\nAlunos:\n\n");
                    }
                    printf("\n%s\tNome: %s", head->info.code, head->info.name);
                    found = 1;
                    break;
                }
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
        }        
        head = head->next;
    }
    head = auxStudent;
    printf("\n\n");
    if(!found) {
        printf("\nNao ha alunos no periodo selecionado\n");
    }
}


// ***** Discipline Functions *****

// Creates new discipline and returns it
Discipline createDiscipline() {
    char code[DISCIPLINE_CODE_SIZE];
    char name[NAME_SIZE];
    char teacher[NAME_SIZE];
    int credits;
    Discipline discipline;
    printf("\nInsira o codigo da disciplina: ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o professor da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", teacher);
    printf("Insira a quantidade de creditos da disciplina: ");
    fflush(stdin);
    scanf(" %d", &credits);
    strcpy(discipline.code, code);
    strcpy(discipline.name, name);
    strcpy(discipline.teacher, teacher);
    strcpy(discipline.period, "----.-");
    discipline.credits = credits;
    discipline.studentsLength = 0;
    discipline.currentStudents = NULL;
    return discipline;
}

// Appends discipline to the end of the list
void appendDiscipline(DisciplineNode **head) {
    DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode));
    Discipline discipline = createDiscipline();
    newDiscipline->info = discipline;
    newDiscipline->next = NULL;
    if(*head == NULL) { // Empty discipline list
        *head = newDiscipline;
        printf("\nDisciplina criada com sucesso!\n\n");
        return;
    }
    DisciplineNode *lastNode = *head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newDiscipline;
    printf("\nDisciplina criada com sucesso!\n\n");
}

// Displays every registered discipline
void showDisciplines(DisciplineNode *head) {
    if(head == NULL) { // Empty discipline list
        spacingLine(35, 1, 2);
        printf("Nao ha disciplinas cadastradas\n\n");
        return;
    }
    printf("\nDisciplinas cadastradas:\n\n");
    printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
    while(head != NULL) {
        printf("%-20s%-30s%-30s%-20d%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.credits, head->info.studentsLength);
        head = head->next;
    }
    printf("\n");
}

// Searches for discipline
int searchDiscipline(DisciplineNode *head) {
    DisciplineNode *aux = head;
    char method;
    do {
        printf("\n\nA.\tProcurar disciplina por codigo\nB.\tProcurar disciplina por nome\nC.\tProcurar disciplina por professor\nD.\tCancelar\n\n");
        printf("Como deseja procurar o disciplina? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch(method) {
        case 'A':
            findDisciplineByCode(head);
            break;
        case 'B':
            findDisciplineByName(head);
            break;
        case 'C':
            findDisciplineByTeacher(head);
            break;
        case 'D':
            break;
        default:
            printf("Opcao invalida");
            break;
        }
    } while (method != 'D');
}

// Finds discipline by code
int findDisciplineByCode(DisciplineNode *head) {
    DisciplineNode *aux = head;
    char code[DISCIPLINE_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->info.code, code) == 0) {
            if(!found) {
                printf("\nDisciplina(s) encontrada(s):\n\n");
                printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
                found = 1;
            }
            printf("%-20s%-30s%-30s%-20s%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.studentsLength);
        }
        printf("\n");
        head = head->next;
    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nDisciplina nao encontrada");
        return 0;
    }
}

// Finds discipline by name
int findDisciplineByName(DisciplineNode *head) {
    DisciplineNode *aux = head;
    char name[NAME_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o nome da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    if (head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->info.name, name) == 0) {
            if(!found) {
                printf("\nDisciplina(s) encontrada(s):\n\n");
                printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
                found = 1;
            }
            printf("%-20s%-30s%-30s%-20s%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.studentsLength);
        }
        printf("\n");
        head = head->next;
    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nDisciplina nao encontrada");
        return 0;
    }
}

// Finds discipline by teacher
int findDisciplineByTeacher(DisciplineNode *head) {
    DisciplineNode *aux = head;
    char teacher[NAME_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o nome do professor da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %[^\n]s", teacher);
    if (head == NULL) { // Empty list
        printf("\nLista vazia\n");
    }
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->info.teacher, teacher) == 0) {
            if(!found) {
                printf("\nDisciplina(s) encontrada(s):\n\n");
                printf("%-20s%-30s%-30s%-20s%-20s\n", "Codigo", "Nome", "Professor", "Creditos", "Alunos");
                found = 1;
            }
            printf("%-20s%-30s%-30s%-20s%-20d\n", head->info.code, head->info.name, head->info.teacher, head->info.studentsLength);
        }
        printf("\n");
        head = head->next;
    }
    head = aux;
    if(found) {
        return 1;
    } else {
        printf("\nDisciplina nao encontrada");
        return 0;
    }
}

// Deletes discipline
int deleteDiscipline(DisciplineNode **head) {
    char method;
    do {
        printf("\n\nA.\tDeletar disciplina por codigo\nB.\tDeletar disciplina por nome\nC.\tDeletar disciplina por professor\nD.\tCancelar\n\n");
        printf("Como deseja deletar a disciplina? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch(method) {
        case 'A':
            deleteDisciplineByCode(head);
            break;
        case 'B':
            deleteDisciplineByName(head);
            break;
        case 'C':
            deleteDisciplineByTeacher(head);
            break;
        case 'D':
            break;
        default:
            printf("Opção inválida");
            break;
        }
    } while (method != 'D');
}

// Deletes discipline by code
int deleteDisciplineByCode(DisciplineNode **head) {
    char code[DISCIPLINE_CODE_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a deletar: ");
    fflush(stdin);
    scanf(" %s", code);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    DisciplineNode *prev = NULL;
    DisciplineNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.code, code) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nDisciplinas deletadas: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhuma disciplina foi deletada");
        return 0;
    }
}

// Deletes discipline by name
int deleteDisciplineByName(DisciplineNode **head) {
    char name[NAME_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o nome da disciplina a deletar: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    DisciplineNode *prev = NULL;
    DisciplineNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.name, name) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nDisciplinas deletadas: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhuma disciplina foi deletada");
        return 0;
    }
}

// Deletes discipline by teacher
int deleteDisciplineByTeacher(DisciplineNode **head) {
    char teacher[NAME_SIZE];
    spacingLine(35, 1, 2);
    printf("Insira o nome do professor da disciplina a deletar: ");
    fflush(stdin);
    scanf(" %[^\n]s", teacher);
    if(*head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return 0;
    } 
    int counter = 0;
    DisciplineNode *prev = NULL;
    DisciplineNode *curr = *head;
    while(curr != NULL) {
        if(strcmp(curr->info.teacher, teacher) == 0) {
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            counter++;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    if(counter) {
        printf("\nDisciplinas deletadas: %d\n", counter);
        return 1;
    } else {
        printf("\nNenhuma disciplina foi deletada");
        return 0;
    }
}

// Shows every student registered in a discipline
void showStudentsFromDisciplineCode(DisciplineNode *head) {
    DisciplineNode *auxDiscipline = head;
    char code[DISCIPLINE_CODE_SIZE];
    printf("Insira o codigo da disciplina: ");
    fflush(stdin);
    scanf(" %s", code);
    if(head == NULL) { // Empty list
        printf("\nLista vazia\n");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            StudentNode *auxStudent = head->info.currentStudents;
            found = 1;
            printf("\n%s\tDisciplina: %s\n\n", head->info.code, head->info.name);
            printf("Alunos:\n");
            if(head->info.currentStudents == NULL) {
                printf("Nao ha alunos\n");
                return;
            }
            while(head->info.currentStudents != NULL) {
                printf("%s\t%s\n", head->info.currentStudents->info.code, head->info.currentStudents->info.name);
                head->info.currentStudents = head->info.currentStudents->next;
            }
            head->info.currentStudents = auxStudent;
            printf("\n");
        }
        head = head->next;
    }
    head = auxDiscipline;
}

// Shows every discipline from certain period
void showDisciplinesFromPeriod(StudentNode *head) {
    StudentNode *auxStudent = head;
    char period[PERIOD_SIZE];
    printf("Insira o periodo: ");
    fflush(stdin);
    scanf(" %s", period);
    if(head == NULL) { // Empty list
        printf("Nao ha disciplinas cadastradas em periodos");
        return;
    }
    int found = 0;
    while(head != NULL) {
        if(head->info.disciplinesLength != 0) {
            DisciplineNode *auxDiscipline = head->info.currentDisciplines;
            while(head->info.currentDisciplines != NULL) {
                if(strcmp(head->info.currentDisciplines->info.period, period) == 0) {
                    if(!found) {
                        printf("\nDisciplinas:\n\n");
                    }
                    printf("\n%s\tDisciplina: %s", head->info.currentDisciplines->info.code, head->info.currentDisciplines->info.name);
                    found = 1;
                }
                head->info.currentDisciplines = head->info.currentDisciplines->next;
            }
            head->info.currentDisciplines = auxDiscipline;
        }        
        head = head->next;
    }
    head = auxStudent;
    printf("\n\n");
    if(!found) {
        printf("\nNao ha disciplinas no periodo selecionado\n");
    }
}

// ***** Update funcions *****

// Updates students current disciplines and also discipline current students
int updateDisciplines(StudentNode *headStudent, DisciplineNode *headDiscipline) {
    char studentCode[STUDENT_CODE_SIZE];
    char disciplineCode[DISCIPLINE_CODE_SIZE];
    char period[PERIOD_SIZE];
    printf("Para cadastrar uma disciplina a um aluno, insira:\n1. Codigo do aluno: ");
    fflush(stdin);
    scanf(" %[^\n]s", studentCode);
    printf("2. Codigo da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", disciplineCode);
    printf("3. Periodo: ");
    fflush(stdin);
    scanf(" %[^\n]s", period);
    if(headStudent == NULL || headDiscipline == NULL) { // Empty list
        printf("\nAlguma das listas é vazia\n");
        return 0;
    }
    int updated = -1;
    while(headDiscipline != NULL) {
        if(strcmp(headDiscipline->info.code, disciplineCode) == 0) {
            updated = 0;
            while(headStudent != NULL) {
                if(strcmp(headStudent->info.code, studentCode) == 0) {
                    headStudent->info.disciplinesLength++;
                    DisciplineNode *newDiscipline = (DisciplineNode*)malloc(sizeof(DisciplineNode));
                    newDiscipline->info = headDiscipline->info;
                    strcpy(newDiscipline->info.period, period);
                    newDiscipline->next = NULL;
                    if(headStudent->info.currentDisciplines == NULL) {
                        headStudent->info.currentDisciplines = newDiscipline;
                    } else {
                        DisciplineNode *lastDisciplineNode = headStudent->info.currentDisciplines;
                        while(lastDisciplineNode->next != NULL) {
                            lastDisciplineNode = lastDisciplineNode->next;
                        }
                        lastDisciplineNode->next = newDiscipline;
                    }
                    headDiscipline->info.studentsLength++;
                    StudentNode *newStudent = (StudentNode*)malloc(sizeof(StudentNode));
                    newStudent->info = headStudent->info;
                    newStudent->next = NULL;
                    if(headDiscipline->info.currentStudents == NULL) {
                        headDiscipline->info.currentStudents = newStudent;
                    } else {
                        StudentNode *lastStudentNode = headDiscipline->info.currentStudents;
                        while(lastStudentNode->next != NULL) {
                            lastStudentNode = lastStudentNode->next;
                        }
                        lastStudentNode->next = newStudent;
                    }
                    updated = 1;
                }
                headStudent = headStudent->next;
            }
        }
        headDiscipline = headDiscipline->next;
    }
    if(updated == -1) {
        printf("\nA disciplina nao foi encontrada\n\n");
        return 0;
    } else if(updated == 0) {
        printf("\nO aluno nao foi encontrado\n\n");
        return 0;
    } else {
        printf("\nO aluno foi atualizado com sucesso\n\n");
        return 1;
    }
}

// Other functions
void spacingLine(int Length, int spacingBefore, int spacingAfter) {
    int i = 0, j = 0, k = 0;
    while (i < spacingBefore) {
        printf("\n");
        i++;
    }
    while (j < Length) {
        printf("*");
        j++;
    }
    while (k < spacingAfter) {
        printf("\n");
        k++;
    }
}