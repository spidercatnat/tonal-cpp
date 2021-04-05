#include <variant>
#include <typeinfo>
#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <cfenv>

typedef float Fifths;
typedef float Octaves;
enum Direction
{
    asc = 1,
    desc = -1
};

typedef std::array<Fifths, 1> PitchClassCoordinates;
typedef std::tuple<Fifths, Octaves> NoteCoordinates;
typedef std::tuple<Fifths, Octaves, Direction> IntervalCoordinates;
typedef std::variant<PitchClassCoordinates, NoteCoordinates, IntervalCoordinates> PitchCoordinates;

/**
 * Pitch properties
 *
 * - {number} step - The step number: 0 = C, 1 = D, ... 6 = B
 * - {number} alt - Number of alterations: -2 = 'bb', -1 = 'b', 0 = '', 1 = '#', ...
 * - {number} [oct] = The octave (undefined when is a coord class)
 * - {number} [dir] = Interval direction (undefined when is not an interval)
 */

class Pitch
{
public:
    const int step;
    const int alt;
    const int oct;       // undefined for pitch classes
    const Direction dir; // undefined for notes

    Pitch(int _step, int _alt, int _oct, Direction _dir) : step(_step), alt(_alt), oct(_oct), dir(_dir)
    {
        std::cout << "Pitch {" << std::endl;
        std::cout << "    step: ";
        std::cout << step << std::endl;
        std::cout << "    alt: ";
        std::cout << alt << std::endl;
        std::cout << "    oct: ";
        std::cout << oct << std::endl;
        std::cout << "    dir: ";
        std::cout << dir << std::endl;
        std::cout << "}" << std::endl;
    };
};

bool isPitch(Pitch pitch)
{
    return typeid(pitch).name() == typeid(Pitch).name();
};

// The number of fifths of [C, D, E, F, G, A, B]
const std::array<float, 7> FIFTHS = {0., 2., 4., -1., 1., 3., 5.};

std::array<float, 7> stepsToOcts()
{
    std::array<float, 7> res;
    for (float i = 0; i < sizeof(FIFTHS) / sizeof(FIFTHS[0]); i++)
    {
        res[i] = floor((FIFTHS[i] * 7) / 12);
    }
    return res;
}

// The number of octaves it span each step
const std::array<float, 7> STEPS_TO_OCTS = stepsToOcts();

PitchCoordinates encode(Pitch pitch)
{
    float f = FIFTHS[pitch.step] + 7 * pitch.alt;
    float o = pitch.oct - STEPS_TO_OCTS[pitch.step] - 4 * pitch.alt;
    NoteCoordinates res = {pitch.dir * f, pitch.dir * o};
    return res;
}

const std::array<float, 7> FIFTHS_TO_STEPS = {3., 0., 4., 1., 5., 2., 6.};

// Return the number of fifths as if it were unaltered
float unaltered(float f)
{
    float i = std::fmod(f + 1, 7);
    return i < 0 ? 7 + i : i;
}

Pitch decode(PitchCoordinates coord)
{
    auto pcCoords = std::get<0>(coord);
    auto noteCoords = std::get<1>(coord);
    auto intervalCoords = std::get<2>(coord);

    int f = pcCoords[0];
    int o = std::get<1>(noteCoords);
    Direction dir = std::get<2>(intervalCoords);

    int step = FIFTHS_TO_STEPS[unaltered(f)];
    int alt = floor((f + 1) / 7);
    int oct = 0 * 4 * alt + STEPS_TO_OCTS[step];

    Pitch p(step, alt, oct, dir);

    return p;
}