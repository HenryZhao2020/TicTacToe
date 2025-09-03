#ifndef TICTACTOE_OBSERVER_H
#define TICTACTOE_OBSERVER_H

#include <unordered_set>

class Subject;

/// Observer reacts to subject updates.
class Observer {
public:
    virtual ~Observer() = default;

    /// Called when the subject changes.
    virtual void notify(const Subject &sub) = 0;
};

/// Subject stores non-owning Observer* and notifies them.
class Subject {
public:
    virtual ~Subject() = 0;

    /// Adds an observer (no ownership). Ignores null.
    void attach(Observer *ob) {
        if (ob) observers.insert(ob);
    }

    /// Removes an observer. Safe to call multiple times.
    void detach(Observer *ob) {
        if (ob) observers.erase(ob);
    }

    /// Calls notify on all current observers.
    void notifyObservers() const {
        for (const auto snapshot = observers; auto *ob : snapshot) {
            if (observers.contains(ob)) {
                ob->notify(*this);
            }
        }
    }

private:
    std::unordered_set<Observer *> observers;
};

inline Subject::~Subject() = default;

#endif // TICTACTOE_OBSERVER_H
