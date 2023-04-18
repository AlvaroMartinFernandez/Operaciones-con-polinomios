#ifndef CPOLINOMIO_H
#define CPOLINOMIO_H
#include "CMonomio.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class CPolinomio {
private:
	vector<CMonomio> m_monomios;	// Primer término (el de mayor grado)
public:
	//Constructores
	CPolinomio();//1
	//2
	CPolinomio(double dCoef, int nExp = 0);//3
	CPolinomio(const vector<CMonomio>& polinomioVector);//4
	CPolinomio(const CMonomio mono);//5
	//destructor
	~CPolinomio();//6
	//7 Operador asignacion
	//FUNCIONES
	void MostrarPoli(ostream& os) const;
	int Grado()const;

	//sobrecargar operadores
	CPolinomio& operator<<(const CMonomio& mono);			// Insertion			<<
	bool operator<(const CPolinomio& polinomio);			// Sobrecargar menor	<
	bool operator>(const CPolinomio& polinomio);			// Sobrecargar mayor	>
	bool operator==(const CPolinomio& polinomio);			// Sobrecargar igual	==
	CPolinomio operator-();									// Negativo				-
	CPolinomio& operator+=(const CPolinomio& polinomio);	//						+=
	CPolinomio& operator-=(const CPolinomio& polinomio);	//						-=
	CPolinomio  operator+(const CPolinomio& polinomio);		// Suma					+
	CPolinomio  operator-(const CPolinomio& polinomio);		// Resta				-
	double operator[](int i);								// Braquets				[]
	double operator()(double i);							// Parentesis			()
	CPolinomio operator*(const CPolinomio& poli);			// Multiplication		*
	CPolinomio& operator*=(const CPolinomio& poli);			//						*=
};
ostream& operator<<(ostream& os, const CPolinomio& Poli);
#endif
