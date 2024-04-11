#include "list.h"


int ListCtor(LIST *list)
    {
    assert(list);

    list->capacity = capacity_list;

    list->size     = size_list;

    list->status   = NO_ERROR;

    list->free     = 1;

    list->front    = ZERO;

    list->back     = ZERO;

    list->data = (Node*)calloc(list->capacity, sizeof(Node));

    if (list->data == nullptr)
        {
        return ALLOC_FAIL;
        }

    SetList(list, 1);

    list->data[ZERO].next = ZERO;

    list->data[ZERO].prev = ZERO;

    return list->status;
    }


int ListVerify(LIST* list)
    {
    if (list == nullptr)
        {
        list->status |= NULL_LIST;
        }
        
    if (list->data == nullptr)
        {
        list->status |= NULL_DATA;
        }

    if (list->capacity < ZERO)
        {
        list->status |= CAPACITY_LESS_THAN_ZERO;
        }

    if (list->size < ZERO)
        {
        list->status |= SIZE_LESS_THAN_ZERO;
        }


    if (list->size > list->capacity)
        {
        list->status |= CAPACITY_LESS_THAN_SIZE;
        }

    return list->status;
    }


void ListDtor(LIST* list)
    {
    assert(list);

    list->capacity = POISON_NUMBER_FOR_VALUE;

    list->size     = POISON_NUMBER_FOR_VALUE;

    list->free     = POISON_NUMBER_FOR_VALUE;

    list->front    = POISON_NUMBER_FOR_VALUE;

    list->back     = POISON_NUMBER_FOR_VALUE;

    free(list->data);
    }


int PushFront(LIST* list, List_type value)
    {
    return ListInsert(list, value, list->front);
    }


int PushBack(LIST* list, List_type value)
    {
    return ListInsert(list, value, list->data[list->back].next);
    }


void UpdateParams(LIST* list) 
    {
    list->front = list->data[ZERO].next;

    list->back = list->data[ZERO].prev;
    }


int ListInsert(LIST* list, List_type value, iterator_t index)
    {
    CHECK_LIST_ERROR(list);

    if (list->size + 1 >= list->capacity)
        {
        ListResize(list, list->capacity * size_extend);
        }

    iterator_t old_free = list->free;

    list->free = list->data[old_free].next;

    list->data[old_free].value = value;

    if (list->size == ZERO) 
        {
        list->data[old_free].next = ZERO;

        list->data[old_free].prev = ZERO;

        list->data[ZERO].next = old_free;

        list->data[ZERO].prev = old_free;

        list->front = old_free;

        list->back = old_free;

        list->size++;

        return list->status;
        } 

    else 
        {
        list->data[old_free].next = index;

        list->data[old_free].prev = list->data[index].prev;

        list->data[list->data[index].prev].next = old_free;

        list->data[index].prev = old_free;
        }

    UpdateParams(list);

    list->size++;

    CHECK_LIST_ERROR(list);

    return list->status;
    }


int PopFront(LIST* list)
    {
    return ListDelete(list, list->front);
    }


int PopBack(LIST* list)
    {
    return ListDelete(list, list->back);
    }


int ListDelete(LIST* list, iterator_t index)
    {
    CHECK_LIST_ERROR(list);

    if (index >= list->capacity)
        {
        return INDEX_BIGGER_THAN_CAPACITY;
        }

    if (list->size == ZERO)
        {
        return POP_NULL;
        }

    list->data[index].value = (List_type)POISON_NUMBER_FOR_VALUE;

    list->data[list->data[index].prev].next = list->data[index].next;

    list->data[list->data[index].next].prev = list->data[index].prev;

    iterator_t old_free = list->free;

    list->free = index;

    list->data[list->free].prev = FREE_INDEX;

    list->data[list->free].next = old_free;

    UpdateParams(list);

    list->size--;

    CHECK_LIST_ERROR(list);

    return list->status;
    }


static int ListResize(LIST* list, int new_capacity_list)
    {
    CHECK_LIST_ERROR(list);

    if (new_capacity_list <= ZERO)
        {
        return WRONG_NEW_CAPACITY;
        }

    list->capacity = new_capacity_list;

    Node* new_data = (Node*)calloc(new_capacity_list, sizeof(Node));

    if (new_data == nullptr)
        {
        return ALLOC_FAIL;
        }

    for (size_t i = ZERO; i <= list->size; i++)
        {
        (new_data)[i].next  = list->data[i].next;

        (new_data)[i].prev  = list->data[i].prev;

        (new_data)[i].value = list->data[i].value;
        }
    
    free(list->data);

    list->data = new_data;

    SetList(list, list->size + 1);

    list->free = list->size + 1;

    CHECK_LIST_ERROR(list);

    return list->status;    
    }


iterator_t NextCurIndex(LIST* list, size_t index)
    {
    return list->data[index].next;
    }


iterator_t PrevCurIndex(LIST* list, size_t index)
    {
    return list->data[index].prev;
    }


iterator_t Begin(LIST* list)
    {
    return list->front;
    }


iterator_t End(LIST* list)
    {
    return PrevCurIndex(list, list->front);
    }


iterator_t FindByIndex(LIST* list, size_t index)
    {
    iterator_t cur_ind = Begin(list);

    for (size_t i = ZERO; i < index; i++)
        {
        cur_ind = NextCurIndex(list, index);
        }

    return cur_ind;
    }


void ListGraphDumpFunction(LIST* list, const char* path, const char* signature, unsigned line)
    {
    assert(list);

    graph_file = fopen("dotfile.dot", "wb");

    static int dump_number = 1;

    print("digraph G {bgcolor=RosyBrown rankdir = TB\n" "splines = ortho; edge[minlen = 3, penwidth = 2; color = blue];\n\n");

    print("label = \"list_dump from function %s, List_Index/%s:%d\";\n", signature, path, line);

    print("Info[shape=record, fillcolor=\"grey\", width=0.2, style=\"filled\","
            "label=\" {Capacity: %zu | Size: %zu | Free: %d | Front: %d | Back: %d}\"] \n\n",
            list->capacity, list->size, list->free, list->front, list->back);

    print("{rank = max; node0[shape=record, width=0.2, style=\"filled\", fillcolor=\"purple\","
                "label=\" {id: 0 | value: NILL | next: %d | prev: %d}\"]} \n \n",
                list->data[ZERO].next, list->data[ZERO].prev);

    print("{rank = same;\n");

    for (size_t i = 1; i < list->capacity; i++)
        {
        if (list->data[i].prev == FREE_INDEX)
            {
            print("node%zu[shape=record, width=0.2, style=\"filled\", fillcolor=\"red\","
                    "label=\" {id: %zu | value: %s | next: %d | prev: %d}\"] \n \n",
                    i, i, "POIZON", list->data[i].next, list->data[i].prev);
            }
        else
            {
            print("node%zu[shape=record, width=0.2, style=\"filled\", fillcolor=\"green\","
                    "label=\" {id: %zu | value: %s | next: %d | prev: %d}\"] \n \n",
                    i, i, list->data[i].value, list->data[i].next, list->data[i].prev);
            }   
        }
    
    print("}\n");

    print("Free[color=orange, style=filled]");

    print("Front[color=orange, style=filled]");

    print("Back[color=orange, style=filled]");

    print("Free->node%d\n", list->free);

    print("Front->node%d\n", list->front);

    print("Back->node%d\n\n", list->back);

    print("edge[color=darkgreen, constraint = true]\n");

    print("node0");

    for (size_t i = 1; i < list->capacity; i++)
        {
        print(" -> node%zu", i);

        if (i == list->capacity - 1)
            {
            print("\n[style=invis, weight = 10000];");
            }
        }

    print("\n\n");

    print("edge[style=solid, constraint = false]\n");

    for (size_t i = 1; i < list->capacity; i++)
        {
        print("node%zu -> node%d;\n", i, list->data[i].next);
        }

    print("\n}");

    fclose(graph_file);

    char shell_command[MAX_COMMAND_LENGTH] = "";
    sprintf(shell_command, "dot -v -Tpng dotfile.dot -o graph%d.png", dump_number);
    system(shell_command);


    log_file = fopen("log_file.html", "a");

    fprintf(log_file, "<pre>\n");

    fprintf(log_file, "<img width=\"1100px\" height=\"500px\" src=\"graph%d.png\">", dump_number);

    fprintf(log_file, ".\n");
        
    fclose(log_file);

    dump_number++;
    }


static void SetList(LIST* list, size_t size)
    {
    assert(list);

    for (size_t i = size; i < list->capacity; i++)
        {
        list->data[i].next  = i + 1;

        list->data[i].prev  = FREE_INDEX;

        list->data[i].value = (List_type)POISON_NUMBER_FOR_VALUE;
        }

    list->data[list->capacity - 1].next  = ZERO;
    }