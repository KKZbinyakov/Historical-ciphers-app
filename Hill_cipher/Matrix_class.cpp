#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>


/**
* \file Matrix_class.cpp
*
* This file describes the matrix class required to implement the Vigener cipher.
*/

/**
* A class for working with matrices.
*
*/

class Matrix_class
{
/**
* An auxiliary recursive function that finds all unique products in a matrix, the number of multipliers in which is equal to the size of the matrix.
*
*\ param[in] First_multiplier The element of the vector that the function is currently working with.
*\ param[in] Determinant_vector A vector of terms that are unique products of a matrix, the number of multipliers of which is equal to the order of the matrix.
*\ param[in] Y The row of the matrix.
*
*\ return A vector of terms that are unique products of a matrix, the number of multipliers of which is equal to the order of the matrix.
*/
private:
    std::vector <int> Rec_function(int First_multiplier, std::vector <int> &Determinant_vector, int Y = 1)
    {
        int number;
        std::vector <int> Something;
        std::vector <int> Determinant_parts;
        for(int i{0}; i < Matrix_X; i++)
        {
            Determinant_parts.push_back(int(pow(1, Y+i))*First_multiplier*Matrix[Y][i]);
            if(Y == Matrix_Y - 1)
            {
                number = Determinant_parts[i];
                Determinant_vector.push_back(number);
            }
        }
        if(Y == Matrix_Y - 1)
        {
            return Determinant_vector;
        }
        Y += 1;
        if(Y < Matrix_Y)
        {
            for(int j{0}; j < Determinant_parts.size(); j++)
            {
                Rec_function(Determinant_parts[j], Determinant_vector, Y);
            }
            return Determinant_vector;
        }
    }
/**
* Checks the vector for the presence of identical elements, returning a check vector vector if any are found.
*
*\ param[in] Vector The vector in which the check is performed.
*\ param[in] Check_vector The vector that will be used as a reference point in the future.
*
*\ return The vector that will be used as a reference point in the future.
*\ return A vector in which there are no repetitions.
*/
    std::vector <int> Duplicates_find(std::vector <int> Vector, std::vector <int> Check_vector)
    {
        std::set<int> Numbers;
        int Vector_size = Vector.size();
        for(int i{0}; i < Vector_size; i++)
        {
            if(Numbers.count(Vector[i]) == 1)
            {
                return Check_vector;
            }
            else
            {
                Numbers.insert(Vector[i]);
                continue;
            }
        }
        return Vector;
    }
/**
* A function that counts the number of inversions in a vector.
*
*\ param[in] Vector the investigated vector.
*\ return Number of inversions.
*/
    int Inversion_counter(std::vector <int> Vector)
    {
        int counter;
        std::vector <int> Numbers;
        std::vector <int> Indexes;
        for(int i{0}; i < Vector.size(); i++)
        {
            Numbers.push_back(Vector[i]);
            Indexes.push_back(i);
        }
        for(int i{0}; i < Vector.size(); i++)
        {
            for(int j{0}; j < Vector.size(); j++)
            {
                if(Numbers[i] > Vector[j] && Indexes[i] < j)
                {
                    counter += 1;
                }
            }
        }
        return counter;
    }
public:
    std::vector<std::vector<int>> Matrix; ///< Matrix.
    int Matrix_X; ///< Number of columns.
    int Matrix_Y; ///< Number of lines.
/**
* Matrix Constructor.
*
*\ param[in] p_matrix A vector of vectors that reflects the matrix.
*\ param[in] p_matrix_X Number of columns.
*\ param[in] p_matrix_Y Number of lines.
*
*/
    Matrix_class(std::vector<std::vector<int>> p_matrix = {{0}}, int p_matrix_X = 0, int p_matrix_Y = 0)
    {
        Matrix = p_matrix;
        Matrix_X = p_matrix_X;
        Matrix_Y = p_matrix_Y;
    }
/**
* dereferencing the matrix.
*/
    std::vector<int> operator[](unsigned index)
    {
        return Matrix[index];
    }
/**
* Assigning appropriate values to a class object.
*
*\ param[in] matrix The vector of vectors, the value of which the matrix will take.
*
*/
    void Get_Matrix(std::vector <std::vector<int>> matrix)
    {
        Matrix_X = matrix[0].size();
        Matrix_Y = matrix.size();
        int Matrix_size;
        Matrix = matrix;
    }
/**
* The function that is responsible for manually entering the matrix.
*/
    void Enter_Matrix()
    {
        std::vector<std::vector<int>> matrix;
        std::string stroke;
        int Matrix_size{1};
        for (int i = 0; i < Matrix_size; i++)
        {
            std::getline(std::cin, stroke, '\n');
            std::vector<int> Stroke;
            std::stringstream ss(stroke);
            int number;
            while(ss >> number)
            {
                Stroke.push_back(number);
            }
            matrix.push_back(Stroke);
            Matrix_size = matrix[0].size();
            Matrix_X = matrix[0].size();
            Matrix_Y = matrix.size();
        }
        Matrix = matrix;
    }
/**
* A function that performs a matrix transposition operation.
*
*\ return The transposed matrix.
*/
    std::vector <std::vector<int>> Transposition()
    {
        std::vector<int> Null_vector = {0};
        std::vector <std::vector<int>> T_Matrix;
        if(Matrix_Y == Matrix_X)
        {
            std::vector <std::vector<int>> T_Matrix = Matrix;
            for(int i{0}; i < Matrix_Y; i++)
            {
                for(int j{0}; j < Matrix_X; j++)
                {
                    T_Matrix[j][i] = Matrix[i][j];
                }
            }
            return T_Matrix;
        }
        else if(Matrix_Y != Matrix_X)
        {
            if(Matrix_Y < Matrix_X)
            {
                for(int i{0}; i < Matrix_X; i++)
                {
                    T_Matrix.push_back(Null_vector);
                    for(int j{0}; j < Matrix_Y-1; j++)
                    {
                        T_Matrix[i].push_back(0);
                    }
                }
                for(int i{0}; i < Matrix_X; i++)
                {
                    for(int j{0}; j < Matrix_Y; j++)
                    {
                        T_Matrix[i][j] = Matrix[j][i];
                    }
                }
                return T_Matrix;
            }
            else if(Matrix_Y > Matrix_X)
            {
                for(int i{0}; i < Matrix_X; i++)
                {
                    T_Matrix.push_back(Null_vector);
                    for(int j{0}; j < Matrix_Y-1; j++)
                    {
                        T_Matrix[i].push_back(0);
                    }
                }
                for(int i{0}; i < Matrix_Y; i++)
                {
                    for(int j{0}; j < Matrix_X; j++)
                    {
                        T_Matrix[j][i] = Matrix[i][j];
                    }
                }
                return T_Matrix;
            }
        }
    }
/**
* A function that deletes a column or row.
*
*\ param[in] Index The index of the row or column to be deleted.
*\ param[in] Action_choice A variable that is responsible for selecting a row or column.
*
*/
    void Delete(int Index, int Action_choice)
    {
        if(Action_choice == 0)
        {
            if(Index <= Matrix_X)
            {
                for(int i{0}; i < Matrix_Y; i++)
                {
                    auto iter = Matrix[i].cbegin();
                    Matrix[i].erase(iter + Index);
                }
                Matrix_X = Matrix_X - 1;
            }
        }
        else if(Action_choice == 1)
        {
            if(Index <= Matrix_Y)
            {
                auto iter = Matrix.cbegin();
                Matrix.erase(iter + Index);
                Matrix_Y = Matrix_Y - 1;
            }
        }
    }
/**
* A function that performs the composition of matrices.
*
*\ param[in] Matrix1 The first multiplier of the composition.
*\ param[in] Matrix2 The second multiplier of the composition.
*
*\ return matrix composition.
*/
    std::vector <std::vector<int>> Composition(std::vector <std::vector<int>> Matrix1, std::vector <std::vector<int>> Matrix2)
    {
        std::vector <std::vector<int>> Matrix_Composition;
        Matrix_Composition = Matrix2;
        int matrix_X = Matrix2[0].size();
        int matrix_Y = Matrix2.size();
        for(int i{0}; i < matrix_Y; i++)
        {
            for(int j{0}; j < matrix_X; j++)
            {
                Matrix_Composition[i][j] = 0;
                for(int k{0}; k < matrix_Y; k++)
                {
                    Matrix_Composition[i][j] += Matrix1[i][k]*Matrix2[k][j];
                }
            }
        }
        return Matrix_Composition;
    }
/**
* Calculating the determinant of the matrix.
*
*\ return determinant.
*/
    int Determinant()
    {
        std::vector <std::vector <int>> Index_storage;
        std::vector <int> v1;
        int determinant{0};
        std::vector <int> Determinant_parts;
        int Number_of_composition = pow(Matrix_X, Matrix_Y);
        int Position_counter = Number_of_composition / Matrix_X;
        int Position{0};
        std::vector <int> Check_vector {0};
        for(int i{0}; i < Matrix_X-1; i++)
        {
            Check_vector.push_back(0);
        }
        Index_storage.push_back(Check_vector);
        if( Matrix_X == Matrix_Y)
        {
            for(int i{1}; i < Number_of_composition; i++)
            {
                Index_storage.push_back(Index_storage[i-1]);
                int l{Matrix_X-1};
                if(Index_storage[i][l] == Matrix_X-1)
                {
                    while(Index_storage[i][l] == Matrix_X-1)
                    {
                        Index_storage[i][l] = 0;
                        l = l - 1;
                        if(Index_storage[i][l] != Matrix_X-1)
                        {
                            Index_storage[i][l] = Index_storage[i][l] + 1;
                            break;
                        }
                    }
                }
                else
                {
                    Index_storage[i][l] += 1;
                }
            }
            for(int i{0}; i < Matrix_X; i++)
            {
                Determinant_parts = Rec_function(Matrix[0][i], v1, 1);
            }
            for(int i{0}; i < Determinant_parts.size(); i++)
            {
                Index_storage[i] = Duplicates_find(Index_storage[i], Check_vector);
                if(Index_storage[i] == Check_vector)
                {
                    Determinant_parts[i] = 0;
                }
                    if(Inversion_counter(Index_storage[i]) % 2 != 0)
                    {
                        Determinant_parts[i] = Determinant_parts[i] * (-1);
                    }
                determinant += Determinant_parts[i];
            }
        }
        return determinant;
    }
/**
* Calculating the inverse matrix.
*
*\ param[in] The inverse determinant of the matrix for which the inverse matrix is calculated.
*
*\ return Inverse matrix/
*/
    std::vector <std::vector <int>> Invers_Matrix(int Key_determinant_1)
        {
        Matrix_class Union_matrix(Matrix, Matrix_X, Matrix_Y);
        for(int i{0}; i < Union_matrix.Matrix_Y; i++)
        {
            for(int j{0}; j < Union_matrix.Matrix_X; j++)
            {
                Matrix_class Auxiliary_matrix(Matrix, Matrix_X, Matrix_Y);
                Auxiliary_matrix.Delete(j, 0);
                Auxiliary_matrix.Delete(i, 1);
                Union_matrix.Matrix[i][j] = pow(-1, (i+j))*round(Auxiliary_matrix.Determinant());
            }
        }
        Union_matrix.Matrix = Union_matrix.Transposition();
        Matrix_class Key_1(Union_matrix.Matrix, Union_matrix.Matrix_X, Union_matrix.Matrix_Y);
        for(int i{0}; i < Union_matrix.Matrix_Y; i++)
        {
            for(int j{0}; j < Union_matrix.Matrix_X; j++)
            {
                Key_1.Matrix[i][j] = Key_1.Matrix[i][j] * Key_determinant_1;
            }
        }
        return Key_1.Matrix;
    }
};


