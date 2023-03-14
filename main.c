#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define endl printf("\n")

// Structs
struct Student {
    char code[6];
    char name[101];
    char cpf[21];
};

struct Discipline {
    char code[5];
    char name[101];
    char teacher[101];
    int credits;
};

struct StudentNode {
    struct Student info;
    struct StudentNode *next;
};

struct DisciplineNode {
    struct Discipline info;
    struct DisciplineNode *next;
};

// Functions
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

int main() {
    int option;
    struct StudentNode *headStudent = NULL;
    struct DisciplineNode *headDiscipline = NULL;
    setlocale(LC_ALL, "Portuguese");
    do {
        printf("\nMenu\n\n");
        printf("1.\tVer lista de alunos\n2.\tVer lista de materias\n3.\tAdicionar aluno\n4.\tAdicionar materiat\n5.\tProcurar aluno\n6.\tSair\n\n");
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
            case 6: break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while(option != 6);
    system("pause");
    return 0;
}

struct Student createStudent() {
    char code[5];
    char name[101];
    char cpf[21];
    struct Student student;
    printf("\nInsira o codigo do aluno: ");
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
    return student;
}

struct Discipline createDiscipline() {
    char code[5];
    char name[101];
    char teacher[101];
    int credits;
    struct Discipline discipline;
    printf("\nInsira o codigo da disciplina: ");
    fflush(stdin);
    scanf(" %s", code);
    printf("Insira o nome da disciplina: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    printf("Insira o professor da disciplina: ");
    fflush(stdin);
    scanf(" %s", teacher);
    printf("Insira a quantidade de creditos da disciplina: ");
    fflush(stdin);
    scanf(" %d", &credits);
    strcpy(discipline.code, code);
    strcpy(discipline.name, name);
    strcpy(discipline.teacher, teacher);
    discipline.credits = credits;
    return discipline;
}

void appendStudent(struct StudentNode **head) {
    struct StudentNode *newStudent = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    struct Student student = createStudent();
    newStudent->info = student;
    newStudent->next = NULL;
    if(*head == NULL) {
        *head = newStudent;
        printf("\nAluno criado com sucesso!\n\n");
        return;
    }
    struct StudentNode *lastNode = *head;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newStudent;
    printf("\nAluno criado com sucesso!\n\n");
}

void appendDiscipline(struct DisciplineNode **head) {
    struct DisciplineNode *newDiscipline = (struct DisciplineNode*)malloc(sizeof(struct DisciplineNode));
    struct Discipline discipline = createDiscipline();
    newDiscipline->info = discipline;
    newDiscipline->next = NULL;
    if(*head == NULL) {
        *head = newDiscipline;
        printf("\nDisciplina criada com sucesso!\n\n");
        return;
    }
    struct DisciplineNode *lastNode = *head;
    while(lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newDiscipline;
    printf("\nDisciplina criada com sucesso!\n\n");
}

void showStudents(struct StudentNode *head) {
    if(head == NULL) {
        printf("\nNao ha alunos cadastrados\n\n");
        printf("-----------------------------------");
    }
    while(head != NULL) {
        printf("Codigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
        head = head->next;
    }
}

void showDisciplines(struct DisciplineNode *head) {
    if(head == NULL) {
        printf("\nNao ha disciplinas cadastradas\n\n");
    }
    while(head != NULL) {
        printf("Codigo: %s\nNome: %s\nProfessor: %s\nCreditos: %d\n\n", head->info.code, head->info.name, head->info.teacher, head->info.credits);
        head = head->next;
    }
}

int searchStudent(struct StudentNode *head) {
    struct StudentNode *aux = head;
    char method;
    char name[101];
    char cpf[21];
    do {
        printf("\n\nA.\tProcurar aluno por codigo\nB.\tProcurar aluno por nome\nC.\tProcurar aluno por CPF\nD.\tCancelar\n\n");
        printf("Como deseja procurar o aluno? ");
        fflush(stdin);
        scanf("%c", &method);
        switch (method) {
            case 'A':
                findStudentByCode(head);
                break;
            case 'B':
                printf("Insira o nome do aluno a procurar: ");
                fflush(stdin);
                scanf("%[^\n]s", name);
                if(head == NULL) {
                    printf("\nLista vazia\n");
                    break;
                }
                while(head != NULL) {
                    if(strcmp(head->info.name, name) == 0) {
                        printf("\nAluno encontrado:\n");
                        printf("Codigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
                        head = aux;
                        return 1;
                        break;
                    } else {
                        head = head->next;
                    }
                }
                if(head == NULL) {
                    printf("\nAluno nao encontrado");
                    head = aux;
                    return 0;
                }
                break;
            case 'C':
                printf("Insira o CPF do aluno a procurar: ");
                fflush(stdin);
                scanf("%s", cpf);
                if(head == NULL) {
                    printf("\nLista vazia\n");
                    break;
                }
                while(head != NULL) {
                    if(strcmp(head->info.cpf, cpf) == 0) {
                        printf("\nAluno encontrado:\n");
                        printf("Codigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
                        head = aux;
                        return 1;
                        break;
                    } else {
                        head = head->next;
                    }
                }
                if(head == NULL) {
                    printf("\nAluno nao encontrado");
                    head = aux;
                    return 0;
                }
                break;
            default:
                printf("Opcao invalida");
                break;
            }
    } while(method != 'A' && method != 'B' && method != 'C' && method != 'D');
}

int findStudentByCode(){
    char code[5];
    printf("Insira o codigo do aluno a procurar: ");
                fflush(stdin);
                scanf("%s", code);
                if(head == NULL) {
                    printf("\nLista vazia\n");
                    break;
                }
                while(head != NULL) {
                    if(strcmp(head->info.code, code) == 0) {
                        printf("\nAluno encontrado:\n");
                        printf("Codigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
                        head = aux;
                        return 1;
                        break;
                    } else {
                        head = head->next;
                    }
                }
                if(head == NULL) {
                    printf("\nAluno nao encontrado");
                    head = aux;
                    return 0;
                }
}