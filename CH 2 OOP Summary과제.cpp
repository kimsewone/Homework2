#include <iostream>
#include <string>
#include <list>
using namespace std;
enum EAnimal
{
	DOG,
	CAT,
	COW,
	MAX
};

class Animal
{
public:
	Animal() {}
	virtual void makeSound() = 0;
	virtual void Action() = 0;
	~Animal() {}
};
class Dog :public Animal
{
public:
	Dog() {}
	void makeSound() override {
		cout << " Wal Wal Wal!" << endl;
	}
	void Action() override {
		cout << "  Dog Action!!" << endl;
	}
	~Dog() {}
};
class Cat :public Animal
{
public:
	Cat() {}
	void makeSound() override {
		cout << " Nyaong~ Nyaong~" << endl;
	}
	void Action() override {
		cout << " Cat Action!!" << endl;
	}
	~Cat() {}
};
class Cow :public Animal
{
public:
	Cow() {}
	void makeSound() override {
		cout << " Um~mea~ Um~mea~" << endl;
	}
	void Action() override {
		cout << " Cow Action!!" << endl;
	}
	~Cow() {}
};
Animal* createRandomAnimal()
{
	srand(time(NULL));

	int idx = rand() % EAnimal::MAX;

	Animal* animal = NULL;
	if (idx == EAnimal::DOG)
		animal = new Dog();
	else if (idx == EAnimal::CAT)
		animal = new Cat();
	else if (idx == EAnimal::COW)
		animal = new Cow();

	return animal;
}
class Zoo
{
public:
	Zoo() {
		animals = new Animal * [10];
	}

	//배열이 넘치면 그냥 막아버리는 로직.
	bool addAnimal_V1(Animal* animal) {
		if (animalCount >= 10)
		{
			cout << "Add Anamal Fail! Array Overflow!" << endl;
			return false;
		}
		animals[animalCount] = animal;
		animalCount++;

		return true;
	};
	void addAnimal(Animal* animal) {

		//애니멀 배열이 가득차면  배열을 10씩 늘려서 교체한다.
		if (animalCount >= Resize)
		{
			Resize = animalCount + 10;
			Animal** NewArr = new Animal * [Resize];//(Animal**)malloc(sizeof(Animal*) * Resize) ;

			for (int i = 0; i < animalCount;++i)
			{
				NewArr[i] = animals[i];
			}
			delete[] animals;
			animals = NewArr;
		}

		animals[animalCount] = animal;
		animalCount++;

	};
	void performActions() {

		for (int i = 0; i < animalCount;++i) {
			Animal* ani = animals[i];
			ani->makeSound();
			ani->Action();
		}
	};
	void deleteAnamals()
	{
		for (int i = 0; i < animalCount;++i) {
			Animal* ani = animals[i];
			delete ani;
		}
		delete[] animals;
	}
	~Zoo() {
	}
private:
	//Animal* animals[10];
	Animal** animals;

	int animalCount = 0;
	int Resize = 10;
public:
	Animal** GetAnimals() {
		return animals;
	}
	int GetTotalAnimalCount() {
		return animalCount;
	}
};
void AddAnimalZoo(Zoo* zoo, Animal* animal)
{
	bool IsCreat = zoo->addAnimal_V1(animal);
	if (!IsCreat)
	{
		delete animal;
		//animal = nullptr;
	}
}
int main()
{
	Zoo* zoo = new Zoo();
	Animal* creatAnimal = NULL;

	for (int i = 0; i < 3;++i) {
		creatAnimal = createRandomAnimal();
		zoo->addAnimal(creatAnimal);
		//AddAnimalZoo(zoo, creatAnimal);
	}

	Animal* animalArr[5] = { new Dog(), new Cat(),new Cow(), new Dog(),new Cat() };

	size_t  size = sizeof(animalArr) / sizeof(animalArr[0]);
	for (int i = 0; i < size;++i)
	{
		zoo->addAnimal(animalArr[i]);
	}

	for (int i = 0; i < zoo->GetTotalAnimalCount(); ++i)
	{
		zoo->GetAnimals()[i]->makeSound();
	}
	zoo->performActions();

	for (int i = 0; i < 10;++i) {
		creatAnimal = createRandomAnimal();
		zoo->addAnimal(creatAnimal);
		//AddAnimalZoo(zoo, creatAnimal);
	}

	zoo->performActions();

	zoo->deleteAnamals();
	return 0;
}
