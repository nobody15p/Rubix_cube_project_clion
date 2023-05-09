//
// Created by Pranav on 08-05-2023.
//
//    Another way to represent the Rubik’s Cube would be a single array of 54 characters.
//    Each position holds the color of the particular cubic side.
//    Since there are 6 sides and each side has 9 stickers/colors, the size of the array is going to be 6 * 9 = 54.
//    cube[ i ] → color of the i-th cubic side, when indexed sequentially

#include "GenericRubiksCube.h++"

class RubiksCube1dArray : public GenericRubiksCube {
private:
    /*
     * Given a face index, row and col, return it's flattened index
     */
    static inline int getIndex(int ind, int row, int col) {
        return (ind * 9) + (row * 3) + col;
        // example, consider top i.e. index=0 then,
        // small cube on leftmost top is 0th as its row value is 0 and column value is 0
        // then we move like 1,2 then next row 3,4,5 next row 6,7,8
        // after this move to next face thus, 9,10,11...so on
        // 0,1,....,53
        // thus we marked all the small cubes with an index and its value is color on it.

    }

    // rotateFace function takes index of face as input
    // and gives rotated cube array
    // first copy it to temporary array
    // then applies rotation

    void rotateFace(int ind) {
        char temp_arr[9] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_arr[i * 3 + j] = cube[getIndex(ind, i, j)];
                // temp_arr stores value = color info for given index
                // this array stores 9 entries for a particular face
            }
        }

        /*
         * Another approach
         * first, the first row is replaced by the last column,
         * then the last row is replaced by the first column,
         * then the last column is replaced by the last row in reverse order,
         * and finally, the first column is replaced by the last row in reverse order.
         *
         * This can be understood by rotating a face say UP and observing its effect on other faces
         */

        for (int i = 0; i < 3; i++) cube[getIndex(ind, 0, i)] = temp_arr[getIndex(0, 2 - i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, i, 2)] = temp_arr[getIndex(0, 0, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2, 2 - i)] = temp_arr[getIndex(0, i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2 - i, 0)] = temp_arr[getIndex(0, 2, 2 - i)];
    }

public:
    char cube[54]{};

    // stores color information
    RubiksCube1dArray() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i * 9 + j * 3 + k] = getColorLetter(COLOR(i));
                    // get color of given cube
                }
            }
        }
    }

    // getColor function returns COLOR datatype, it takes face, row, col as input
    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[getIndex((int) face, (int) row, (int) col)];
        switch (color) {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
            default:
                return COLOR::WHITE;
        }
    }

    // following function checks cube is solved or not
    // if all faces have same correct color then it returns true
    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (this->cube[getIndex(i, j, k)] == getColorLetter(COLOR(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

    // this code override previous u function
    // u is up face rotation clockwise
    GenericRubiksCube &u() override {
        this->rotateFace(0);
        // up has index 0 as per our convention
        char temp_arr[3] = {};
        //    Up → 0 (White) Left → 1 (Green) Front → 2 (Red) Right → 3 (Blue) Back → 4 (Orange) Down → 5 (Yellow)

        // COPY color from back side to right side in reverse order, we are storing this in temp array
        // in last loop we are equating it to 3 i.e. right


        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(4, 0, 2 - i)];

        // COPY color from LEFT side to BACK side in reverse order
        for (int i = 0; i < 3; i++) cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
        // COPY color from FRONT side to LEFT side in reverse order
        for (int i = 0; i < 3; i++) cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
        // COPY color from RIGHT side to FRONT side in reverse order
        for (int i = 0; i < 3; i++) cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
        // COPY color from BACK side to RIGHT side in reverse order
        for (int i = 0; i < 3; i++) cube[getIndex(3, 0, 2 - i)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }

    GenericRubiksCube &u2() override {
        this->u();
        this->u();

        return *this;
    }

    GenericRubiksCube &l() override {
        this->rotateFace(1);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, i, 0)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }

    GenericRubiksCube &l2() override {
        this->l();
        this->l();

        return *this;
    }

    GenericRubiksCube &f() override {
        this->rotateFace(2);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, i, 0)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();

        return *this;
    }

    GenericRubiksCube &f2() override {
        this->f();
        this->f();

        return *this;
    }

    GenericRubiksCube &r() override {
        this->rotateFace(3);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, i, 0)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    }

    GenericRubiksCube &r2() override {
        this->r();
        this->r();

        return *this;
    }

    GenericRubiksCube &b() override {
        this->rotateFace(4);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, i, 0)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    }

    GenericRubiksCube &b2() override {
        this->b();
        this->b();

        return *this;
    }

    GenericRubiksCube &d() override {
        this->rotateFace(5);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(2, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 2, i)] = temp_arr[i];

        return *this;
    }

    GenericRubiksCube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    }

    GenericRubiksCube &d2() override {
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const RubiksCube1dArray &r1) const {
        for (int i = 0; i < 54; i++) {
            if (cube[i] != r1.cube[i]) return false;
        }
        return true;
    }

    RubiksCube1dArray &operator=(const RubiksCube1dArray &r1) {
        for (int i = 0; i < 54; i++) {
            cube[i] = r1.cube[i];
        }
        return *this;
    }

};

// this struct is used to implement a hash function for objects of type RubiksCube1dArray.
struct Hash1d {
    // This line defines the hash function operator.
    // It takes a const reference to a RubiksCube1dArray object named r1
    // as its argument and returns a size_t hash code.
    size_t operator()(const RubiksCube1dArray &r1) const {
        string str = "";
        for (int i = 0; i < 54; i++) str += r1.cube[i];
        return hash<string>()(str);
        // This line applies the std::hash<std::string> function to the string str to generate a hash code.
        // The () operator is used to invoke the hash function on the string, which returns a size_t hash code.
    }
};

/*
 *
 * The line of code return hash<string>()(str); is a call to a hash function template in C++ called std::hash.
 * The std::hash function is a way to generate a unique numeric code,
 * known as a hash code, that represents an object of any type.
 * This hash code can be used for various purposes, such as indexing objects in a hash table or comparing objects for equality.

 In the line of code hash<string>(), the std::hash function template is specialized for the string type,
 meaning that it is designed to generate a hash code for a string object.
 The empty parentheses () after hash<string> create an instance of the hash function that can be called with an argument.
 In this case, the argument is the string str.

 So, hash<string>()(str) means that we are calling the hash function that was specialized for string and passing the string str as an argument.
 This will generate a unique hash code for the string, which we then return from the operator() function.
*/