/*
Copyright (C) 2015 Marien Raat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <midpointDisplacement.h>
#include <math.h>
#include <iostream>

double *normalizedMidpointDisplacement(int size, double h) {
    double *values = midpointDisplacement(size, h);

    normalizeValues(values, size);

    return values;
}


double *midpointDisplacement(int size, double h) {
    double *values = new double[size]; 
    for (int i = 0; i < size; i++) values[i] = 0.0;

    PassSettings passSettings;
    passSettings.values = values;
    passSettings.valuesSize = size;
    passSettings.passSize = (size - 1);
    passSettings.randomDisplacementMultiplier = 1.0;

    std::random_device randomD;
    passSettings.mt = new std::mt19937(randomD());
    passSettings.dist = new std::uniform_real_distribution<double>(-1.0, 1.0);

    while (passSettings.passSize > 1) {
        midpointDisplacementPass(&passSettings);

        passSettings.passSize /= 2;
        passSettings.randomDisplacementMultiplier *= pow(2.0, -h);
    }
    return values;
}

void midpointDisplacementPass(PassSettings *settings) {
    for (int i = settings->passSize / 2; i < settings->valuesSize; i += settings->passSize) {
        settings->values[i] = (settings->values[i - (settings->passSize / 2)]
                               + settings->values[i + (settings->passSize / 2)])
            / 2.0;
        settings->values[i] += (*(settings->dist))(*(settings->mt))
            * settings->randomDisplacementMultiplier;
    }
}

void normalizeValues(double *values, int size) {
    double min = values[0], max = values[0];
    for (int i = 0; i < size; i++) {
        if (values[i] < min) min = values[i]; 
        if (values[i] > max) max = values[i];
    }
    for (int i = 0; i < size; i++) {
        values[i] = (values[i] - min) / (max - min);
    }
}
