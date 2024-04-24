#include <iostream>
#include "Program.h"
#include <vector>
#include <cmath>
#include <complex>

/*std::vector<std::complex<double>> DFT(const std::vector<std::complex<double>>& signal) {
    std::vector<std::complex<double>> spectrum(signal.size());
    const std::complex<double> I(0, 1);

    for (int k = 0; k < signal.size(); ++k) {
        std::complex<double> sum = 0.0;

        for (int n = 0; n < signal.size(); ++n) {
            double angle = -2 * M_PI * k * n / signal.size();
            sum += signal[n] * std::exp(I * angle);
        }

        spectrum[k] = sum;
    }

    return spectrum;
}

std::vector<double> calculateAmplitudeSpectrum(const std::vector<std::complex<double>>& spectrum) {
    std::vector<double> amplitude(spectrum.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        amplitude[i] = std::abs(spectrum[i]);
    }
    return amplitude;
}*/

/*std::vector<double> toDecibel(const std::vector<double>& amplitude) {
    std::vector<double> decibel(amplitude.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        std::cout << amplitude[i] << "\n";
        decibel[i] = 10 * log10(std::fabs(amplitude[i]));
    }
    for (size_t i = 0; i < amplitude.size(); ++i) {
        decibel[i] *= -1;
    }
    return decibel;
}*/

std::vector<double> toDecibel(const std::vector<double>& amplitude) {
    std::vector<double> decibel(amplitude.size());
    for (size_t i = 0; i < amplitude.size(); ++i) {
        decibel[i] = amplitude[i] * std::pow(10.0f,10 * 0.05f);
        //std::cout << decibel[i] << "\n";
    }
    return decibel;
}

int main(int argv, char* argc[]){

    // Faza pocz¹tkowa dla g³ównej funkcji cosinus (phi) to start pêtli
    // Czas trwania to ró¿nica pomiêdzy startem a warunkiem przerwania pêtli
    // Czêstotliwoœæ próbkowania oznacza ile razy i musi zostaæ zwiêkszone aby z np 2 zmieni³o siê na 3
    // Iloœæ próbek to czas trwania razy czêstotliwoœæ

    const double pi = 3.14;
    double start = 0;
    double stop = 100;

    Program program;

    std::vector<double> signal;


    double uFun = 0;

    double mt = 0;

    for (double i = start; i < stop; i += 0.01)
    {
        //////////////////////////////////AMPLITUDA
        //mt = sin(2 * pi * 100 * i);
        //signal.push_back(
        //    (0.1 * mt + 1) * cos(2*pi*200 * pi)
        //);
        //mt = sin(2 * pi * 200 * i);
        //signal.push_back(
        //    (0.5 * mt +1) * cos(2*pi*1000 * pi)
        //);
        //mt = sin(2 * pi * 200 * i);
        //signal.push_back(
        //    (0.5 * mt +1) * cos(2*pi*1000 * pi)
        //);
        //////////////////////////////////K¥TOWA
        // 
        //mt = sin(2 * pi * 200 * i);
        //signal.push_back(
        //   cos(2*pi*100 * i * 0.5 * mt)
        //); // Modyfikacja fazy
        // 
        //////////////////////////////////CZÊSTOTLIWOŒÆ
        mt = sin(2 * pi * 4000 * i);
        signal.push_back(
           cos(2*pi*150 * i * (0.5/1000) * mt)
        ); // Modyfikacja czêstotliwoœci
    }

    double fs = (15 * stop) / 2;

    //std::vector<std::complex<double>> spectrum = DFT(signal);
    //std::vector<double> amplitude = calculateAmplitudeSpectrum(spectrum);

    //std::vector<double> decibel = toDecibel(signal);

    std::vector<double> decibel = toDecibel(signal);
    

    program.CreateFunction(start, fs, 1400, 900, signal);

    return 0;
}