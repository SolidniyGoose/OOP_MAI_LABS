#include "observer.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

void ConsoleObserver::onKill(const std::string& killer,
                           const std::string& victim,
                           int attack, int defense) {
    std::lock_guard<std::mutex> lock(coutMutex);
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    
    std::cout << "[БОЙ] " << std::put_time(std::localtime(&now_time), "%T")
              << " " << killer << " убил " << victim
              << " (атака: " << attack << " > защита: " << defense << ")" << std::endl;
}

void ConsoleObserver::onMove(const std::string& npc,
                           double x, double y) {
    std::lock_guard<std::mutex> lock(coutMutex);
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    
    std::cout << "[ДВИЖЕНИЕ] " << std::put_time(std::localtime(&now_time), "%T")
              << " " << npc << " переместился в (" 
              << x << ", " << y << ")" << std::endl;
}

FileObserver::FileObserver(const std::string& file) 
    : filename(file) {}

void FileObserver::onKill(const std::string& killer,
                        const std::string& victim,
                        int attack, int defense) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        
        file << "[БОЙ] " << std::put_time(std::localtime(&now_time), "%F %T")
             << " " << killer << " убил " << victim
             << " (атака: " << attack << " > защита: " << defense << ")" << std::endl;
    }
}

void FileObserver::onMove(const std::string& npc,
                        double x, double y) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        
        file << "[ДВИЖЕНИЕ] " << std::put_time(std::localtime(&now_time), "%F %T")
             << " " << npc << " переместился в (" 
             << x << ", " << y << ")" << std::endl;
    }
}