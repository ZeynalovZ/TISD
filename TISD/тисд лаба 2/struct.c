typedef enum{KIND_PERSON, KIND_SERVICE} kind;

typedef struct
{
    char name[NAME_LENGHT + 1];
    char surname[SURNAME_LENGHT + 1];
    char phone_number[PHONE_NUMBER_LENGTH + 1];
    char adress[ADRESS_LENGHT + 1];
    //enum key {surname, name, adress};
    union
    {
        struct
        {
            char post[POST_LENGHT + 1];
            char service_name[SERVICE_LENGHT + 1];
        } service;
        struct
        {
            int day;
            int month;
            int year;
        } personal;
    } type_user;
} user;
