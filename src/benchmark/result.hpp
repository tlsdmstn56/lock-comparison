#pragma once

#include <string>
#include <iostream>

struct BenchmarkResult {
    enum class BenchmarkStatus {
        SUCCESS,
        FAIL,
    };

    const std::string name;
    const BenchmarkStatus status;
    const uint64_t time;

    BenchmarkResult(const std::string& name, const BenchmarkStatus status, const uint64_t time): 
        name(name), status(status), time(time) {}

    void print() const {
        std::cout << '[' << name << ']' << '\n';
        switch (status)
        {
        case BenchmarkStatus::FAIL:
            std::cout << "Incorrect Lock Implementation\n";
            break;
        case BenchmarkStatus::SUCCESS:
            std::cout << "Time: " << time << " ms\n" ;
            break;
        }
    }
};