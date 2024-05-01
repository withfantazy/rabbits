#pragma once
#include<string>

class FieldOverflow {
private:
	std::string message = "";
public:
	FieldOverflow(std::string& message) : message(message){}
};

class MathError {
private:
	std::string message = "";
public:
	MathError(std::string& message) : message(message) {}
};

class InvalidOperation {
private:
	std::string message = {};
public:
	InvalidOperation() = default;
	InvalidOperation(std::string message) : message(message) {}
};

class UndefinedBehavior {
private:
	std::string message = {};
public:
	UndefinedBehavior() = default;
	UndefinedBehavior(std::string message) : message(message) {}
};

class OutOfRange {
private:
	std::string message = {};
public:
	OutOfRange() = default;
	OutOfRange(std::string message) : message(message) {}
};