#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

struct Dot {
  double x, y;
  Dot(double t_x, double t_y)
  : x(t_x), y(t_y)
  {
  }
};

double EstimateFunction(double p, double q) {
  if (q >= 100) {
    return (p + q) / (2 * q);
  }
  if (q > 0 && q < 100 && p < 20) {
    return p - 2 * q;
  }
  return p - 3 * q;
}

double Trigonometric(double x, double y) {
  double numerator = cos(x) - 3 * 1 / tan(y);
  double denumerator = exp(-1 * x * y) + pow((pow(x, 2) - log10(y / x)), 1 / 6.0);
  return numerator / denumerator;
}

bool Sign(double value) {
  return value < 0 ? false : true;
}

bool AreDotsInLine(Dot first, Dot second) {
    double left = first.x / (second.x - first.x);
    double right = first.y / (second.y - first.y);
    return left == right;
  }

double FindLineLength(Dot first, Dot second) {
  return sqrt(pow((second.x - first.x), 2) + pow((second.y - first.y), 2));
}

double FindTrianglePerimeter(Dot first, Dot second, Dot third) {
  double f_line = FindLineLength(first, second);
  double s_line = FindLineLength(second, third);
  double t_line = FindLineLength(first, third);
  return f_line + s_line + t_line;
}

bool AreDotsInFourth(Dot first, Dot second) {
    return (Sign(first.x) == Sign(second.x) && Sign(first.y) == Sign(second.y));
  }

bool AreDotsInPlane(Dot first, Dot second) {
  return Sign(first.x) == Sign(second.x) || Sign(first.y) == Sign(second.y);
}

int DestroyingWoods(double init_vol, double perc, double plan_vol) {
  if (init_vol * perc >= plan_vol) {
    throw invalid_argument("Given perc is too big or given plan volume is too small");
  }
  int result = 1;
  for (double deforestation = init_vol; deforestation > 0;
      deforestation = deforestation + init_vol * perc - plan_vol) {
        result++;
  }
  return result;
}

double Factorial(double n) {
  if (n <= 0) {
    throw invalid_argument("Given value is invalid");
  }
  if (n == 2) {
    return 2;
  }
  return n * Factorial(n - 1);
}

double FindHyperbolicSine(double x) {
  double prev = x;
  double next = prev + pow(prev, 3) / Factorial(3);
  double degree = 3;
  double precision = 0.00001;
  for (prev = next, next = prev + pow(x, degree + 2) / Factorial(degree + 2); prev - next > precision;);
  return next;
}

double FindExponential(double x) {
  if (x < 0.1 || x > 1) {
    throw invalid_argument("Given value is invalid");
  }
  double prev = 1, next = prev + cos(M_PI / 4) * x;
  double degree = 1, precision = 0.0001;
  for (prev = next, ++degree, next = prev + pow(cos(M_PI / 4), degree) * pow(x, degree) / Factorial(degree); prev - next > precision;);
  return next;
}

double FindSum(int n) {
  double result = 0.0;
  for(int k = 1; k <= n; k++) {
    for (int i = 1; i <= k; i++) {
      result += 1 / (pow(k, 2) + i);
    }
  }
  return result;
}

int main() {
  while (true) {
    cout << "Выберите задание:" << endl;
    cout << "1 - Вычислить значение функции f(p,q) при заданных p и q" << endl;
    cout << "2 - Вычислить значение функции S(x,y) при заданных x и y" << endl;
    cout << "3 - Вычислить периметр треугольника с заданными вершинами" << endl;
    cout << "4 - Вычислить темп вырубки леса" << endl;
    cout << "5 - Определить значение гиперболического синуса вычислительным методом" << endl;
    cout << "6 - Определить значение экспоненциальной функции вычислительным методом" << endl;
    cout << "7 - Вычислить сумму" << endl;
    cout << "Нажмите любую другую кнопку, чтобы выйти из программы" << endl;
    int choise = 0;
    cin >> choise;
    switch (choise) {
      case 1: {
        cout << "Введите значения p и q: ";
        double p, q;
        cin >> p >> q;
        cout << "Значение функции: f(" << p << ", " << q << ") = " << EstimateFunction(p, q) << endl;
        break;
      }
      case 2: {
        cout << "Введите значения x и y: ";
        double x, y;
        cin >> x >> y;
        cout << "Значение функции: S(" << x << ", " << y << ") = " << Trigonometric(x, y) << endl;
        break;
      }
      case 3: {
        double x1, y1;
        cout << "Введите координаты первой точки: ";
        cin >> x1 >> y1;
        Dot first(x1, y1);
        double x2, y2;
        cout << "Введите координаты второй точки: ";
        cin >> x2 >> y2;
        Dot second(x2, y2);
        Dot origin(0, 0);
        if (AreDotsInFourth(first, second)) {
          cout << "Данные точки расположены в одной четверти" << endl;
          if (AreDotsInLine(first, second)) {
            cout << "Данные точки расположены на одной прямой вместе с началом координат" << endl;
          } else {
            cout << "Периметр треугольнка равен " << FindTrianglePerimeter(first, second, origin) << endl;
          }
        } else {
          cout << "Данные точки не расположены в одной четверти" << endl;
          if (AreDotsInPlane(first, second)) {
            cout << "Данные точки расположены в одной полуплоскости" << endl;
          } else {
            cout << "Данные точки не расположены в одной полуплоскости" << endl;
          }
        }
        break;
      }
      case 4: {
        cout << "Введите значения:" << endl;
        cout << "первоначального объема древесины;" << endl;
        cout << "ежегодного прироста;" << endl;
        cout << "годового плана заготовки" << endl;
        double p, k, t;
        cin >> p >> k >> t;
        try {
          int years = DestroyingWoods(p, k, t);
          cout << "Данный участок леса будет вырублен за " << years << " лет" << endl;
        } catch (invalid_argument) {
          cout << "Даны неверные данные!" << endl;
        }
        break;
      }
      case 5: {
        cout << "Введите x: ";
        double x;
        cin >> x;
        cout << "Значение sh(x) вычислительным методом: " << FindHyperbolicSine(x) << endl;
        cout << "Значение sh(x) стандартным методом: " << sinh(x) << endl;
        break;
      }
      case 6: {
        cout << "Введите x (0.1 <= x <= 1): ";
        double x;
        cin >> x;
        cout << "Значение exp(x) вычислительным методом: " << FindExponential(x) << endl;
        cout << "Значение exp(x) стандартным методом: " << exp(x * cos(M_PI / 4)) << endl;
        break;
      }
      case 7: {
        cout << "Введите натуральное N: ";
        int n;
        cin >> n;
        cout << "Значение суммы: " << FindSum(n) << endl;
        break;
      }
      default:
        exit(1);
    }
  }
}