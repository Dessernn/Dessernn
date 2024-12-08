#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// структура для записи расходов
typedef struct{
	char date[11];//дата(формат:YYYY-MM-DD)
	char category[50];//категория расхода
	double amount;//сумма
	char description[100];//описание
}Expense;
//функция для добавления новой записи
void  addExpense(const char *filename){
	FILE *file= fopen(filename,"a");//открываем файл для обновления
	if (file == NULL){
		perror("не удалось открыть файл");
		exit(1);
	}
	Expense expense;
	printf("введите дату(YYYY-MM-DD):");
	scanf("%10s",expense.date);
	printf("введите категорию:");
	scanf("%49s",expense.category);
	printf("введите сумму:");
	scanf("%lf",&expense.amount);
	printf("введите описание:");
	getchar();//очистка буфера после ввода числа
	fgets(expense.description,sizeof(expense.description),stdin);
	//Удаляем символ новой строки в конце описания
	size_t len = strlen(expense.description);
	if (len>0 && expense.description[len-1]=='\n'){
		expense.description[len-1]='\0';
	}
	//Записываем данные в файл
	fprintf(file,"%s,%s,%.2lf,%s\n",expense.date,expense.category,expense.amount,expense.description);
	fclose(file);
	printf("Запись добавлена успешно!\n");
}
//Функция для просмотра всех записей
void viewExpenses(const char *filename){

	FILE *file=fopen(filename, "r");//Открываем файл для чтения
	if (file==NULL){
		perror("Не удалось открыть файл");
		exit(1);
	}
	Expense expense;
	printf("Список расходов:\n");
	printf("Дата | Категория | Сумма | Описание\n");
	printf("--------------------\n");
	while(fscanf(file, "%10[^,],%49[^,],%lf,%99[^\n]\n",expense.date,expense.category,&expense.amount,expense.description) ==4){
		printf("%-10s | %-17s | %-7.2lf | %s\n",expense.date,expense.category,expense.amount,expense.description);
	}
	fclose(file);
}
int main(int argc, char *argv[]){
	if (argc !=2){
		printf("Использование:%s <имя файла>\n", argv[0]);
		return 1;
	}
	const char *filename = argv[1];
	int choice;
	do{
		printf("\nМеню:\n");
		printf("1. Добавить новую запись\n");
		printf("2. \n");
		printf("0. Выход\n");
		printf("Выберите действие: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				addExpense(filename);
				break;
			case 2:
				viewExpenses(filename);
				break;
			case 0:
				printf("Выход из программы.\n");
				break;
			default:
				printf("Неверный выбор. Попробуйте снова.\n");
		}
	}while (choice != 0);
	return 0;
}
