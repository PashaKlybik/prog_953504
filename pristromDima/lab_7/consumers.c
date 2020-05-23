#include "consumers.h"

int loadConsumerBase(ConsumerList *consumers, char *path)
{
    char *ext = strstr(path, ".con");
    if (ext == NULL)
        return 1;

    FILE *file = fopen(path, "rb");
    if (file == NULL)
        return 1;

    while(!feof(file))
    {
        Consumer offer;
        fread(&offer, sizeof(Consumer), 1, file);
        addConsumer(consumers, offer);
    }
    fclose(file);
    return 0;
}

int dumpConsumerBase(ConsumerList *consumers, char *raw_path)
{
    char str[5] = ".con";
    char *path = strcat(raw_path, str);
    FILE *file = fopen(path, "wb");
    if (file == NULL)
        return 1;

    struct ConsumerListNode *current = consumers->first;
    while (current != NULL)
    {
        current->value.request = NULL;
        fwrite(&current->value, sizeof(Consumer), 1, file);
        current = current->next;
    }
    fclose(file);
    return 0;
}

void addConsumer(ConsumerList *consumers, Consumer consumer)
{
    struct ConsumerListNode *new_node = malloc(sizeof *new_node);
    *new_node = (struct ConsumerListNode) { .value = consumer, .prev = NULL, .next = NULL };
    if (consumers->size == 0)
    {
        consumers->first = new_node;
        consumers->last = consumers->first;
    }
    else
    {
        consumers->last->next = new_node;
        new_node->prev = consumers->last;
        consumers->last = new_node;
    }
    consumers->size++;
}

int addOrder(ConsumerList *consumers, Consumer consumer, CarUnit *order)
{
    if (order != NULL)
    {
        Consumer *target = getConsumer(consumers, consumers->first, consumer);
        if (target != NULL)
        {
            target->request = malloc(sizeof(CarUnit));
            target->request = order;
            return 0;
        }
    }
    return 1;
}

int removeConsumer(ConsumerList *consumers, struct ConsumerListNode *node, Consumer consumer)
{
    if (node != NULL)
    {
        Consumer node_consumer = node->value;
        if (strcmp(node_consumer.name, consumer.name) == 0 && node_consumer.contacts == consumer.contacts)
        {
//            if (strcmp(consumer.request->model, node_consumer.request->model) == 0 && consumer.request->state == node_consumer.request->state &&
//                consumer.request->year == node_consumer.request->year && consumer.request->engine_capacity == node_consumer.request->engine_capacity &&
//                consumer.request->mileage == node_consumer.request->mileage && consumer.request->power == node_consumer.request->power)
            struct ConsumerListNode *node_to_remove = node;
            if (node->prev != NULL)
                node->prev = node->next;
            else if (node->next != NULL)
                node->next->prev = NULL;
            else
                consumers->first = consumers->last = NULL;
            free(node_to_remove);
            consumers->size--;
            return 0;
        }
        else
            return removeConsumer(consumers, node->next, consumer);
    }
    return 1;
}

int removeOrder(ConsumerList *consumers, Consumer consumer)
{
    Consumer *target = getConsumer(consumers, consumers->first, consumer);
    if (target != NULL)
    {
        free(target->request);
        target->request = NULL;
        return 0;
    }
    return 1;
}

Consumer* getConsumer(ConsumerList *consumers, struct ConsumerListNode *node, Consumer consumer)
{
    if (node != NULL)
    {
        Consumer node_consumer = node->value;
        if (strcmp(node_consumer.name, consumer.name) == 0 && node_consumer.contacts == consumer.contacts)
            return &node->value;
        else
            return getConsumer(consumers, node->next, consumer);
    }
    return NULL;
}

CarUnit* selectCar(CarList *cars, CarUnit order)
{
    struct CarListNode *current = cars->first;
    while (current != NULL)
    {
        if (strcmp(order.model, current->value.model) == 0 && order.state == current->value.state &&
            order.year <= current->value.year && order.power <= current->value.power &&
            order.engine_capacity <= current->value.engine_capacity && order.mileage >= current->value.mileage &&
            order.price >= current->value.price)
                return &current->value;
        current = current->next;
    }
    return NULL;
}

int buyCar(ConsumerList *consumers, CarList *cars, CarUnit *car, Consumer *consumer)
{
    if (!removeOrder(consumers, *consumer))
    {
        if (consumer->finances >= car->price)
        {
            sellCar(cars, *car);
            consumer->finances -= car->price;
            return 0;
        }
        else
        {
            addOrder(consumers, *consumer, car);
            return 1;
        }
    }
    return 1;
}

ConsumerList* searchConsumers(ConsumerList *consumers, Field field, char *value)
{
    ConsumerList *found = malloc(sizeof *found);
    *found = (ConsumerList) { .first = NULL, .last = NULL, .size = 0 };
    struct ConsumerListNode *current = consumers->first;
    while (current != NULL)
    {
        switch (field)
        {
            case NAME:
                if (!strcmp(current->value.name, value))
                    addConsumer(found, current->value);
                break;
            case CONTACTS:
                if (current->value.contacts == atoi(value))
                    addConsumer(found, current->value);
                break;
            case FINANCES:
                if (current->value.contacts == atoi(value))
                    addConsumer(found, current->value);
                break;
        }
        current = current->next;
    }
    return (found->size != 0) ? found : NULL;
}

void deallocConsumerList(ConsumerList *consumers)
{
    if (consumers != NULL)
    {
        struct ConsumerListNode *current = consumers->first;
        while (current != NULL)
        {
            if (current->prev != NULL)
                free(current->prev);
            current = current->next;
        }
        free(consumers);
    }
}
