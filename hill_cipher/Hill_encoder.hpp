#ifndef HILL_ENCODER_HPP
#define HILL_ENCODER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <algorithm>
#include <numeric>
#include "exceptions.hpp"

/**
 * \file Hill_encoder.hpp
 *
 * This file describes the matrix class and functions required to implement the Hill cipher.
 */

/**
 * A class for working with matrices.
 *
 */
class Matrix_class
{
public:
    std::vector<std::vector<int>> Matrix; ///< Matrix.
    unsigned long long Matrix_X;          ///< Number of columns.
    unsigned long long Matrix_Y;          ///< Number of lines.
    /**
     * Matrix Constructor.
     *
     * \param[in] p_matrix   A vector of vectors that reflects the matrix.
     * \param[in] p_matrix_X Number of columns.
     * \param[in] p_matrix_Y Number of lines.
     *
     */
    Matrix_class(std::vector<std::vector<int>> p_matrix = {{0}}, unsigned long long p_matrix_X = 0, unsigned long long p_matrix_Y = 0)
    {
        Matrix = p_matrix;
        Matrix_X = p_matrix_X;
        Matrix_Y = p_matrix_Y;
    }
    /**
     * Dereferencing the matrix.
     */
    std::vector<int> operator[](unsigned index)
    {
        return Matrix[index];
    }
    /**
     * Assigning appropriate values to a class object.
     *
     * \param[in] matrix The vector of vectors, the value of which the matrix will take.
     *
     */
    void Get_Matrix(std::vector<std::vector<int>> matrix)
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
        unsigned long long Matrix_size{1};
        for (unsigned long long i = 0; i < Matrix_size; i++)
        {
            std::getline(std::cin, stroke, '\n');
            std::vector<int> Stroke;
            std::stringstream ss(stroke);
            int number;
            while (ss >> number)
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
     * \return The transposed matrix.
     */
    std::vector<std::vector<int>> Transposition()
    {
        std::vector<int> Null_vector = {0};
        std::vector<std::vector<int>> T_Matrix;
        if (Matrix_Y == Matrix_X)
        {
            T_Matrix = Matrix;
            for (unsigned long long i{0}; i < Matrix_Y; i++)
            {
                for (unsigned long long j{0}; j < Matrix_X; j++)
                {
                    T_Matrix[j][i] = Matrix[i][j];
                }
            }
            return T_Matrix;
        }
        else if (Matrix_Y != Matrix_X)
        {
            if (Matrix_Y < Matrix_X)
            {
                for (unsigned long long i{0}; i < Matrix_X; i++)
                {
                    T_Matrix.push_back(Null_vector);
                    for (unsigned long long j{0}; j < Matrix_Y - 1; j++)
                    {
                        T_Matrix[i].push_back(0);
                    }
                }
                for (unsigned long i{0}; i < Matrix_X; i++)
                {
                    for (unsigned long long j{0}; j < Matrix_Y; j++)
                    {
                        T_Matrix[i][j] = Matrix[j][i];
                    }
                }
                return T_Matrix;
            }
            else if (Matrix_Y > Matrix_X)
            {
                for (unsigned long long i{0}; i < Matrix_X; i++)
                {
                    T_Matrix.push_back(Null_vector);
                    for (unsigned long long j{0}; j < Matrix_Y - 1; j++)
                    {
                        T_Matrix[i].push_back(0);
                    }
                }
                for (unsigned long long i{0}; i < Matrix_Y; i++)
                {
                    for (unsigned long long j{0}; j < Matrix_X; j++)
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
     * \param[in] Index The index of the row or column to be deleted.
     * \param[in] Action_choice A variable that is responsible for selecting a row or column.
     *
     */
    void Delete(int Index, int Action_choice)
    {
        if (Action_choice == 0)
        {
            if (Index <= Matrix_X)
            {
                for (unsigned long long i{0}; i < Matrix_Y; i++)
                {
                    auto iter = Matrix[i].cbegin();
                    Matrix[i].erase(iter + Index);
                }
                Matrix_X = Matrix_X - 1;
            }
        }
        else if (Action_choice == 1)
        {
            if (Index <= Matrix_Y)
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
     * \param[in] Matrix1 The first multiplier of the composition.
     * \param[in] Matrix2 The second multiplier of the composition.
     *
     * \return matrix composition.
     */
    std::vector<std::vector<int>> Composition(std::vector<std::vector<int>> Matrix1, std::vector<std::vector<int>> Matrix2)
    {
        std::vector<std::vector<int>> Matrix_Composition;
        Matrix_Composition = Matrix2;
        unsigned long long matrix_X = Matrix2[0].size();
        unsigned long long matrix_Y = Matrix2.size();
        for (unsigned long long i{0}; i < matrix_Y; i++)
        {
            for (unsigned long long j{0}; j < matrix_X; j++)
            {
                Matrix_Composition[i][j] = 0;
                for (unsigned long long k{0}; k < matrix_Y; k++)
                {
                    Matrix_Composition[i][j] += Matrix1[i][k] * Matrix2[k][j];
                }
            }
        }
        return Matrix_Composition;
    }
    /**
    * Calculating the determinant of the matrix.
    *
    * \return determinant.
    */
    int Determinant()
    {
        int change_counter{0};
        double multiplier = 0;
        std::vector<std::vector<double>> Determinant_matrix;
        std::vector<double> v1;
        for(unsigned long long i{0}; i < Matrix_X; i++)
        {
            Determinant_matrix.push_back(v1);
            for(unsigned long long j{0}; j < Matrix_Y; j++)
            {
                Determinant_matrix[i].push_back(Matrix[i][j]);
            }
        }
        std::vector<double> Help_vector;
        double Determinant{1};
        if(Matrix_X == 0 && Matrix_Y == 0)
        {
            return 0;
        }
        else if(Matrix_X == 1 && Matrix_Y == 1)
        {
            return Matrix[0][0];
        }
        else
        {
            for(unsigned long long i{0}; i < Matrix_Y-1; i++)
            {
                for(unsigned long long j{i}; j < Matrix_X; j++)
                {
                    if(Determinant_matrix[j][i] != 0)
                    {
                        Help_vector = Determinant_matrix[i];
                        Determinant_matrix[i] = Determinant_matrix[j];
                        Determinant_matrix[j] = Help_vector;
                        break;
                    }
                    else
                    {
                        change_counter += 1;
                    }
                }
                for(unsigned long long j{i+1}; j < Matrix_X; j++)
                {
                    multiplier = Determinant_matrix[j][i] / Determinant_matrix[i][i];
                    for(unsigned long long k{i}; k < Matrix_X; k++)
                    {
                        Determinant_matrix[j][k] = (Determinant_matrix[j][k] - Determinant_matrix[i][k] * multiplier);
                    }
                }
            }
            for(unsigned long long f{0}; f < Matrix_X; f++)
            {
               Determinant = Determinant * Determinant_matrix[f][f];
            }
            return pow(-1, change_counter)*std::lround(Determinant);
        }
    }
    /**
     * Calculating the inverse matrix.
     *
     * \param[in] The inverse determinant of the matrix for which the inverse matrix is calculated.
     * \param[in] Action_choice the choice between the standard algorithm for finding the inverse matrix or the algorithm for the Hill cipher.
     *
     * \return Inverse matrix.
     */
    std::vector<std::vector<int>> Invers_Matrix(int Key_determinant_1 = 0, int Action_choice = 0)
    {
        Matrix_class Union_matrix(Matrix, Matrix_X, Matrix_Y);
        for (unsigned long long i{0}; i < Union_matrix.Matrix_Y; i++)
        {
            for (unsigned long long j{0}; j < Union_matrix.Matrix_X; j++)
            {
                Matrix_class Auxiliary_matrix(Matrix, Matrix_X, Matrix_Y);
                Auxiliary_matrix.Delete(j, 0);
                Auxiliary_matrix.Delete(i, 1);
                Union_matrix.Matrix[i][j] = pow(-1, (i + j)) * round(Auxiliary_matrix.Determinant());
            }
        }
        Union_matrix.Matrix = Union_matrix.Transposition();
        Matrix_class Key_1(Union_matrix.Matrix, Union_matrix.Matrix_X, Union_matrix.Matrix_Y);
        if (Action_choice == 1)
        {
            for (unsigned long long i{0}; i < Union_matrix.Matrix_Y; i++)
            {
                for (unsigned long long j{0}; j < Union_matrix.Matrix_X; j++)
                {
                    Key_1.Matrix[i][j] = Key_1.Matrix[i][j] * Key_determinant_1;
                }
            }
            return Key_1.Matrix;
        }
        else if (Action_choice == 0)
        {
            Matrix_class Key_Matrix(Matrix, Matrix[0].size(), Matrix.size());
            int Key_determinant = Key_Matrix.Determinant();
            for (unsigned long long i{0}; i < Union_matrix.Matrix_Y; i++)
            {
                for (unsigned long long j{0}; j < Union_matrix.Matrix_X; j++)
                {
                    Key_1.Matrix[i][j] = static_cast<int>(Key_1.Matrix[i][j] * (1 / Key_determinant));
                }
            }
            return Key_1.Matrix;
        }
    }
};

void hill_data_is_valid(const std::string &text, const std::string &ABC, Matrix_class &Key);
int greatest_common_divisor(int a, int b);
std::string Hill_cipher_encoder(std::string ABC, std::string Text, Matrix_class &Key_matrix);
std::string Hill_cipher_decoder(std::string ABC, std::string Cipher_Text, Matrix_class &Key_matrix);
std::string Rec_Hill_cipher_encoder(std::string ABC, std::string Text, Matrix_class &Key_matrix1, Matrix_class &Key_matrix2);
std::string Rec_Hill_cipher_decoder(std::string ABC, std::string Cipher_Text, Matrix_class &Key_matrix1, Matrix_class &Key_matrix2);

#endif // HILL_ENCODER
