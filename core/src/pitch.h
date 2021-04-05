#include <variant>
#include <typeinfo>
#include <iostream>
#include <array>

typedef int Fifths;
typedef int Octaves;
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

    Pitch(int _step, int _alt, int _oct, Direction _dir) : step(_step), alt(_alt), oct(_oct), dir(_dir) {
        std::cout << "Created a pitch instance!" << std::endl;
    };

    void showParams() {
        std::cout << step << std::endl;
        std::cout << alt << std::endl;
        std::cout << oct << std::endl;
        std::cout << dir << std::endl;
    };

};

bool isPitch(Pitch pitch)
{
    return typeid(pitch).name() == typeid(Pitch).name();
};