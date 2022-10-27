#include <iostream>
#include <vector>

using namespace std;

class Rational {
public:
	Rational (long long _num = 0, long long _den = 1) {
		long long _gcd = gcd (_num, _den);
		num = _num / _gcd;
		den = _den / _gcd;
		if (den < 0) {
			den *= -1;
			num *= -1;
		}
	}

	Rational & operator= (const Rational & _r) {
		num = _r.num;
		den = _r.den;
		return *this;
	}
	friend Rational operator+ (const Rational & _r1, const Rational & _r2) {
		return Rational (_r1.num * _r2.den + _r2.num * _r1.den, _r1.den * _r2.den);
	}
	friend Rational & operator+ (Rational & _r) {
		return _r;
	}
	friend Rational operator- (const Rational & _r1, const Rational & _r2) {
		return Rational (_r1.num * _r2.den - _r2.num * _r1.den, _r1.den * _r2.den);
	}
	friend Rational operator- (const Rational & _r) {
		return Rational (-_r.num, _r.den);
	}
	friend Rational operator* (const Rational & _r1, const Rational & _r2) {
		return Rational (_r1.num * _r2.num, _r1.den * _r2.den);
	}
	friend Rational operator/ (const Rational & _r1, const Rational & _r2) {
		return Rational (_r1.num * _r2.den, _r1.den * _r2.num);
	}
	friend bool operator== (const Rational & _r1, const Rational & _r2) {
		return ((_r1.num == _r2.num) && (_r1.den == _r2.den));
	}
	friend bool operator== (const long long & _n, const Rational & _r) {
		return ((_n == _r.num) && _r.den == 1);
	}
	friend bool operator== (const Rational & _r, const long long & _n) {
		return ((_n == _r.num) && _r.den == 1);
	}

	operator double () {
		return double (num / den);
	};

	friend ostream & operator<<(ostream & os, const Rational & _r) {
		if (_r.den == 1) {
			os << _r.num;
		} else if (_r.num == 0) {
			os << 0;
		} else {
			os << _r.num << "/" << _r.den;
		}
		return os;
	}
	friend istream & operator>>(istream & is, Rational & _r) {
		is >> _r.num;
		is.get ();
		is >> _r.den;
		return is;
	}

private:
	long long gcd (long long _n1, long long _n2) {
		if (!(_n1 && _n2)) {
			return 1;
		}
		_n1 = abs (_n1);
		_n2 = abs (_n2);
		while (_n2 %= _n1) {
			swap (_n1, _n2);
		}
		return _n1;
	}
	void swap (long long & _n1, long long & _n2) {
		_n1 = _n1 + _n2;
		_n2 = _n1 - _n2;
		_n1 = _n1 - _n2;
	}

	long long num, den;
};

void print (vector<vector<Rational>> & v, int n) {
	cout << "=================\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << v[i][j] << "\t";
		}
		cout << "\n";
	}
}

int main () {
	int n, i, j, k;
	Rational temp;
	cout << "Enter the number of rows of the system matrix: ";
	cin >> n;
	vector<vector<Rational>> v (n, vector<Rational> (n + 1));
	cout << "Enter the values of the matrix elements:\n";
	cout << "ATTENTION input occurs in common fractions.\n";
	cout << "For example :\n";
	cout << "to enter an integer n, you need to enter n/1,\n";
	cout << "to enter an common fraction n/m, you need to enter n/m.\n";
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n + 1; ++j) {
			cin >> v[i][j];
		}
	}
	cout << "Your system matrix:\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << v[i][j] << "\t";
		}
		cout << "\n";
	}

	for (i = 0; i < n; ++i) {
		temp = v[i][i];
		if (temp == Rational (0)) {
			cout << "INFINITY SOLUTIONS\n";
			system ("pause");
			return 0;
		}
		for (j = 0; j < n + 1; ++j) {
			v[i][j] = v[i][j] / temp;
		}
		for (j = 0; j < n; ++j) {
			if (j == i) continue;
			temp = v[j][i];
			for (k = 0; k < n + 1; ++k) {
				v[j][k] = v[j][k] - temp * v[i][k];
			}
		}
		cout << "========= " << i + 1 << " =========\n";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				cout << v[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	system ("pause");
	return 0;
}
