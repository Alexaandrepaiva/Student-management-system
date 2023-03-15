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