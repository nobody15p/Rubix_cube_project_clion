//
// Created by Pranav on 04-05-2023.
//

// we will implement Rubik's Cube as a 3D array
// cube[ i ][ j ][ k ] → color of the ith side, jth row and kth col.
//
//    Up → 0 (White)
//
//    Left → 1 (Green)
//
//    Front → 2 (Red)
//
//    Right → 3 (Blue)
//    
//    Back → 4 (Orange)
//
//    Down → 5 (Yellow)

#include "GenericRubiksCube.h++"

class RubiksCube3dArray : public GenericRubiksCube {
private:
    // rotateFace function takes index of face as input
    // and gives rotated cube array
    // first copy it to temporary array
    // then applies rotation

    void rotateFace(int ind) {
        char temp_arr[3][3] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_arr[i][j] = cube[ind][i][j];
            }
        }
        // when we rotate face by clockwise 90 deg

        for (int i = 0; i < 3; i++) cube[ind][0][i] = temp_arr[2 - i][0];
        // first row will be replaced by 1st column in reverse direction

        for (int i = 0; i < 3; ++i) cube[ind][2][i] = temp_arr[2 - i][2];
        // third row will be replaced by 3rd column in reverse direction

        for (int i = 0; i < 3; ++i) cube[ind][1][i] = temp_arr[2 - i][1];
        // 2nd row will be replaced by 2nd column in reverse direction

        /*
         * Another approach
         * first, the first row is replaced by the last column,
         * then the last row is replaced by the first column,
         * then the last column is replaced by the last row in reverse order,
         * and finally, the first column is replaced by the last row in reverse order.
         */
//        for (int i = 0; i < 3; i++) cube[ind][i][2] = temp_arr[0][i];
//        for (int i = 0; i < 3; i++) cube[ind][2][2 - i] = temp_arr[i][2];
//        for (int i = 0; i < 3; i++) cube[ind][2 - i][0] = temp_arr[2][2 - i];
    }

public:
    char cube[6][3][3]{};
    // cube 3d array stores first later of cube's color

    RubiksCube3dArray() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++)
                    cube[i][j][k] = getColorLetter(COLOR(i));
            }
        }
    }

    // getColor function returns COLOR datatype, it takes face, row, col as input
    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[int(face)][row][col];
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
                    if (this->cube[i][j][k] == getColorLetter(COLOR(i))) continue;
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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[4][0][2 - i];

        // COPY color from LEFT side to BACK side in reverse order
        for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
        // COPY color from FRONT side to LEFT side in reverse order
        for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
        // COPY color from RIGHT side to FRONT side in reverse order
        for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
        // COPY color from BACK side to RIGHT side in reverse order
        for (int i = 0; i < 3; i++) cube[3][0][2 - i] = temp_arr[i];
        // DOWN side remains same
        return *this;
    }

    GenericRubiksCube &uPrime() override {
        // do clockwise rotation 3 times
        // equivalent to one anticlockwise rotation
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

    // use similar approach like u
    GenericRubiksCube &l() override {
        this->rotateFace(1);

        //    Up → 0 (White) Left → 1 (Green) Front → 2 (Red) Right → 3 (Blue) Back → 4 (Orange) Down → 5 (Yellow)
        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = temp_arr[i];

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

        //    Up → 0 (White) Left → 1 (Green) Front → 2 (Red) Right → 3 (Blue) Back → 4 (Orange) Down → 5 (Yellow)
        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp_arr[i];

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

    // this function overloads == operator
    bool operator==(const RubiksCube3dArray &r1) const {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (r1.cube[i][j][k] != cube[i][j][k]) return false;
                }
            }
        }
        return true;
    }

    // this function overloads '=' assignment operator
    RubiksCube3dArray &operator=(const RubiksCube3dArray &r1) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = r1.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

// this struct is used to implement a hash function for objects of type RubiksCube3dArray.
struct Hash3d {
    // This line defines the hash function operator.
    // It takes a const reference to a RubiksCube3dArray object named r1
    // as its argument and returns a size_t hash code.
    size_t operator()(const RubiksCube3dArray &r1) const {
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += r1.cube[i][j][k];
                }
            }
        }
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