#include <iostream>
#include <string>
#include <stdexcept> // For std::invalid_argument

using namespace std;

class Temperature {
public:
    Temperature() : m_temp_k(0.0) {}

    Temperature(const string& temp) {
        // Find the position of the underscore
        auto pos = temp.find('_');
        if (pos == string::npos || pos == 0) {
            throw invalid_argument("INVALID Temperature Format");
        }

        // Extract the numeric part and the unit
        string temp_val = temp.substr(0, pos);
        string unit = temp.substr(pos + 1);

        try {
            float value = stof(temp_val); // Convert the numerical part to float

            if (unit == "deg") { // Celsius to Kelvin
                m_temp_k = value + 273.15;
            } else if (unit == "f") { // Fahrenheit to Kelvin
                m_temp_k = (value - 32) * 5.0 / 9.0 + 273.15;
            } else if (unit == "K") { // Kelvin
                m_temp_k = value;
            } else {
                throw invalid_argument("INVALID Temperature Unit");
            }
        } catch (const std::exception& e) {
            throw invalid_argument("Error parsing temperature: " + string(e.what()));
        }
    }

    // Copy constructor
    Temperature(const Temperature& other) = default;
    // Copy assignment operator
    Temperature& operator=(const Temperature& other) = default;

    // Move constructor
    Temperature(Temperature&& other) noexcept = default;
    // Move assignment operator
    Temperature& operator=(Temperature&& other) noexcept = default;

    // Utility function to display temperature in Kelvin
    float to_kelvin()
    {
        return m_temp_k;
    }
    float to_celsius()
    {
        return m_temp_k - 273.15;
    }
    float to_fahrenheit()
    {
        return (m_temp_k - 273.15) * 9.0 / 5.0 + 32;
    }

    std::string displayInKelvin()
    {
        return std::to_string(m_temp_k) + "_K";
    }
    //Operations
    friend Temperature operator+(Temperature first, Temperature second)
    {
        
        Temperature T(std::to_string(first.m_temp_k + second.m_temp_k)+"_K");
        return T;
    }
    friend Temperature operator-(Temperature first, Temperature second)
    {
        
        Temperature T(std::to_string(first.m_temp_k - second.m_temp_k)+"_K");
        return T;
    }

    friend ostream& operator<<(std::ostream& os, Temperature temp)
    {
        os << temp.displayInKelvin() << "\n";
        return os;
    }
private:
    float m_temp_k;
};

int main() {
    try {
        Temperature t1("36.5_deg");
        cout << "TEMP = " << t1 << "\n";

        Temperature t2("97.7_f");
        t2.displayInKelvin();

        Temperature t3("309.65_K");
        t3.displayInKelvin();
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
