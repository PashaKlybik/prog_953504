//6.2 (9).HotelTracer.Программа работает с базами данных семи мировых
//туристических сайтов : www.HotelQuest.com, www.TravelWeb.com,
//www.opodo.com, www.hotels.com, www.orbitz.com,
//www.AllHotels.com, www.TravelWorm.com.Каждая база данных
//представляет собой двоичный файл, содержащий информацию о
//свободных номерах в отеле : город, название отеля, адрес отеля,
//класс номера(обычный класс, полулюкс, люкс, vip - номер),
//количество мест и стоимость номера.Информация в базах данных
//обновляется каждые 60 секунд.HotelTracer ищет наилучший отель,
//соответствующий запросу пользователя.Примеры запросов :
//“Венеция, престижный номер на двоих, цена не имеет значения”,
//“София, одиночный номер по минимальной цене”.Функции
//бронирования номера и снятия брони.


//Kinda example what to enter for hotel searching
//Minsk expensive room for two 25000


#include <cstdio>
#include <cstring>
#include <malloc.h>
#include <locale.h>

#include "HotelTracer.h"

int main()
{
    MenuChoiceGetter();

    SearchStringProcessing();

    return 0;
}