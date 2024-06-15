#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <exception>

/**
 * \file exceptions.hpp
 *
 * A file containing classes for working with exceptions.
 */

 /**
 * A class for working with exceptions.
 *
 */
class exception
{
public:
    exception() noexcept;
    exception(const exception&) noexcept;
    exception& operator=(const exception&) noexcept;
    virtual ~exception();
    virtual const char* what() const noexcept;
};

/**
 * A class to simplify error output.
 *
 */
class input_data_invalid: public std::exception
{
public:
    std::string message;
    input_data_invalid(const std::string& _message){
        message = _message;
    }

/**
 * The function that returns an error.
 *
 * \return message.c_str() error message.
 */
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

#endif // EXCEPTIONS
