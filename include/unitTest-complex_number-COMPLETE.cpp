#include "catch.hpp" // simple unit-testing framework
#include "complex_number-COMPLETE.hpp" // the functions we want to test

#include <string>
#include <sstream>

using std::string;

TEST_CASE("getReal", "[getRealPart]") {
  complex_number b;
  complex_number c(5.2, 12.6);
  CHECK(b.getRealPart() == 0);
  CHECK(c.getRealPart() == 5.2);
}


TEST_CASE("setReal", "[setRealPart]") {
  complex_number c(5.2, 12.6);
  CHECK(c.getRealPart() == 5.2);
  CHECK(c.getImaginaryPart() == 12.6);
  c.setRealPart(33.1);
  CHECK(c.getRealPart() == 33.1);
  CHECK(c.getImaginaryPart() == 12.6);
  c.setRealPart(0);
  CHECK(c.getRealPart() == 0);
  CHECK(c.getImaginaryPart() == 12.6);
}

TEST_CASE("setImaginary", "[setImaginaryPart]") {
  complex_number c(5.2, 12.6);
  CHECK(c.getRealPart() == 5.2);
  CHECK(c.getImaginaryPart() == 12.6);
  c.setImaginaryPart(33.1);
  CHECK(c.getRealPart() == 5.2);
  CHECK(c.getImaginaryPart() == 33.1);
  c.setImaginaryPart(0);
  CHECK(c.getRealPart() == 5.2);
  CHECK(c.getImaginaryPart() == 0);
}

TEST_CASE("getImaginary", "[getImaginaryPart]") {
  complex_number b;
  complex_number c(5.2, 12.6);
  CHECK(b.getImaginaryPart() == 0);
  CHECK(c.getImaginaryPart() == 12.6);
}

TEST_CASE("toString", "[toString]") {
  complex_number b;
  complex_number c(5.2, 12.6);
  complex_number d(5.23495, 12.62271);
  CHECK(b.toString() == "0 + 0i");
  CHECK(c.toString() == "5.2 + 12.6i");
  CHECK(d.toString() == "5.23 + 12.6i"); // check precision=3
}

TEST_CASE("overloaded + operator", "[operator+]") {
  complex_number b(6,1);
  complex_number c(3,2);
  complex_number sum = b + c;
  CHECK(sum.toString() == "9 + 3i");
  CHECK((c+b).toString() == "9 + 3i");
  sum = sum + c;
  CHECK(sum.toString() == "12 + 5i");

  complex_number sum2 = complex_number(3.2, 4) + complex_number(2.9, 10.5);
  CHECK(sum2.toString() == "6.1 + 14.5i"); 
}

TEST_CASE("overloaded * operator", "[operator*]") {
  complex_number b(6,1);
  complex_number c(3,2);
  complex_number product = b * c;
  CHECK(product.toString() == "16 + 15i");
  CHECK((c*b).toString() == "16 + 15i");

  complex_number product2 = product * c;
  CHECK(product2.getRealPart() == 18);
  CHECK(product2.getImaginaryPart() == 77);
  CHECK(product2.toString() == "18 + 77i");

  product = product * c;
  CHECK(product.getRealPart() == 18);
  CHECK(product.getImaginaryPart() == 77);
  CHECK(product.toString() == "18 + 77i");

  complex_number product3 = complex_number(3.2, 4) * complex_number(2.9, 10.5);
  CHECK(product3.toString() == "-32.7 + 45.2i"); //check precision=3

}

TEST_CASE("output stream operator <<", "[operator<<]") {
  complex_number b;
  complex_number c(5.2, 12.6);
  complex_number d(5.23495, 12.62271);
  std::stringstream ss;

  ss << b << ", " << c << ", " << d << "\n";
  CHECK(ss.str() == "0 + 0i, 5.2 + 12.6i, 5.23 + 12.6i\n");

  ss << complex_number(9.0, 3.2) << "\n";
  CHECK(ss.str() == "0 + 0i, 5.2 + 12.6i, 5.23 + 12.6i\n9 + 3.2i\n");
}
