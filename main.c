#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

int main()
{
    int option;
    struct StudentNode *headStudent = NULL;
    struct DisciplineNode *headDiscipline = NULL;
    spacingLine(35, 1, 2);
    printf("Seja bem vindo ao GRANITO\n\n");
    do
    {
        spacingLine(35, 0, 2);
        printf("Menu\n\n");
        printf("1.\tVer lista de alunos\n2.\tVer lista de disciplinas\n3.\tAdicionar aluno\n4.\tAdicionar disciplina\n5.\tProcurar aluno\n6.\tSair\n\n");
        spacingLine(35, 0, 2);
        printf("Opcao: ");
        scanf("%d", &option);
        switch (option)
        {
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
            deleteStudent(&headStudent);
            break;
        case 7:
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    } while (option != 7);
    return 0;
}

struct Student createStudent()
{
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
