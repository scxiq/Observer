#include <iostream>
#include <vector>
#include <algorithm>

// Інтерфейс спостерігача
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// Конкретний спостерігач
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const std::string& name) : name_(name) {}

    void update(const std::string& message) override {
        std::cout << name_ << " received message: " << message << "\n";
    }

private:
    std::string name_;
};

// Суб'єкт, за яким слідкується
class Subject {
public:
    void addObserver(Observer* observer) {
        observers_.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void notifyObservers(const std::string& message) {
        for (auto observer : observers_) {
            observer->update(message);
        }
    }

private:
    std::vector<Observer*> observers_;
};

int main() {
    // Використання паттерна "Спостерігач"
    Subject subject;

    ConcreteObserver observer1("Observer 1");
    ConcreteObserver observer2("Observer 2");
    ConcreteObserver observer3("Observer 3");

    // Підписка спостерігачів
    subject.addObserver(&observer1);
    subject.addObserver(&observer2);
    subject.addObserver(&observer3);

    // Відправлення повідомлення спостерігачам
    subject.notifyObservers("Hello, observers!");

    // Відписка спостерігача
    subject.removeObserver(&observer2);

    // Ще одне повідомлення
    subject.notifyObservers("Observer 2 is no longer receiving messages.");

    return 0;
}
