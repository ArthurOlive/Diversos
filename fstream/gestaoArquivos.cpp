#include <iostream>
#include <fstream> //Funções ifstream e ofstream usadas
#include <conio.h> //Função _getch() usada
using namespace std;

//Classe simples que armazena o nome e a idade da pessoa, esse registro poderia ter sido feito com n atributos;
class Pessoa {
private:
	char nome[20]; //Nome da pessoa
	int idade; //idade
public:
	Pessoa() {
		//construtor default
	}
	~Pessoa() {
		//destrutor default
	}
	//funções get e set
	void setNome(char name[]) {
		strcpy_s(this->nome, name);
	}
	char* getNome() {
		return nome;
	}
	void setIdade(int &old) {
		this->idade = old;
	}
	int& getIdade() {
		return idade;
	}
	//sobrecarga do operador de leitura >>
	friend istream &operator >> (istream &input, Pessoa &p) {
		char nome[20];
		int idade;
		input >> nome;
		input >> idade;
		p.setNome(nome);
		p.setIdade(idade);
		return input;
	}
	//sobrecarga do operador de escrita <<  
	friend ostream &operator << (ostream &output, Pessoa &p) {
		output  << "\n" << p.getNome() << "\n" << p.getIdade();
		return output;
	}
};


char menu() {
	cout << "Opcoes: \n";
	cout << "1 - Salva pessoas: \n" 
		<< "2 - Listar pessoas : \n"
		<< "3 - Sair\n";
	cout << "Escolha: ";
	return _getche();
}

int main() {
	//loop infinito
	while (true) {
		char esc = menu();
		cout << endl << endl;
		if (esc == '1') {
			Pessoa p;
			char nome[20];//Vetor que irá receber o nome
			int idade;//Vetor que irá receber a idade
			
			cout << "\n";
			cout << "Digite o nome: ";
			cin >> nome;
			cout << "Digite a idade: ";
			cin >> idade;
			cout << "\n";

			p.setNome(nome);
			p.setIdade(idade);

			ofstream arquivoO; //ofstream que irá realizar as operações de armazenamento
			arquivoO.open("Usuarios.txt", ofstream::app);//local do arquivo no modo append
			arquivoO << p;//Passa o objeto
			arquivoO.close(); //Fecha o arquivo
		}
		else if (esc == '2') {
			ifstream arquivoI; //ofstream que irá realizar as operações de leitura
			arquivoI.open("Usuarios.txt");//local do arquivo

			if (arquivoI.good()) {
				cout << "Usuarios:" << endl;
				while (!arquivoI.eof()) //enquanto o arquivo tiver linhas preenchidas
				{
					Pessoa p;
					arquivoI >> p;
					cout << "Nome:  " << p.getNome() << endl; //mostra a pessoa
					cout << "Idade: " << p.getIdade() << "\n\n";
				}
				arquivoI.close(); //Fecha o arquivo
			}
			else {
				cout << "Arquivo não existe, cadastre alguem para criar o arquivo.\n";
			}
		}
		else if (esc == '3') {
			cout << "Ate mais :-).\n";
			break; //Sai do loop
		}
		else {
			cout << "Opção invalida, tente novamente.\n";
			system("cls"); //limpa a tela no windows
		}
	}
	system("pause");
	return 0;
}