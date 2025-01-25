#include <Arduino.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;


vector<String> cars = {"Volvo", "BMW", "Ford", "Mazda"};
std::map<String, int> people = { {"John", 32}, {"Adele", 45}, {"Bo", 29} };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  for(String car : cars){
    Serial.println(car);
  }
  Serial.println();
  for(auto person : people){
    Serial.printf("%s, %d\n",person.first, person.second);
    // std::cout << person.first << " " << person.second;
  }
  Serial.println();

  Serial.printf("count(igor): %d\n\n",people.count("igor"));

  people["igor"] = 27;
  people.insert({"igor", 3});

  try{
    people.insert({"igor", 6});
  }
  catch(const std::exception& e){
    Serial.println(e.what());
  }



  for(auto person : people){
    Serial.printf("%s, %d\n",person.first, person.second);
    // std::cout << person.first << " " << person.second;
  }
  Serial.printf("count(igor): %d\n\n",people.count("igor"));

  try {
    int age = 15;
    if (age >= 18) {
      Serial.println("Access granted - you are old enough.");
    } else {
      throw ("Access denied - You must be at least 18 years old.\nAge is: " + String(age));
    }
  }
  catch (String error) {
    // Serial.printf("Access denied - You must be at least 18 years old.\nAge is: %d\n",myNum); 
    Serial.println(error);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}

