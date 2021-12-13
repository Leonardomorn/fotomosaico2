#include "list.h"

int initialize_list( t_list *l)
/* cria uma lista vazia, retorna 1 se criada com sucesso e 0 caso contrário */
{
    l->first = NULL;
    if(list_is_empty(l))
        return 1;
    return 0;
}

int list_is_empty (t_list *l)
/* Verifica se a lista é vazia, retorna 1 se é vazia e 0 caso contrário*/
{
    if (l->first == NULL)
        return 1;
    return 0;
}

int add_empty_list (t_list *l, PPM *knot)
/*insere em lista vazia, retorna 1 se sucesso e 0 caso contrário*/
{
    l->first = knot;
    knot->prev_knot = NULL;
    knot->next_knot = NULL;
    if(l->first == NULL)
    {
        return 0;
    }
    return 1;
}

int append(t_list *l, PPM *knot)
/*insere um nodo no first da lista, retorna 1 se feito com sucesso e 0 caso contrário*/
{
    PPM *knot_aux; 
    knot_aux= l->first;
    knot->next_knot = l->first;
    knot->prev_knot = NULL;
    l->first = knot;
    knot_aux->prev_knot = l->first;
    if (knot->prev_knot == NULL)
        return 1;
    return 0;
}

void remove_list(t_list *l)
/*remove o primeiro da lista*/
{
    PPM *knot_aux;    
    knot_aux = l->first;
    if (list_is_empty(l))                  /*caso a lista seja vazia*/
    {
        printf ("\n lista vazia, impossivel remover\n");
        return;
    }
    if (l->first->next_knot == NULL)   /*caso seja o único nó da lista*/
    {
        free(knot_aux);
        l->first = NULL;
        return;
    }

    l->first = knot_aux->next_knot;
    knot_aux->next_knot->prev_knot = NULL;
    
    for (int i = 0; i < knot_aux->height; i++)
    {
        free (knot_aux->matriz_pixel[i]);
    }
        
    free(knot_aux->matriz_pixel);
    free(knot_aux);
    return;
}

void destroy_list(t_list *l)
/*remove todos os elementos da lista*/
{
    if (list_is_empty(l))                  /*caso a lista seja vazia*/
    {
        return;
    }
    while(!list_is_empty(l))               /*remove todos os dados da lista até 
                                        a lista estar vazia*/
    {
        remove_list(l);
    }    
    return;
}