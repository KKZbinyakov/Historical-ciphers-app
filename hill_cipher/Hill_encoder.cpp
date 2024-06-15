#include "Hill_encoder.hpp"

/**
 * \file Hill_encoder.cpp
 *
 * This file describes the functions required to implement the Hill cipher.
 */

/**
 *
 * \param[in] text The text being checked for correctness.
 * \param[in] ABC The alphabet being checked for correctness.
 * \param[in] Key The key is a matrix that is checked for correctness.
 *
 * \throw Alphabet letter repeat error when alphabet letter repeat error.
 * \throw Unknown text symbol when there is a symbol in the text that is not in the alphabet.
 * \throw Invalid Key matrix when the determinant of the matrix does not satisfy the conditions of the algorithm.
 *
 */
void hill_data_is_valid(const std::string &text, const std::string &ABC, Matrix_class &Key)
{
    for (char c : ABC)
    {
        if (count(ABC.begin(), ABC.end(), c) > 1)
        {
            throw input_data_invalid("Alphabet letter repeat error");
        }
    }
    long long counter{0};
    for (char c : ABC)
    {
        counter += count(text.begin(), text.end(), c);
    }
    if (counter < text.size())
    {
        throw input_data_invalid("Unknown text symbol");
    }
    if(Key.Matrix_X != Key.Matrix_Y)
    {
        throw input_data_invalid("Invalid Key matrix");
    }
    int m;
    m = ABC.size();
    int Key_determinant = ((Key.Determinant() % m) + m) % m;
    if (greatest_common_divisor(m, Key_determinant) != 1 || Key_determinant == 0)
    {
        throw input_data_invalid("Invalid Key matrix");
    }
}

/**
 * Finding the largest common divisor.
 *
 * \param[in] a the first number in question.
 * \param[in] b the second number in question.
 *
 * \return greatest common divisor.
 */
int greatest_common_divisor(int a, int b)
{
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return greatest_common_divisor(a % b, b);
    return greatest_common_divisor(a, b % a);
}

/**
 * Implementation of Hill cipher encryption.
 *
 * \param[in] ABC alphabet.
 * \param[in] Text The text that is being encrypted.
 * \param[in] Key_matrix The key matrix.
 *
 * \return Encrypted text.
 */
std::string Hill_cipher_encoder(std::string ABC, std::string Text, Matrix_class &Key_matrix)
{
    try
    {
        int m = ABC.size();
        unsigned long long Lenght_of_text = Text.size();
        int Key_size = Key_matrix.Matrix_X;
        // int Key_determinant = ((Key_matrix.Determinant() % m) + m) % m;
        // while(greatest_common_divisor(m, Key_determinant) != 1 || Key_determinant == 0)
        //{
        //     Key_matrix.Enter_Matrix();
        //     Key_determinant = Key_matrix.Determinant();
        // }
        hill_data_is_valid(Text, ABC, Key_matrix);
        while (Lenght_of_text % Key_size != 0)
        {
            Text += ABC[0];
            Lenght_of_text = Text.size();
        }
        std::string Encrypted_text;
        std::vector<int> v1{0};
        std::vector<std::vector<int>> size_matrix;
        std::cout << Key_matrix.Determinant() << "\n";
        for (int i{0}; i < Key_size; i++)
        {
            auto iter = size_matrix.cbegin();
            size_matrix.emplace(iter + i, v1);
        }
        unsigned long long i = 0;
        Matrix_class Size_matrix(size_matrix, size_matrix[0].size(), size_matrix.size());
        while (i <= Lenght_of_text)
        {
            for (int j{0}; j < Key_size; j++)
            {
                Size_matrix.Matrix[j][0] = ABC.find(Text[i]);
                i += 1;
            }
            Size_matrix.Matrix = Key_matrix.Composition(Key_matrix.Matrix, Size_matrix.Matrix);
            for (int j{0}; j < Key_size; j++)
            {
                Size_matrix.Matrix[j][0] = Size_matrix.Matrix[j][0] % m;
                Encrypted_text += ABC[Size_matrix.Matrix[j][0]];
            }
            if (i == Lenght_of_text)
            {
                break;
            }
        }
        return Encrypted_text;
    }
    catch (input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * Implementation of Hill cipher decryption.
 *
 * \param[in] ABC alphabet.
 * \param[in] Cipher_Text The text that is being decrypted.
 * \param[in] Key_matrix The key matrix.
 *
 * \return Cipher text.
 */
std::string Hill_cipher_decoder(std::string ABC, std::string Cipher_Text, Matrix_class &Key_matrix)
{
    try
    {
        int m = ABC.size();
        unsigned long long Lenght_of_text = Cipher_Text.size();
        int Key_size = Key_matrix.Matrix_X;
        int Key_determinant = ((Key_matrix.Determinant() % m) + m) % m;
        // while(greatest_common_divisor(m, Key_determinant) != 1 || Key_determinant == 0)
        //{
        //     Key_matrix.Enter_Matrix();
        //     Key_determinant = Key_matrix.Determinant();
        // }
        hill_data_is_valid(Cipher_Text, ABC, Key_matrix);
        int Key_determinant_1;
        for (int i{0}; i < m; i++)
        {
            Key_determinant_1 = i;
            if (((Key_determinant * Key_determinant_1 % m) + m) % m == 1)
            {
                break;
            }
        }
        std::string Decode_Text = "";
        Matrix_class Key_1(Key_matrix.Invers_Matrix(Key_determinant_1, 1), Key_matrix.Matrix_X, Key_matrix.Matrix_Y);
        std::vector<int> v1{0};
        std::vector<std::vector<int>> size_matrix;
        for (int i{0}; i < Key_size; i++)
        {
            auto iter = size_matrix.cbegin();
            size_matrix.emplace(iter + i, v1);
        }
        unsigned long long i = 0;
        Matrix_class Size_matrix(size_matrix, size_matrix[0].size(), size_matrix.size());
        while (i <= Lenght_of_text)
        {
            if (i == Lenght_of_text)
            {
                break;
            }
            for (int j{0}; j < Key_size; j++)
            {
                Size_matrix.Matrix[j][0] = ABC.find(Cipher_Text[i]);
                i += 1;
            }
            Size_matrix.Matrix = Key_1.Composition(Key_1.Matrix, Size_matrix.Matrix);
            for (int j{0}; j < Key_size; j++)
            {
                Size_matrix.Matrix[j][0] = (Size_matrix.Matrix[j][0] % m + m) % m;
                Decode_Text += ABC[Size_matrix.Matrix[j][0]];
            }
        }
        return Decode_Text;
    }
    catch (input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * Implementation of Hill's recurrent cipher encryption.
 *
 * \param[in] ABC alphabet.
 * \param[in] Text The text that is being encrypted.
 * \param[in] Key_matrix1 The key matrix.
 * \param[in] Key_matrix2 The key matrix.
 *
 * \return Encrypted text.
 */
std::string Rec_Hill_cipher_encoder(std::string ABC, std::string Text, Matrix_class &Key_matrix1, Matrix_class &Key_matrix2)
{
    try
    {
        int m = ABC.size();
        unsigned long long Lenght_of_text = Text.size();
        int Key_size = Key_matrix1.Matrix_X;
        // int Key_determinant1 = ((Key_matrix1.Determinant() % m) + m) % m;
        // int Key_determinant2 = ((Key_matrix2.Determinant() % m) + m) % m;
        // while(greatest_common_divisor(m, Key_determinant1) != 1 || Key_determinant1 == 0)
        //{
        //     Key_matrix1.Enter_Matrix();
        //     Key_determinant1 = Key_matrix1.Determinant();
        // }
        // while(greatest_common_divisor(m, Key_determinant2) != 1 || Key_determinant2 == 0)
        //{
        //     Key_matrix2.Enter_Matrix();
        //     Key_determinant2 = Key_matrix2.Determinant();
        // }
        hill_data_is_valid(Text, ABC, Key_matrix1);
        hill_data_is_valid(Text, ABC, Key_matrix2);
        while (Lenght_of_text % Key_size != 0)
        {
            Text += ABC[0];
            Lenght_of_text = Text.size();
        }
        int Key_count = Lenght_of_text / Key_size;
        std::vector<Matrix_class> Key_set;
        Key_set.push_back(Key_matrix1);
        Key_set.push_back(Key_matrix2);
        std::string Encrypted_text = "";
        std::vector<int> v1{0};
        std::vector<std::vector<int>> size_matrix;
        std::string Part_of_Text{Text, 0, Key_size};
        Encrypted_text += Hill_cipher_encoder(ABC, Part_of_Text, Key_matrix1);
        Part_of_Text = Text.substr(Key_size, Key_size);
        Encrypted_text += Hill_cipher_encoder(ABC, Part_of_Text, Key_matrix2);
        for (int i{0}; i < Key_count - 2; i++)
        {
            Matrix_class Short_time_key(Key_set[i].Composition(Key_set[i].Matrix, Key_set[i + 1].Matrix), Key_set[i + 1].Matrix_X, Key_set[i + 1].Matrix_Y);
            Part_of_Text = Text.substr(Key_size + (i + 1) * Key_size, Key_size);
            Encrypted_text += Hill_cipher_encoder(ABC, Part_of_Text, Short_time_key);
            Key_set.push_back(Short_time_key);
        }
        return Encrypted_text;
    }
    catch (input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * Implementation of Hill's recurrent cipher decryption.
 *
 * \param[in] ABC alphabet.
 * \param[in] Cipher_Text The text that is being decrypted.
 * \param[in] Key_matrix1 The key matrix.
 * \param[in] Key_matrix2 The key matrix.
 *
 * \return Cipher text.
 */
std::string Rec_Hill_cipher_decoder(std::string ABC, std::string Cipher_Text, Matrix_class &Key_matrix1, Matrix_class &Key_matrix2)
{
    try
    {
        int m = ABC.size();
        unsigned long long Lenght_of_text = Cipher_Text.size();
        int Key_size = Key_matrix1.Matrix_X;
        int Key_determinant1 = ((Key_matrix1.Determinant() % m) + m) % m;
        int Key_determinant2 = ((Key_matrix2.Determinant() % m) + m) % m;
        // while(greatest_common_divisor(m, Key_determinant1) != 1 || Key_determinant1 == 0)
        //{
        //     Key_matrix1.Enter_Matrix();
        //     Key_determinant1 = Key_matrix1.Determinant();
        // }
        // while(greatest_common_divisor(m, Key_determinant2) != 1 || Key_determinant2 == 0)
        //{
        //     Key_matrix2.Enter_Matrix();
        //     Key_determinant2 = Key_matrix2.Determinant();
        // }
        hill_data_is_valid(Cipher_Text, ABC, Key_matrix1);
        hill_data_is_valid(Cipher_Text, ABC, Key_matrix2);
        int Key_count = Lenght_of_text / Key_size;
        std::vector<Matrix_class> Key_set;
        Key_set.push_back(Key_matrix1);
        Key_set.push_back(Key_matrix2);
        std::string Decode_Text = "";
        std::vector<int> v1{0};
        std::vector<std::vector<int>> size_matrix;
        std::string Part_of_Text{Cipher_Text, 0, Key_size};
        Decode_Text += Hill_cipher_decoder(ABC, Part_of_Text, Key_matrix1);
        Part_of_Text = Cipher_Text.substr(Key_size, Key_size);
        Decode_Text += Hill_cipher_decoder(ABC, Part_of_Text, Key_matrix2);
        for (int i{0}; i < Key_count - 2; i++)
        {
            Matrix_class Short_time_key(Key_set[i].Composition(Key_set[i].Matrix, Key_set[i + 1].Matrix), Key_set[i + 1].Matrix_X, Key_set[i + 1].Matrix_Y);
            Part_of_Text = Cipher_Text.substr(Key_size + (i + 1) * Key_size, Key_size);
            Decode_Text += Hill_cipher_decoder(ABC, Part_of_Text, Short_time_key);
            Key_set.push_back(Short_time_key);
        }
        return Decode_Text;
    }
    catch (input_data_invalid error)
    {
        return error.message;
    }
}
