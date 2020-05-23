#include <cars.h>

int loadCarBase(CarList *cars, char *path)
{
    char *ext = strstr(path, ".car");
    if (ext == NULL)
        return 1;

    FILE *file = fopen(path, "rb");
    if (file == NULL)
        return 1;

    CarUnit car;
    while (fread(&car, sizeof(CarUnit), 1, file) == 1)
        addCar(cars, car);
    fclose(file);
    return 0;
}

int dumpCarBase(CarList *cars, char *raw_path)
{
    char str[5] = ".car";
    char *path = strcat(raw_path, str);
    FILE *file = fopen(path, "wb");
    if (file == NULL)
        return 1;

    struct CarListNode *current = cars->first;
    while (current != NULL)
    {
        fwrite(&current->value, sizeof(CarUnit), 1, file);
        current = current->next;
    }
    fclose(file);
    return 0;
}

void addCar(CarList *cars, CarUnit car)
{
    struct CarListNode *new_node = malloc(sizeof *new_node);
    *new_node = (struct CarListNode) { .value = car, .prev = NULL, .next = NULL };
    if (cars->size == 0)
    {
        cars->first = new_node;
        cars->last = cars->first;
    }
    else
    {
        cars->last->next = new_node;
        new_node->prev = cars->last;
        cars->last = new_node;
    }
    cars->size++;
}

int removeCar(CarList *cars, struct CarListNode *node, CarUnit car)
{
    if (node != NULL)
    {
        CarUnit node_car = node->value;
        if (strcmp(car.model, node_car.model) == 0 && car.state == node_car.state && car.year == node_car.year &&
            car.engine_capacity == node_car.engine_capacity && car.mileage == node_car.mileage &&
            car.power == node_car.power)
        {
            struct CarListNode *node_to_remove = node;
            if (node->prev != NULL)
            {
                node->prev->next = node->next;
                node->next = node->prev;
            }
            else if (node->next != NULL)
            {
                cars->first = node->next;
                node->next->prev = NULL;
            }
            else
                cars->first = cars->last = NULL;
            free(node_to_remove);
            cars->size--;
            return 0;
        }
        else
            return removeCar(cars, node->next, car);
    }
    return 1;
}

void sortByField(CarList *cars, Field field)
{
    struct CarListNode *min_node = cars->first;
    struct CarListNode *max_node = cars->last;

    struct CarListNode *current;
    int min = 0, max = cars->size - 1;
    switch (field)
    {
        case YEAR:
        {
            do
            {
                current = min_node;
                for (int i = 0; i < max; i++)
                {
                    if (current->value.year > current->next->value.year)
                    {
                        CarUnit temp;
                        temp = current->value;
                        current->value = current->next->value;
                        current->next->value = temp;
                    }
                    current = current->next;
                }
                max_node = max_node->prev; max--;

                current = max_node;
                for (int i = max; i > min; i--)
                {
                    if (current->value.year < current->prev->value.year)
                    {
                        CarUnit temp;
                        temp = current->value;
                        current->value = current->prev->value;
                        current->prev->value = temp;
                    }
                    current = current->prev;
                }
                min_node = min_node->next; min++;
            }
            while (min_node->value.year < max_node->value.year);
            break;
        }
        case PRICE:
        {
            do
            {
                current = min_node;
                for (int i = 0; i < max; i++)
                {
                    if (current->value.price > current->next->value.price)
                    {
                        CarUnit temp;
                        temp = current->value;
                        current->value = current->next->value;
                        current->next->value = temp;
                    }
                    current = current->next;
                }
                max_node = max_node->prev; max--;

                current = max_node;
                for (int i = max; i > min; i--)
                {
                    if (current->value.price < current->prev->value.price)
                    {
                        CarUnit temp;
                        temp = current->value;
                        current->value = current->prev->value;
                        current->prev->value = temp;
                    }
                    current = current->prev;
                }
                min_node = min_node->next; min++;
            }
            while (min_node->value.price < max_node->value.price);
            break;
        }
    }
}

CarList* searchCars(CarList *cars, Field field, char *value)
{
    CarList *found = malloc(sizeof *found);
    *found = (CarList) { .first = NULL, .last = NULL, .size = 0, .sold = 0, .obtained = 0, .income = 0.0f };
    struct CarListNode *current = cars->first;
    while (current != NULL)
    {
        switch (field)
        {
            case MODEL:
                if (!strcmp(current->value.model, value))
                    addCar(found, current->value);
                break;
            case STATE:
                if (current->value.state == atoi(value))
                    addCar(found, current->value);
                break;
            case YEAR:
                if (current->value.year == atoi(value))
                    addCar(found, current->value);
                break;
            case ENGINE_CAPACITY:
                if (current->value.engine_capacity == atoi(value))
                    addCar(found, current->value);
                break;
            case MILEAGE:
                if (current->value.mileage == atoi(value))
                    addCar(found, current->value);
                break;
            case POWER:
                if (current->value.power == atoi(value))
                    addCar(found, current->value);
                break;
            case PRICE:
                if (current->value.price < strtof(value, NULL))
                    addCar(found, current->value);
                break;
        }
        current = current->next;
    }
    return (found->size != 0) ? found : NULL;
}

void sellCar(CarList *cars, CarUnit car)
{
    removeCar(cars, cars->first, car);
    cars->sold++;
    cars->income += car.price;
}

void obtainCar(CarList *cars, CarUnit order)
{
    float result_price = order.price + 250;
    if ((CURRENT_YEAR - order.year) <= 3)
        result_price += (order.engine_capacity * 0.6f);
    else if ((CURRENT_YEAR - order.year) > 3 && (CURRENT_YEAR - order.year) < 10)
    {
        if (order.engine_capacity < 2500)
            result_price += (order.engine_capacity * 0.35f);
        else
            result_price += (order.engine_capacity * 0.6f);
    }
    else if ((CURRENT_YEAR - order.year) >= 10 && (CURRENT_YEAR - order.year) < 14)
        result_price += (order.engine_capacity * 0.6f);
    else
        result_price += (order.engine_capacity * 2.0f);

    CarUnit new_car = { .state = order.state, .year = order.year, .engine_capacity = order.engine_capacity,
                        .mileage = order.mileage, .power = order.power, .price = 1.15f * result_price };
    strcpy(new_car.model, order.model);
    addCar(cars, new_car);
    cars->obtained++;
    cars->income -= result_price;
}

void deallocCarList(CarList *cars)
{
    if (cars != NULL)
    {
        struct CarListNode *current = cars->first;
        while (current != NULL)
        {
            if (current->prev != NULL)
                free(current->prev);
            current = current->next;
        }
        free(cars);
    }
}
