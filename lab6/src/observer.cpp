#include "observer.hpp"
#include <iostream>
#include <fstream>

void ConsoleObserver::onKill(const std::string& killer,
                             const std::string& victim) {
    std::cout << "[BATTLE] " << killer << " killed " << victim << std::endl;
}

FileObserver::FileObserver(const std::string& file) : filename(file) {}

void FileObserver::onKill(const std::string& killer,
                          const std::string& victim) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "[BATTLE] " << killer << " killed " << victim << std::endl;
    }
}