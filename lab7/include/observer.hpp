#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onKill(const std::string& killer,
                       const std::string& victim,
                       int attack, int defense) = 0;
    virtual void onMove(const std::string& npc,
                       double x, double y) = 0;
};

class ConsoleObserver : public Observer {
private:
    std::mutex coutMutex;
    
public:
    void onKill(const std::string& killer,
                const std::string& victim,
                int attack, int defense) override;
    void onMove(const std::string& npc,
                double x, double y) override;
};

class FileObserver : public Observer {
private:
    std::string filename;
    std::mutex fileMutex;
    
public:
    FileObserver(const std::string& file = "log.txt");
    void onKill(const std::string& killer,
                const std::string& victim,
                int attack, int defense) override;
    void onMove(const std::string& npc,
                double x, double y) override;
};