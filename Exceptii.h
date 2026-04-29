#pragma once
#include <exception>
#include <string>

class JocError : public std::exception {
protected:
    std::string mesaj;
public:
    explicit JocError(const std::string& m) : mesaj(">>> EROARE JOC: " + m) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class InputInvalid : public JocError {
public:
    explicit InputInvalid(const std::string& m) : JocError("Input invalid! " + m) {}
};

class ResurseInsuficiente : public JocError {
public:
    explicit ResurseInsuficiente(const std::string& m) : JocError("Puncte insuficiente pentru actiunea: " + m) {}
};

class ConfigurareInvalida : public JocError {
public:
    explicit ConfigurareInvalida(const std::string& m) : JocError("Configurare fatala: " + m) {}
};
