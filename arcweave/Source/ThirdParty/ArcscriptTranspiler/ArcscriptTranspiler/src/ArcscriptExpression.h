#include <iostream>
#include <any>
#include <string>
#include <cstring>

namespace Arcweave {

class Expression {
private:
  struct NumberValues {
    double value1;
    double value2;
    bool hasDoubles = false;
  };

  static NumberValues doubleValues(std::any value1, std::any value2) ;

  static std::string valueToString(std::any value);
  static bool valueToBool(std::any value);
public:
  std::any value;
  Expression() {
    value = std::any();
  }
  Expression(std::string _value) {
    value = _value;
  }
  Expression(bool _value) {
    value = _value;
  }
  Expression(int _value) {
    value = _value;
  }
  Expression(double _value) {
    value = _value;
  }
  Expression(const Expression &e) {
    value = e.value;
  }

  void setValue(std::any _value) {
    value = _value;
  }

  const std::type_info& type() {
    return value.type();
  }

  Expression operator+ (const Expression &other);
  Expression operator- (const Expression &other);
  Expression operator* (const Expression &other);
  Expression operator* (const int other);
  Expression operator/ (const Expression &other);
  Expression operator+= (const Expression &other);
  Expression operator-= (const Expression &other);
  Expression operator*= (const Expression &other);
  Expression operator/= (const Expression &other);

  bool operator== (const Expression &other);
  bool operator== (double other);
  bool operator== (int other);
  bool operator== (std::string other);
  bool operator== (bool other);
  bool operator!= (const Expression &other);
  bool operator!= (double other);
  bool operator!= (int other);
  bool operator!= (std::string other);
  bool operator!= (const char other[]);
  bool operator> (const Expression &other);
  bool operator> (int other);
  bool operator> (double other);
  bool operator>= (const Expression &other);
  bool operator< (const Expression &other);
  bool operator<= (const Expression &other);
  bool operator! ();
  bool operator&& (const Expression &other);
  bool operator|| (const Expression &other);
};

}
std::ostream& operator<< (std::ostream& out, const Arcweave::Expression &e);