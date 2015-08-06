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
#include <random>

// Returns a pointer to an array of doubles of the size 'size'
// Displaced between 0.0 and 1.0
// size is required to be of the form '(2 ^ n) + 1'
double *normalizedMidpointDisplacement(int size, double h);

double *midpointDisplacement(int size, double h);

struct PassSettings {
    double *values;
    int valuesSize;
    int passSize;
    double randomDisplacementMultiplier; // Given by 2 ^ (- (h * pass))

    std::mt19937 *mt;
    std::uniform_real_distribution<double> *dist;
};

void midpointDisplacementPass(PassSettings *settings);

void normalizeValues(double *values, int size);
