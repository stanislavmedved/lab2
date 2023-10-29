// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#include "lab2.h"

std::vector<std::string> names = {};
std::vector<int> grades = {}; //оценки 0-100

int main()
{
	setlocale(LC_ALL, "rus");
	char* input = new char;
	//цикл ввода
	while (true) {
		system("cls");
		printf("Выберите способ инициализации вектора:\n\n"
			"1. Демонстрационный анализ на предустановленных значениях.\n"
			"2. Анализ на случайных значениях\n"
			"3. Ввод и анализ значений\n\n"
			"Введите выбор и нажмите Enter: ");
		std::cin >> *input;

		if (!isdigit(*input)) continue;
		if (0 < (int)*input < 4) break;
	}
	int choice = (int)*input - 48;
	switch (choice) {
	case 1:
		demoAnalysis();
		break;
	case 2:
		randomAnalysis();
		break;
	case 3:
		inputAnalysis();
		break;
	}
}

void demoAnalysis() {
	//прописать 10 значений
	names = { "Владислав", "Андрей", "Георгий", "София", "Александр", "Дмитрий", "Светлана", "Николай", "Мохаммед", "Алоис"};
	grades = { 38,83,41,48,32,50,26,52,50,65 };
	//вывести вектора
	rangePrint();
	//сделать и вывести анализ
	printAvgGrade();
	printMedian();
	printMode();
}
void randomAnalysis() {
	//принять размер выборки
	std::cout << "Введите размер выборки: ";
	int setSize = 1;
	std::cin >> setSize;
	//сгенерировать 
	//и вывести вектора
	forLoopPrint();
	//сделать и вывести анализ
}
void inputAnalysis() {
	//принимать значения от пользователя до пустой строчки
	//вывести вектора
	iterationPrint();
	//сделать и вывести анализ
	//войти в цикл приема/удаления
}

void rangePrint() {
	//у нас нет какого-то красивого пути итерировать таким способом по двум векторам одновременно,
	//поэтому придется соединить их в таблицу-буфер
	std::map<std::string, int> buffer;
	// create buffer map
	std::transform(names.begin(), names.end(), grades.begin(), std::inserter(buffer, buffer.end()), [](std::string a, int b)
		{
			return std::make_pair(a, b);
		});
	for (auto& [a, b] : buffer) std::cout << a << ' ' << b << '\n';
	std::cout << '\n';
}

void iterationPrint() {
	for (auto [n, g] = std::tuple{names.begin(), grades.begin()}; n != names.end() && g != grades.end(); n++, g++) 
		std::cout << *n << ' ' << *g << '\n';
	std::cout << '\n';
}

void forLoopPrint() {
	for(int i = 0; i < std::min(names.size(), grades.size()); i++) 
		std::cout << names[i] << ' ' << grades[i] << '\n';
	std::cout << '\n';
}

void printAvgGrade() {
	double avg = 0.0;
	for (auto i : grades) avg += (double)i;
	avg /= grades.size();
	std::cout << "Среднее значение оценок: " << avg << '\n';
}

void printMedian() {
	std::vector<int> sortedGrades = grades;
	cocktailSort(sortedGrades);
	double median = (sortedGrades.size() % 2 == 0) ? getMedianFromEvenVector(sortedGrades) : sortedGrades.at(std::floor(sortedGrades.size() / 2));
	std::cout << "Медиана: " << median << '\n';
}

double getMedianFromEvenVector(std::vector<int> input) {
	return (input.at(input.size() / 2) + input.at(input.size() / 2 - 1)) / 2;
}

void printMode() {
	//заполняем таблицу частот оценок
	std::unordered_map<int, int> gradesHashmap;
	for (auto i : grades) {
		gradesHashmap[i] += 1;
	}
	//находим максимальную частоту
	int maxFreq = 0;
	for (auto& [a, b] : gradesHashmap) {
		if (b > maxFreq) maxFreq = b;
	}
	//находим все оценки с максимальной частотой
	std::vector<int> freqGrades;
	for (auto& [a, b] : gradesHashmap) {
		if (b == maxFreq) freqGrades.push_back(a);
	}
	//выводим
	std::cout << "Моды: ";
	for (auto i : freqGrades) std::cout << i << ' ';
	std::cout << '\n';
	//выводим всех студентов с оценками максимальной частоты
	std::cout << "Ученики, оценка которых соответствует моде (модам):\n";
	for (int i = 0; i < names.size(); i++) {
		if (std::find(freqGrades.begin(), freqGrades.end(), grades.at(i)) != freqGrades.end()) {
			std::cout << names.at(i) << ' ' << grades.at(i) << '\n';
		}
	}
}

// сортирует вектор чисел с помощью cocktail shaker sort
// принимает ссылку на вектор
void cocktailSort(std::vector<int>& input)
{
	// флаг перестановки двух элементов
	bool swapped = true;
	// счетчик начальной позиции
	int start = 0;
	// счетчик конечной позиции
	int end = input.size() - 1;

	// цикл работает, пока мы можем переставлять элементы в векторе
	while (swapped) {
		// сбрасываем флаг при начале цикла, так как он может быть true после предыдущей итерации
		swapped = false;

		// проходим циклом слева направо, как в пузырьковой сортировке
		for (int i = start; i < end; ++i) {
			// если текущий элемент больше следующего
			if (input[i] > input[i + 1]) {
				// переставляем элементы
				std::swap(input[i], input[i + 1]);
				// и поднимаем флаг
				swapped = true;
			}
		}
		// если ни один элемент не был переставлен - вектор отсортирован
		if (!swapped)
			// без комментариев
			break;
		// иначе сбрасываем флаг и переходим к следующему этапу
		swapped = false;
		// сдвигаем указатель конца на один влево, так как самый правый элемент уже на месте
		--end;
		// ещё одна пузырьковая сортировка, но уже справа налево
		for (int i = end - 1; i >= start; --i) {
			// если текущий элемент больше следующего
			if (input[i] > input[i + 1]) {
				// переставляем элементы
				std::swap(input[i], input[i + 1]);
				// и поднимаем флаг
				swapped = true;
			}
		}
		// сдвигаем указатель начала на один вправо, так как самый левый элемент уже на месте
		++start;
	}
}