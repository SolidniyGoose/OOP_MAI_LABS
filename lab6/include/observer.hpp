#pragma once
#include <string>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onKill(const std::string& killer,
                        const std::string& victim) = 0;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const std::string& killer,
                const std::string& victim) override;
};

class FileObserver : public Observer {
private:
    std::string filename;
public:
    FileObserver(const std::string& file = "log.txt");
    void onKill(const std::string& killer,
                const std::string& victim) override;
};