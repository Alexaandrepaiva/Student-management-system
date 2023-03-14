#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Create functions
struct Student createStudent();
struct Discipline createDiscipline();
void appendStudent(struct StudentNode **head);
void appendDiscipline(struct DisciplineNode **head);

// Display functions
void showStudents(struct StudentNode *head);
void showDisciplines(struct DisciplineNode *head);

// Search student functions
int searchStudent(struct StudentNode *head);
int findStudentByCode(struct StudentNode *head);
int findStudentByName(struct StudentNode *head);
int findStudentByCPF(struct StudentNode *head);

// Search discipline functions
int searchDiscipline(struct DisciplineNode *head);
int findDisciplineByCode(struct DisciplineNode *head);
int findDisciplineByName(struct DisciplineNode *head);
int findDisciplineByTeacher(struct DisciplineNode *head);

// Delete student functions
void deleteStudent(struct StudentNode **head);
void deleteStudentByCode(struct StudentNode **head);
void deleteStudentByName(struct StudentNode **head);
void deleteStudentByCPF(struct StudentNode **head);

// Delete discipline functions
void deleteDiscipline(struct DisciplineNode **head);
void deleteDisciplineByCode(struct DisciplineNode **head);
void deleteDisciplineByName(struct DisciplineNode **head);
void deleteDisciplineByTeacher(struct DisciplineNode **head);

void spacingLine(int quantity, int spacingBefore, int spacingAfter);

int main() {
    int option;
    struct StudentNode *headStudent = NULL;
    struct DisciplineNode *headDiscipline = NULL;
    spacingLine(35, 1, 2);
    printf("Seja bem vindo ao GRANITO\n\n");
    do {
        spacingLine(35, 0, 2);
        printf("Menu\n\n");
        printf("1.\tVer lista de alunos\n2.\tVer lista de materias\n3.\tAdicionar aluno\n4.\tAdicionar disciplina\n5.\tProcurar aluno\n6.\tProcurar disciplina\n7.\tDeletar aluno\n8.\tDeletar disciplina\n9.\tSair\n\n");
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
                // searchDiscipline(headDiscipline);
                break;
            case 7: 
                deleteStudent(&headStudent);
                break;
            case 8:
                // deleteDiscipline(&headDiscipline);
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while(option != 9);
    return 0;
}

struct Student createStudent() {
    char code[5];
    char name[101];
    char cpf[21];
    struct Student student;
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
        spacingLine(35, 1, 2);
        printf("Nao ha alunos cadastrados\n\n");
    }
    while(head != NULL) {
        printf("\nCodigo: %s\nNome: %s\nCPF: %s\n\n", head->info.code, head->info.name, head->info.cpf);
        head = head->next;
    }
}

void showDisciplines(struct DisciplineNode *head) {
    if(head == NULL) {
        spacingLine(35, 1, 2);
        printf("Nao ha disciplinas cadastradas\n\n");
    }
    while(head != NULL) {
        printf("\nCodigo: %s\nNome: %s\nProfessor: %s\nCreditos: %d\n\n", head->info.code, head->info.name, head->info.teacher, head->info.credits);
        head = head->next;
    }
}

int searchStudent(struct StudentNode *head) {
    struct StudentNode *aux = head;
    char method;
    do {
        printf("\n\nA.\tProcurar aluno por codigo\nB.\tProcurar aluno por nome\nC.\tProcurar aluno por CPF\nD.\tCancelar\n\n");
        printf("Como deseja procurar o aluno? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch (method) {
            case 'A':
                findStudentByCode(head);
                break;
            case 'B':
                findStudentByName(head);
                break;
            case 'C':
                findStudentByCPF(head);
                break;
            default:
                printf("Opcao invalida");
                break;
            }
    } while(method != 'A' && method != 'B' && method != 'C' && method != 'D');
}

int findStudentByCode(struct StudentNode *head){
    struct StudentNode *aux = head;
    char code[5];
    spacingLine(35, 1, 2);
    printf("Insira o codigo do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL) {
        printf("\nLista vazia\n");
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

int findStudentByName(struct StudentNode *head) {
    struct StudentNode *aux = head;
    char name[101];
    printf("Insira o nome do aluno a procurar: ");
    fflush(stdin);
    scanf(" %[^\n]s", name);
    if(head == NULL) {
        printf("\nLista vazia\n");
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
}

int findStudentByCPF(struct StudentNode *head) {
    struct StudentNode *aux = head;
    char cpf[21];
    printf("Insira o CPF do aluno a procurar: ");
    fflush(stdin);
    scanf(" %s", cpf);
    if(head == NULL) {
        printf("\nLista vazia\n");
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
}

int findDisciplineByCode(struct DisciplineNode *head){
    struct DisciplineNode *aux = head;
    char code[5];
    spacingLine(35, 1, 2);
    printf("Insira o codigo da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", code);
    if (head == NULL) {
        printf("\nLista vazia\n");
    }
    while(head != NULL) {
        if(strcmp(head->info.code, code) == 0) {
            printf("\nDisciplina encontrada:\n");
            printf("Codigo: %s\nNome: %s\nProfessor: %s\n\n", head->info.code, head->info.name, head->info.teacher);
            head = aux;
            return 1;
            break;
        } else {
            head = head->next;
        }
    }
    if(head == NULL) {
        printf("\nDisciplina nao encontrada");
        head = aux;
        return 0;
    }
}

int findDisciplineByName(struct DisciplineNode *head){
    struct DisciplineNode *aux = head;
    char name[101];
    spacingLine(35, 1, 2);
    printf("Insira o nome da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", name);
    if (head == NULL) {
        printf("\nLista vazia\n");
    }
    while(head != NULL) {
        if(strcmp(head->info.name, name) == 0) {
            printf("\nDisciplina encontrada:\n");
            printf("Codigo: %s\nNome: %s\nProfessor: %s\n\n", head->info.code, head->info.name, head->info.teacher);
            head = aux;
            return 1;
            break;
        } else {
            head = head->next;
        }
    }
    if(head == NULL) {
        printf("\nDisciplina nao encontrada");
        head = aux;
        return 0;
    }
}
int findDisciplineByTeacher(struct DisciplineNode *head){
    struct DisciplineNode *aux = head;
    char teacher[101];
    spacingLine(35, 1, 2);
    printf("Insira o nome do professor da disciplina a procurar: ");
    fflush(stdin);
    scanf(" %s", teacher);
    if (head == NULL) {
        printf("\nLista vazia\n");
    }
    while(head != NULL) {
        if(strcmp(head->info.teacher, teacher) == 0) {
            printf("\nDisciplina encontrada:\n");
            printf("Codigo: %s\nNome: %s\nProfessor: %s\n\n", head->info.code, head->info.name, head->info.teacher);
            head = aux;
            return 1;
            break;
        } else {
            head = head->next;
        }
    }
    if(head == NULL) {
        printf("\nDisciplina nao encontrada");
        head = aux;
        return 0;
    }
}


void deleteStudent(struct StudentNode **head) {
    char method;
    char code[5];
    char name[101];
    char cpf[21];
    do {
        printf("\n\nA.\tDeletar aluno por codigo\nB.\tDeletar aluno por nome\nC.\tDeletar aluno por CPF\nD.\tCancelar\n\n");
        printf("Como deseja deletar o aluno? ");
        fflush(stdin);
        scanf(" %c", &method);
        switch (method) {
            case 'A':
                deleteStudentByCode(head);
                break;
            case 'B':
                printf("Insira o nome do aluno a ser deletado: ");
                fflush(stdin);
                scanf(" %[^\n]s", name);
                break;
            case 'C':
                printf("Insira o CPF do aluno a ser deletado: ");
                fflush(stdin);
                scanf(" %s", cpf);
                break;
            default:
                printf("Opcao invalida");
                break;
            }
    } while(method != 'A' && method != 'B' && method != 'C' && method != 'D');
}

void deleteStudentByCode(struct StudentNode **head) {
    struct StudentNode *aux = *head;
    char code[5];
    printf("Insira o codigo do aluno a ser deletado: ");
    fflush(stdin);
    scanf(" %s", code);
    if (*head == NULL) {
        printf("\nLista vazia\n");
    }
    if (strcmp((*head)->info.code, code) == 0) {
        struct StudentNode *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    struct StudentNode *current = *head;
    while (current->next != NULL) {
        if (strcmp(current->next->info.code, code) == 0) {
            struct StudentNode *temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }
    printf("\nAluno nao encontrado\n");
}
void spacingLine(int quantity, int spacingBefore, int spacingAfter){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < spacingBefore){
        printf("\n");
        i++;
    }
    while (j < quantity){
        printf("*");
        j++;
    }
    while (k < spacingAfter){
        printf("\n");
        k++;
    }
}
