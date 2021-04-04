#include <vector>
#include <variant>
#include <any>
#include <typeinfo>
#include <iostream>

typedef int Fifths;
typedef int Octaves;
enum Direction
{
    asc = 1,
    desc = -1
};

typedef std::vector<Fifths> PitchClassCoordinates;
typedef std::vector<std::variant<Fifths, Octaves>> NoteCoordinates;
typedef std::vector<std::variant<Fifths, Octaves, Direction>> IntervalCoordinates;
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

    };

    void showParams() {
        std::cout << step;
        std::cout << alt;
        std::cout << oct;
        std::cout << dir;
    }

};

bool isPitch(Pitch pitch)
{
    return typeid(pitch).name() == typeid(Pitch).name() &&
           typeid(pitch.step).name() == "number" &&
           typeid(pitch.alt).name() == "number";
}