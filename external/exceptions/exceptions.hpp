#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <exception>

class exception
{
public:
    exception() noexcept;
    exception(const exception&) noexcept;
    exception& operator=(const exception&) noexcept;
    virtual ~exception();
    virtual const char* what() const noexcept;
};

class input_data_invalid: public std::exception
{
public:
    std::string message;
    input_data_invalid(const std::string& _message){
        message = _message;
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

#endif // EXCEPTIONS