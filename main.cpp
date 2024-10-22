#include <iostream>
#include <cstring>
#include <cstdlib> // для malloc и realloc
#include <algorithm>

// Структура для хранения информации о задаче
struct Task {
    char* task_name;   // Указатель на динамически выделенную строку для названия задачи
    int priority;      // Приоритет задачи (целое число)
    char* deadline;    // Указатель на динамически выделенную строку для срока выполнения
};

// Функция для добавления задачи
void addTask(Task*& tasks, int& size) {
    // Увеличиваем размер массива задач
    size += 1;
    tasks = (Task*)realloc(tasks, size * sizeof(Task)); // Изменяем размер массива задач

    char buffer[100]; // Буфер для временного хранения строк

    // Ввод названия задачи
    std::cout << "Введите название задачи: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    tasks[size - 1].task_name = (char*)malloc((strlen(buffer) + 1) * sizeof(char)); // Выделяем память для строки
    strcpy(tasks[size - 1].task_name, buffer); // Копируем введенное название задачи

    // Ввод приоритета задачи
    std::cout << "Введите приоритет задачи (от 1 до 10): ";
    std::cin >> tasks[size - 1].priority;
    std::cin.ignore(); // Игнорируем символ новой строки

    // Ввод срока выполнения задачи
    std::cout << "Введите срок выполнения задачи (например, \"10 октября\"): ";
    std::cin.getline(buffer, 100);
    tasks[size - 1].deadline = (char*)malloc((strlen(buffer) + 1) * sizeof(char)); // Выделяем память для срока выполнения
    strcpy(tasks[size - 1].deadline, buffer); // Копируем срок выполнения

    std::cout << "Задача добавлена!\n";
}

// Функция для сортировки задач по убыванию приоритета
bool compareTasks(const Task& a, const Task& b) {
    return a.priority > b.priority;
}

// Функция для вывода всех задач
void printTasks(Task* tasks, int size) {
    std::cout << "Список задач (по убыванию приоритета):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". Задача: " << tasks[i].task_name
                  << ", Приоритет: " << tasks[i].priority
                  << ", Срок выполнения: " << tasks[i].deadline << std::endl;
    }
}

// Функция для освобождения памяти
void freeTasks(Task* tasks, int size) {
    for (int i = 0; i < size; ++i) {
        free(tasks[i].task_name);  // Освобождаем память для названия задачи
        free(tasks[i].deadline);   // Освобождаем память для срока выполнения
    }
    free(tasks); // Освобождаем память для массива задач
}

int main() {
    Task* tasks = nullptr; // Указатель на массив задач (динамический массив)
    int size = 0;          // Количество задач
    std::string user_input;

    while (true) {
        addTask(tasks, size); // Добавляем новую задачу

        std::cout << "Хотите добавить еще одну задачу? (да/нет): ";
        std::getline(std::cin, user_input);

        if (user_input == "нет") {
            break; // Выход из цикла, если пользователь не хочет добавлять задачи
        }
    }

    // Сортировка задач по убыванию приоритета
    std::sort(tasks, tasks + size, compareTasks);

    // Вывод списка задач
    printTasks(tasks, size);

    // Освобождение динамически выделенной памяти
    freeTasks(tasks, size);

    return 0;
}
