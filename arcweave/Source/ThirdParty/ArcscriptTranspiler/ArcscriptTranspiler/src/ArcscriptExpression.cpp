#include "ArcscriptExpression.h"

namespace Arcweave {

Expression::NumberValues Expression::doubleValues(std::any value1, std::any value2) {
  int intValue1, intValue2;
  double dblValue1, dblValue2;
  bool isDouble = false;
  if (value1.type() == typeid(int)) {
    intValue1 = std::any_cast<int>(value1); 
    dblValue1 = intValue1;
  } else if (value1.type() == typeid(double)){ // type double;
    isDouble = true;
    dblValue1 = std::any_cast<double>(value1); 
  } else if (value1.type() == typeid(bool)) {
    bool boolVal = std::any_cast<bool>(value1);
    if (boolVal) {
      dblValue1 = 1;
    } else {
      dblValue1 = 0;
    }
  }
  if (value2.type() == typeid(int)) {
    intValue2 = std::any_cast<int>(value2); 
    dblValue2 = intValue2;
  } else if (value2.type() == typeid(double)) {
    isDouble = true;
    dblValue2 = std::any_cast<double>(value2);
  } else if (value2.type() == typeid(bool)) {
    bool boolVal = std::any_cast<bool>(value1);
    if (boolVal) {
      dblValue2 = 1;
    } else {
      dblValue2 = 0;
    }
  }
  NumberValues returnVal;
  returnVal.value1 = dblValue1;
  returnVal.value2 = dblValue2;
  returnVal.hasDoubles = isDouble;
  return returnVal;
}

bool Expression::valueToBool(std::any value) {
  if (value.type() == typeid(int))  {
    return (std::any_cast<int>(value) > 0);
  }
  if (value.type() == typeid(double))  {
    return (std::any_cast<double>(value) > 0);
  }
  if (value.type() == typeid(std::string))  {
    return (std::any_cast<std::string>(value) != "");
  }
  return (std::any_cast<bool>(value));
}

Expression Expression::operator+ (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  Expression* result;
  if (!values.hasDoubles) {
    int intValue = values.value1 + values.value2;
    result  = new Expression(intValue);
  } else {
    result = new Expression(values.value1 + values.value2);
  }
  return *result;
}

Expression Expression::operator- (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  Expression* result;
  if (!values.hasDoubles) {
    int intValue = values.value1 - values.value2;
    result  = new Expression(intValue);
  } else {
    result = new Expression(values.value1 - values.value2);
  }
  return *result;
}

Expression Expression::operator* (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  Expression* result;
  if (!values.hasDoubles) {
    int intValue = values.value1 * values.value2;
    result  = new Expression(intValue);
  } else {
    result = new Expression(values.value1 * values.value2);
  }
  return *result;
}

Expression Expression::operator* (const int other) {
  NumberValues values = doubleValues(value, other);
  Expression* result;
  if (!values.hasDoubles) {
    int intValue = values.value1 * values.value2;
    result  = new Expression(intValue);
  } else {
    result = new Expression(values.value1 * values.value2);
  }
  return *result;
}

Expression Expression::operator/ (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  Expression* result;
  if (!values.hasDoubles) {
    int intValue = values.value1 / values.value2;
    result  = new Expression(intValue);
  } else {
    result = new Expression(values.value1 / values.value2);
  }
  return *result;
}

Expression Expression::operator+= (const Expression &other) {
  if (value.type() == typeid(int) || value.type() == typeid(double)) {
    NumberValues values = doubleValues(value, other.value);
    if (!values.hasDoubles) {
      int intValue = values.value1 + values.value2;
      value = intValue;
    } else {
      value = values.value1 + values.value2;
    }
  }
  if (value.type() == typeid(std::string)) {
    value = std::any_cast<std::string>(value) + std::any_cast<std::string>(other.value);
  }
  return *this;
}

Expression Expression::operator-= (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  if (!values.hasDoubles) {
    int intValue = values.value1 - values.value2;
    value = intValue;
  } else {
    value = values.value1 - values.value2;
  }
  return *this;
}

Expression Expression::operator*= (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  if (!values.hasDoubles) {
    int intValue = values.value1 * values.value2;
    value = intValue;
  } else {
    value = values.value1 * values.value2;
  }
  return *this;
}

Expression Expression::operator/= (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  if (!values.hasDoubles) {
    int intValue = values.value1 / values.value2;
    value = intValue;
  } else {
    value = values.value1 / values.value2;
  }
  return *this;
}

bool Expression::operator== (const Expression &other) {
  if (value.type() == typeid(int) || value.type() == typeid(double)) {
    NumberValues values = doubleValues(value, other.value);
    return values.value1 == values.value2;
  }
  if (value.type() == typeid(bool)) {
    return std::any_cast<bool>(value) == std::any_cast<bool>(other.value);
  }
  return std::any_cast<std::string>(value) == std::any_cast<std::string>(other.value);
}

bool Expression::operator== (double other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 == values.value2;
}

bool Expression::operator== (int other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 == values.value2;
}

bool Expression::operator== (std::string other) {
  return std::any_cast<std::string>(value) == other;
}

bool Expression::operator== (bool other) {
  return valueToBool(value) == other;
}

bool Expression::operator!= (const Expression &other) {
  if (value.type() == typeid(int) || value.type() == typeid(double)) {
    NumberValues values = doubleValues(value, other.value);
    return values.value1 != values.value2;
  }
  if (value.type() == typeid(bool)) {
    return std::any_cast<bool>(value) != std::any_cast<bool>(other.value);
  }
  return std::any_cast<std::string>(value) != std::any_cast<std::string>(other.value);
}

bool Expression::operator!= (double other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 != values.value2;
}

bool Expression::operator!= (int other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 != values.value2;
}

bool Expression::operator!= (std::string other) {
  return std::any_cast<std::string>(value) != other;
}

bool Expression::operator!= (const char other[]) {
  return strcmp(std::any_cast<std::string>(value).c_str(), other) == 0;
}

bool Expression::operator> (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  return values.value1 > values.value2;
}

bool Expression::operator> (int other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 > values.value2;
}

bool Expression::operator> (double other) {
  NumberValues values = doubleValues(value, other);
  return values.value1 > values.value2;
}

bool Expression::operator>= (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  return values.value1 >= values.value2;
}

bool Expression::operator< (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  return values.value1 < values.value2;
}

bool Expression::operator<= (const Expression &other) {
  NumberValues values = doubleValues(value, other.value);
  return values.value1 <= values.value2;
}

bool Expression::operator! () {
  return !(valueToBool(value));
}

bool Expression::operator&& (const Expression &other) {
  return valueToBool(value) && valueToBool(other.value);
}

bool Expression::operator|| (const Expression &other) {
  return valueToBool(value) || valueToBool(other.value);
}
}

std::ostream& operator<< (std::ostream& out, const Arcweave::Expression &e) {
  std::any value = e.value;
  if (value.type() == typeid(int)) {
    return out << std::any_cast<int>(value);
  }
  if (value.type() == typeid(double)) {
    return out << std::any_cast<double>(value);
  }
  if (value.type() == typeid(std::string)) {
    return out << std::any_cast<std::string>(value);
  }
  if (value.type() == typeid(bool)) {
    return out << std::any_cast<bool>(value);
  }
  return out;
}