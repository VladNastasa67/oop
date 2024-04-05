#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class PowerPuffGirl
{
public:
	float damage;
	float health;
	const char* nume;
	virtual const char* GetNume() = 0;
	virtual void SetNume(const char* nume) = 0;
};
class Bubbles:public PowerPuffGirl
{
public:
	Bubbles() {
		damage = 15;
		health = 80;
		nume = "Bubbles";
	}
	const char* GetNume()
	{
		return this->nume;
	}
	void SetNume(const char* nume)
	{
		this->nume = nume;
	}
};
class Blossom:public PowerPuffGirl
{
public:
	Blossom() {
		damage = 25;
		health = 100;
		nume = "Blossom";
	}
	const char* GetNume()
	{
		return this->nume;
	}
	void SetNume(const char* nume)
	{
		this->nume = nume;
	}
};
class ButterCup:public PowerPuffGirl
{
public:
	ButterCup() {
		damage = 40;
		health = 80;
		nume = "ButterCup";
	}
	const char* GetNume()
	{
		return this->nume;
	}
	void SetNume(const char* nume)
	{
		this->nume = nume;
	}
};
class MojoJojo
{
public:
	float damage=50;
	float health=300;
};
class Profesor
{
	MojoJojo MJ;
	PowerPuffGirl** girl;
	int nr;
	int sugar;
	int spices;
	int nice;
	int ture;
	int jojo;
	int death;
public:
	Profesor()
		{
			death = 0;
	        jojo = 1;
			ture = 0;
			sugar = 0;
			spices = 0;
			nice = 0;
			nr = 0;
			girl = new PowerPuffGirl * [100];
		}
	void Incrediente(int sugar, int spices, int nice)
	{
		this->sugar = sugar;
		this->spices = spices;
		this->nice = nice;
	}
	void Creare()
	{
		srand(time(nullptr));
		while (this->sugar and this->spices and this->nice)
		{
			int sansa = rand() % 3;
			if (sansa == 1)
				girl[this->nr++] = new Bubbles;
			else if (sansa == 2)
				girl[this->nr++] = new Blossom;
			else 
				girl[this->nr++] = new ButterCup;
			this->sugar--;
			this->spices--;
			this->nice--;
		}
	}
	void FetiteCreate()
	{
		for (int i = 1; i <= this->nr; i++)
			cout << "A fost creata " << girl[i]->GetNume()<<'\n';
	}
	void Lupta()
	{

		srand(time(nullptr));
		int damagetot = 0;
		for (int i = 0; i < this->nr; i++)
			damagetot = damagetot + girl[i]->damage;
		while (this->nr > 0)
		{
			this->ture++;
			int sansa = rand() % this->nr;
			MJ.health = MJ.health - damagetot;
			if (MJ.health < 0)
			{
				jojo = 0;
				break;
			}
			girl[sansa]->health = girl[sansa]->health - MJ.damage;
			if (girl[sansa]->health < 0)
			{
				death++;
				for (int i = sansa; i < this->nr; i++)
					girl[i] = girl[i + 1];
				this->nr--;
			}
		}

	}
	void Stats()
	{
		if (jojo == 0)
			cout << "Fetitele au castigat " << '\n';
		else cout << "MojoJojo a castigat" << '\n';
		cout << "Lupta a durat " << this->ture <<" runde " << "si au murit " << this->death << " fetite " << '\n';
	}
	int Survive()
	{
		if (this->nr == 0)
		{
			cout << "Nu a supravietuit nicio fetita " << '\n';
			return 0;
		}
		cout << "Au supravietuit " << this->nr <<" fetite"<<  '\n';
		for (int i = 0; i < this->nr; i++)
			cout << girl[i]->GetNume() << " a ramas cu " << girl[i]->health << " viata" << '\n';
		return 1;
	}

};
int main()
{
	Profesor p;
	p.Incrediente(4, 5, 7);
	p.Creare();
	//p.FetiteCreate();
	p.Lupta();
	p.Stats();
	p.Survive();

}
