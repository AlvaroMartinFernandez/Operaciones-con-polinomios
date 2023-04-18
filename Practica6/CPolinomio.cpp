#include <string>
#include <iostream>
#include <vector>
#include "CPolinomio.h"
#include <math.h>

using namespace std;
//-------------------------Los 7 puntos ---------------------------
// los puntos 2 y 7 no harian falta ya que el contructor copia y el de asignacion el compilador lo crean por defecto
CPolinomio::CPolinomio() {//1
	vector<CMonomio> aux;
	m_monomios = aux;
}

CPolinomio::CPolinomio(double dCoef, int nExp) {//3
	if (dCoef == 0) {
		vector<CMonomio> aux;
		m_monomios = aux;
	}
	else {
		m_monomios = vector<CMonomio>(1, CMonomio(dCoef, nExp));
	}
}
CPolinomio::CPolinomio(const vector<CMonomio>& vectorPoli) {//4 
	vector<CMonomio> aux;
	m_monomios = aux;
	for (int i = 0; i < vectorPoli.size(); i++) {
		if (vectorPoli[i].GetCoef() != 0) {
			if (m_monomios.empty())
				m_monomios = vector<CMonomio>(1, vectorPoli[i]);
			else
				*this << vectorPoli[i];
		}
	}
}
CPolinomio::CPolinomio(const CMonomio mono) {//5
	if (mono.GetCoef() == 0) {
		vector<CMonomio> aux;
		m_monomios = aux;
	}
	else {
		m_monomios = vector<CMonomio>(1, mono);
	}
}
CPolinomio::~CPolinomio() {//6 este  metodo no haria falta
	cout << "El objeto fue destruido" << endl;
}
//-------------------------GRADO-------------------------
int CPolinomio::Grado() const {
	if (m_monomios.size() != 0)
		return m_monomios[0].GetExp();
	else
		return 0;
}
//------------------SOBRECARGAR OPERADORES------------------
CPolinomio& CPolinomio::operator<<(const CMonomio& mono) {
	int i = 0;
	if (mono.GetCoef() != 0) {
		if (m_monomios.empty())
			m_monomios = vector<CMonomio>(1, mono);
		else {
			do {
				if (m_monomios[i].GetExp() == mono.GetExp()) {//Ya hay uno con el mismo exponente
					m_monomios[i].SetCoef(mono.GetCoef() + m_monomios[i].GetCoef());
					if (m_monomios[i].GetCoef() == 0) {//si al sumarlos se hacen 0
						m_monomios.erase(m_monomios.begin() + i);							//		Borramos el termino de la lista
					}
							return *this;
					
				}
				else if (m_monomios[i].GetExp() < mono.GetExp()) {//Es mayor nuestro monomio que el que esta en el auxiliar

						m_monomios.insert(m_monomios.begin() + i, mono);				

					return *this;
				}
				++i;
			} while (i < m_monomios.size());
			//Es menor que los polinomios que hay en el polinomio
			m_monomios.push_back(mono);
		}
	}
	return *this;
}
bool CPolinomio::operator<(const CPolinomio& polinomio) {			//	SOBRECARGA MENOR	<
	if (Grado() < polinomio.Grado()) {
		return true;
	}
	return false;
}
bool CPolinomio::operator>(const CPolinomio& polinomio) {			// SOBRECARGA MAYOR		>
	if (Grado() > polinomio.Grado()) {
		return true;
	}
	return false;
}
bool CPolinomio::operator==(const CPolinomio& polinomio) {			// SOBRECARGA IGUAL		==
	if (Grado() == polinomio.Grado()) {
		return  true;
	}
	return false;
}
CPolinomio CPolinomio::operator-() {									// SOBRECARGA NEGAR		-
	CPolinomio aux;
	for (int i = 0; i < m_monomios.size(); i++)
		aux << -(m_monomios[i]);
	return aux;
}
CPolinomio& CPolinomio::operator+=(const CPolinomio& polinomio) {	// SOBRECARGA de		+=
	for (int i = 0; i < polinomio.m_monomios.size(); i++)
		*this << polinomio.m_monomios[i];
	return *this;
}
CPolinomio& CPolinomio::operator-=(const CPolinomio& polinomio) {	// SOBRECARGA de		-=
	for (int i = 0; i < polinomio.m_monomios.size(); i++)
		*this << -(polinomio.m_monomios[i]);
	return *this;
}
CPolinomio CPolinomio::operator+(const CPolinomio& polinomio) {	// SOBRECARGA SUMAR			+
	CPolinomio aux;
	for (int i = 0; i < polinomio.m_monomios.size(); i++)
		aux << polinomio.m_monomios[i];
	for (int i = 0; i < m_monomios.size(); i++)
		aux << m_monomios[i];
	return aux;
}
CPolinomio CPolinomio::operator-(const CPolinomio& polinomio) {	// SOBRECARGA SUMAR			-
	CPolinomio aux;
	for (int i = 0; i < m_monomios.size(); i++)
		aux << m_monomios[i];
	for (int i = 0; i < polinomio.m_monomios.size(); i++)
		aux << -(polinomio.m_monomios[i]);
	return aux;
}
double CPolinomio::operator[](int i) {							// Braquets					[]
	for (int j = 0; j < m_monomios.size(); j++) {
		if (i == m_monomios[j].GetExp())
			return m_monomios[j].GetCoef();
	}
	return 0;
}
double CPolinomio::operator()(double x) {						// Parentesis				()
	double resultado = 0;
	for (int i = 0; i < m_monomios.size(); i++)
		resultado += m_monomios[i].GetCoef() * pow(x, m_monomios[i].GetExp());
	return resultado;
}
CPolinomio CPolinomio::operator*(const CPolinomio& polinomio) {	// SOBRECARGA SUMAR			-
	CPolinomio aux;
	CMonomio monomioAux;
	for (int i = 0; i < m_monomios.size(); i++) {
		for (int j = 0; j < polinomio.m_monomios.size(); j++) {
			monomioAux.SetCoef(m_monomios[i].GetCoef() * polinomio.m_monomios[j].GetCoef());
			monomioAux.SetExp(m_monomios[i].GetExp() + polinomio.m_monomios[j].GetExp());
			aux << monomioAux;
		}
	}
	return aux;
}
CPolinomio& CPolinomio::operator*=(const CPolinomio& poli) { 	//						*=
	*this = *this * poli;
	return *this;
}
//--------------------MOSTRAR--------------------
void CPolinomio::MostrarPoli(ostream& os) const {
	int pos = 0;

	if (m_monomios.size())
	{
		do
		{
			os << m_monomios[pos++] << ' ';
		} while (pos < m_monomios.size());
	}
	else
		os << "0";
}
ostream& operator<<(ostream& os, const CPolinomio& Poli) {	// PARA MOSTRAR POR PANTALLA / ENVIAR FLUJO
	Poli.MostrarPoli(os);
	os << showpos;
	return os;
}